#include "StdAfx.h"
#include <EterPack/EterPackManager.h>

#include "PythonLauncher.h"
#include <chrono>
#include <ctime>

static PyObject* py_time_time(PyObject* self, PyObject* args)
{
	auto now = std::chrono::system_clock::now().time_since_epoch();
	double s = std::chrono::duration<double>(now).count();
	return PyFloat_FromDouble(s);
}

static PyObject* py_time_clock(PyObject* self, PyObject* args)
{
	static auto start = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();
	double s = std::chrono::duration<double>(now - start).count();
	return PyFloat_FromDouble(s);
}

static PyObject* py_time_sleep(PyObject* self, PyObject* args)
{
	double secs;
	if (!PyArg_ParseTuple(args, "d", &secs))
		return NULL;
	struct timespec ts;
	ts.tv_sec = (time_t)secs;
	ts.tv_nsec = (long)((secs - ts.tv_sec) * 1e9);
	nanosleep(&ts, NULL);
	Py_RETURN_NONE;
}

static PyObject* py_time_localtime(PyObject* self, PyObject* args)
{
	time_t t;
	double dt;
	if (args && PyTuple_Size(args) > 0) {
		if (!PyArg_ParseTuple(args, "d", &dt))
			return NULL;
		t = (time_t)dt;
	} else {
		t = ::time(NULL);
	}
	struct tm* tm_info = localtime(&t);
	if (!tm_info)
		return PyErr_SetFromErrno(PyExc_ValueError);
	return Py_BuildValue("(iiiiiiiii)",
		tm_info->tm_year + 1900,
		tm_info->tm_mon + 1,
		tm_info->tm_mday,
		tm_info->tm_hour,
		tm_info->tm_min,
		tm_info->tm_sec,
		(tm_info->tm_wday + 6) % 7,
		tm_info->tm_yday + 1,
		tm_info->tm_isdst
	);
}

static PyObject* py_time_strftime(PyObject* self, PyObject* args)
{
	const char* fmt;
	PyObject* tup = NULL;
	if (!PyArg_ParseTuple(args, "s|O", &fmt, &tup))
		return NULL;

	time_t t = ::time(NULL);
	struct tm* tm_info = localtime(&t);
	struct tm custom_tm;
	if (tup && PyTuple_Check(tup) && PyTuple_Size(tup) >= 9) {
		custom_tm.tm_year = PyInt_AsLong(PyTuple_GetItem(tup, 0)) - 1900;
		custom_tm.tm_mon  = PyInt_AsLong(PyTuple_GetItem(tup, 1)) - 1;
		custom_tm.tm_mday = PyInt_AsLong(PyTuple_GetItem(tup, 2));
		custom_tm.tm_hour = PyInt_AsLong(PyTuple_GetItem(tup, 3));
		custom_tm.tm_min  = PyInt_AsLong(PyTuple_GetItem(tup, 4));
		custom_tm.tm_sec  = PyInt_AsLong(PyTuple_GetItem(tup, 5));
		custom_tm.tm_wday = PyInt_AsLong(PyTuple_GetItem(tup, 6));
		custom_tm.tm_yday = PyInt_AsLong(PyTuple_GetItem(tup, 7)) - 1;
		custom_tm.tm_isdst= PyInt_AsLong(PyTuple_GetItem(tup, 8));
		tm_info = &custom_tm;
	}
	char buf[256];
	size_t len = strftime(buf, sizeof(buf), fmt, tm_info);
	return PyString_FromStringAndSize(buf, len);
}

static PyMethodDef s_time_methods[] = {
	{ "time", py_time_time, METH_NOARGS, "time() -> floating point number" },
	{ "clock", py_time_clock, METH_NOARGS, "clock() -> floating point number" },
	{ "sleep", py_time_sleep, METH_VARARGS, "sleep(seconds)" },
	{ "localtime", py_time_localtime, METH_VARARGS, "localtime([seconds]) -> tuple" },
	{ "strftime", py_time_strftime, METH_VARARGS, "strftime(format[, tuple]) -> string" },
	{ NULL, NULL, 0, NULL }
};

static void init_embedded_time()
{
	Py_InitModule("time", s_time_methods);
}

CPythonLauncher::CPythonLauncher()
{
	Py_NoSiteFlag = 1;
#if defined(__LINUX__) || defined(UNIX)
	static char s_pythonHome[] = ".";
	Py_SetPythonHome(s_pythonHome);
#endif
	Py_Initialize();
}

CPythonLauncher::~CPythonLauncher()
{
	Clear();
}

void CPythonLauncher::Clear()
{
	Py_Finalize();
}

std::string g_stTraceBuffer[512];
int	g_nCurTraceN = 0;

void Traceback()
{
	std::string str;

	for (int i = 0; i < g_nCurTraceN; ++i)
	{
		str.append(g_stTraceBuffer[i]);
		str.append("\n");
	}
	
	PyObject * exc;
	PyObject * v;
	PyObject * tb;
	const char * errStr;

	PyErr_Fetch(&exc, &v, &tb);

	if (PyString_Check(v))
	{
		errStr = PyString_AS_STRING(v);
		str.append("Error: ");
		str.append(errStr);

		Tracef("%s\n", errStr);
	}
	Py_DECREF(exc);
	Py_DECREF(v);
	Py_DECREF(tb);
	LogBoxf("Traceback:\n\n%s\n", str.c_str());
}

int TraceFunc(PyObject * obj, PyFrameObject * f, int what, PyObject *arg)
{
	const char * funcname;
	char szTraceBuffer[128];

	switch (what)
	{
		case PyTrace_CALL:
			if (g_nCurTraceN >= 512)
				return 0;

			if (Py_OptimizeFlag)
				f->f_lineno = PyCode_Addr2Line(f->f_code, f->f_lasti);

			funcname = PyString_AsString(f->f_code->co_name);

			_snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Call: File \"%s\", line %d, in %s", 
					  PyString_AsString(f->f_code->co_filename), 
					  f->f_lineno,
					  funcname);

			g_stTraceBuffer[g_nCurTraceN++]=szTraceBuffer;			
			break;

		case PyTrace_RETURN:
			if (g_nCurTraceN > 0)
				--g_nCurTraceN;
			break;

		case PyTrace_EXCEPTION:
			if (g_nCurTraceN >= 512)
				return 0;
			
			PyObject * exc_type, * exc_value, * exc_traceback;

			PyTuple_GetObject(arg, 0, &exc_type);
			PyTuple_GetObject(arg, 1, &exc_value);
			PyTuple_GetObject(arg, 2, &exc_traceback);

			Py_ssize_t len;
			const char * exc_str;
			PyObject_AsCharBuffer(exc_type, &exc_str, &len);
			
			_snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Exception: File \"%s\", line %d, in %s", 
					  PyString_AS_STRING(f->f_code->co_filename), 
					  f->f_lineno,
					  PyString_AS_STRING(f->f_code->co_name));

			g_stTraceBuffer[g_nCurTraceN++]=szTraceBuffer;
			
			break;
	}
	return 0;
}

void CPythonLauncher::SetTraceFunc(int (*pFunc)(PyObject * obj, PyFrameObject * f, int what, PyObject *arg))
{
	PyEval_SetTrace(pFunc, NULL);
}

bool CPythonLauncher::Create(const char* c_szProgramName)
{
	Py_SetProgramName((char*)c_szProgramName);
#ifdef _DEBUG
	PyEval_SetTrace(TraceFunc, NULL);
#endif
	m_poModule = PyImport_AddModule((char *) "__main__");

	if (!m_poModule)
		return false;
	
	m_poDic = PyModule_GetDict(m_poModule);

    PyObject * builtins = PyImport_ImportModule("__builtin__");
	PyModule_AddIntConstant(builtins, "TRUE", 1);
	PyModule_AddIntConstant(builtins, "FALSE", 0);
    PyDict_SetItemString(m_poDic, "__builtins__", builtins);
	Py_DECREF(builtins);

	init_embedded_time();

	if (!RunLine("import __main__"))
		return false;
	
	if (!RunLine("import sys"))
		return false;

	RunLine("sys.path.insert(0, 'lib')");

	return true;
}

bool CPythonLauncher::RunCompiledFile(const char* c_szFileName)
{
	FILE * fp = fopen(c_szFileName, "rb");

	if (!fp)
		return false;

	PyCodeObject *co;
	PyObject *v;
	long magic;
	long PyImport_GetMagicNumber(void);

	magic = _PyMarshal_ReadLongFromFile(fp);

	if (magic != PyImport_GetMagicNumber())
	{
		PyErr_SetString(PyExc_RuntimeError, "Bad magic number in .pyc file");
		fclose(fp);
		return false;
	}

	_PyMarshal_ReadLongFromFile(fp);
	v = _PyMarshal_ReadLastObjectFromFile(fp);

	fclose(fp);

	if (!v || !PyCode_Check(v))
	{
		Py_XDECREF(v);
		PyErr_SetString(PyExc_RuntimeError, "Bad code object in .pyc file");
		return false;
	}

	co = (PyCodeObject *) v;
	v = PyEval_EvalCode(co, m_poDic, m_poDic);
/*	if (v && flags)
		flags->cf_flags |= (co->co_flags & PyCF_MASK);*/
	Py_DECREF(co);
	if (!v)
	{
		Traceback();
		return false;
	}

	Py_DECREF(v);
	if (Py_FlushLine()) 
		PyErr_Clear();

	return true;
}


bool CPythonLauncher::RunMemoryTextFile(const char* c_szFileName, std::shared_ptr<std::vector<char>> fileData)
{
	std::string stConvFileData;
	stConvFileData.reserve(fileData->size());
	stConvFileData+="exec(compile('''";

	// ConvertPythonTextFormat
	{
		for (UINT i=0; i<fileData->size(); ++i)
		{
			if ((*fileData)[i] != 13)
				stConvFileData+= (*fileData)[i];
		}
	}

	stConvFileData+= "''', ";
	stConvFileData+= "'";
	stConvFileData+= c_szFileName;
	stConvFileData+= "', ";
	stConvFileData+= "'exec'))";

	const CHAR* c_pcConvFileData=stConvFileData.c_str();
	return RunLine(c_pcConvFileData);
}

bool CPythonLauncher::RunFile(const char* c_szFileName)
{
	CEterPackManager::TPackDataPtr data;
	if (!CEterPackManager::Instance().Get(c_szFileName, data))
		return false;
		
	if (data->size() == 0)
		return false;
		
	return RunMemoryTextFile(c_szFileName, data);
}

bool CPythonLauncher::RunLine(const char* c_szSrc)
{
	PyObject * v = PyRun_String((char *) c_szSrc, Py_file_input, m_poDic, m_poDic);

	if (!v)
	{
		Traceback();
		return false;
	}

	Py_DECREF(v);
	return true;
}

const char* CPythonLauncher::GetError()
{
	PyObject* exc;
	PyObject* v;
	PyObject* tb;

	PyErr_Fetch(&exc, &v, &tb);        

	if (PyString_Check(v))
		return PyString_AS_STRING(v);
	
	return "";
}
