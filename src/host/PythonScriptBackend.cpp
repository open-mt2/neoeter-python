#include <Neoeter/Python/Host/StdAfx.h>
#include <Neoeter/Python/Host/PythonScriptBackend.h>
#include <Neoeter/Python/Host/PythonLauncher.h>

#include <climits>

namespace
{
	PyObject* PythonExceptionType(ScriptErrorType type)
	{
		switch (type)
		{
			case ScriptErrorType::TypeError:
				return PyExc_TypeError;
			case ScriptErrorType::ValueError:
				return PyExc_ValueError;
			case ScriptErrorType::IndexError:
				return PyExc_IndexError;
			case ScriptErrorType::KeyError:
				return PyExc_KeyError;
			case ScriptErrorType::OverflowError:
				return PyExc_OverflowError;
			case ScriptErrorType::AttributeError:
				return PyExc_AttributeError;
			case ScriptErrorType::SystemError:
				return PyExc_SystemError;
			case ScriptErrorType::RuntimeError:
			default:
				return PyExc_RuntimeError;
		}
	}

	PyMethodDef s_weakrefCallbackDef = {
		const_cast<char*>("_neoeter_script_release"),
		nullptr, // set in Install (the callback is a private static)
		METH_O,
		nullptr,
	};
}

bool CPythonScriptBackend::RunFile(const char* path)
{
	return m_installed && CPythonLauncher::Instance().RunFile(path);
}

CPythonScriptBackend& CPythonScriptBackend::Instance()
{
	static CPythonScriptBackend s_instance;
	return s_instance;
}

void CPythonScriptBackend::Install()
{
	if (m_installed)
		return;

	s_weakrefCallbackDef.ml_meth = &CPythonScriptBackend::WeakrefCallback;
	m_weakrefCallback = PyCFunction_NewEx(&s_weakrefCallbackDef, nullptr, nullptr);
	m_installed = true;

	ScriptModule_AddListener(this);
	for (ScriptModuleData* module : ScriptModule_All())
	{
		OnModuleCreated(*module);
		for (const auto& constant : module->constants)
			OnModuleConstant(*module, constant.first, constant.second);
	}
}

void CPythonScriptBackend::Uninstall()
{
	if (!m_installed)
		return;

	ScriptModule_RemoveListener(this);

	for (auto& entry : m_wrappers)
	{
		Py_XDECREF(entry.second.weakref);
		ScriptObject_FreeForeign(entry.second.wrapper);
	}
	m_wrappers.clear();
	m_weakrefKeys.clear();

	Py_CLEAR(m_weakrefCallback);
	// Bindings stay allocated: the interpreter may still hold the functions
	// until Py_Finalize completes.
	m_installed = false;
}

// ---------------------------------------------------------------------------
// Modules
// ---------------------------------------------------------------------------
PyObject* CPythonScriptBackend::EnsurePythonModule(ScriptModuleData& module)
{
	// Borrowed; creates the module in sys.modules when missing.
	return PyImport_AddModule(const_cast<char*>(module.name.c_str()));
}

void CPythonScriptBackend::AddFunction(PyObject* pythonModule, const ScriptMethodDef& method)
{
	m_bindings.emplace_back();
	Binding& binding = m_bindings.back();
	binding.scriptDef = method;
	binding.name = method.name;
	binding.pythonDef.ml_name = const_cast<char*>(binding.name.c_str());
	binding.pythonDef.ml_meth = &CPythonScriptBackend::Trampoline;
	binding.pythonDef.ml_flags = METH_VARARGS;
	binding.pythonDef.ml_doc = const_cast<char*>(method.doc);

	PyObject* self = PyCObject_FromVoidPtr(&binding, nullptr);
	PyObject* moduleName = PyObject_GetAttrString(pythonModule, "__name__");
	PyObject* function = PyCFunction_NewEx(&binding.pythonDef, self, moduleName);
	Py_XDECREF(moduleName);
	Py_XDECREF(self);

	if (!function || PyModule_AddObject(pythonModule, binding.name.c_str(), function) != 0)
	{
		Py_XDECREF(function);
		PyErr_Print();
	}
}

void CPythonScriptBackend::OnModuleCreated(ScriptModuleData& module)
{
	OnModuleMethodsAdded(module, 0);
}

void CPythonScriptBackend::OnModuleMethodsAdded(ScriptModuleData& module, std::size_t firstNewMethod)
{
	PyObject* pythonModule = EnsurePythonModule(module);
	if (!pythonModule)
	{
		PyErr_Print();
		return;
	}

	// Re-registered functions replace the old ones, like Py_InitModule.
	for (std::size_t i = 0; i < module.methods.size(); ++i)
	{
		if (i >= firstNewMethod || !PyObject_HasAttrString(pythonModule, module.methods[i].name))
			AddFunction(pythonModule, module.methods[i]);
	}
}

void CPythonScriptBackend::OnModuleConstant(ScriptModuleData& module, const std::string& name, ScriptObject* value)
{
	PyObject* pythonModule = EnsurePythonModule(module);
	PyObject* pythonValue = ToPython(value);
	if (!pythonModule || !pythonValue || PyModule_AddObject(pythonModule, name.c_str(), pythonValue) != 0)
	{
		Py_XDECREF(pythonValue);
		PyErr_Print();
	}
}

bool CPythonScriptBackend::RaisePendingError()
{
	ScriptErrorType type;
	std::string message;
	if (!ScriptErr_Fetch(&type, &message))
		return false;

	PyErr_SetString(PythonExceptionType(type), message.c_str());
	return true;
}

PyObject* CPythonScriptBackend::Trampoline(PyObject* self, PyObject* args)
{
	Binding* binding = static_cast<Binding*>(PyCObject_AsVoidPtr(self));
	CPythonScriptBackend& backend = Instance();

	ScriptErr_Clear();
	ScriptObject* scriptArgs = args ? backend.FromPython(args) : ScriptTuple_New(0);
	ScriptObject* result = ScriptModule_Invoke(&binding->scriptDef, scriptArgs);
	Script_DecRef(scriptArgs);

	if (!result)
	{
		if (!RaisePendingError())
			PyErr_SetString(PyExc_SystemError, "error return without exception set");
		return nullptr;
	}

	PyObject* pythonResult = backend.ToPython(result);
	Script_DecRef(result);

	// Historic contract: Script_BuildException returns None *and* leaves a
	// RuntimeError pending; keep handing both to the interpreter.
	RaisePendingError();
	return pythonResult;
}

// ---------------------------------------------------------------------------
// Value conversion
// ---------------------------------------------------------------------------
PyObject* CPythonScriptBackend::ToPython(ScriptObject* object)
{
	if (!object)
		return nullptr;

	switch (object->Type())
	{
		case ScriptType::None:
			Py_RETURN_NONE;
		case ScriptType::Bool:
			return PyBool_FromLong(object->AsBool() ? 1 : 0);
		case ScriptType::Int:
		{
			const std::int64_t value = object->AsInt();
			if (value >= LONG_MIN && value <= LONG_MAX)
				return PyInt_FromLong(static_cast<long>(value));
			return PyLong_FromLongLong(value);
		}
		case ScriptType::Float:
			return PyFloat_FromDouble(object->AsFloat());
		case ScriptType::String:
			return PyString_FromStringAndSize(object->Bytes().data(), static_cast<Py_ssize_t>(object->Bytes().size()));
		case ScriptType::Tuple:
		{
			const auto& items = object->Items();
			PyObject* tuple = PyTuple_New(static_cast<Py_ssize_t>(items.size()));
			for (std::size_t i = 0; i < items.size(); ++i)
				PyTuple_SET_ITEM(tuple, i, ToPython(items[i]));
			return tuple;
		}
		case ScriptType::List:
		{
			const auto& items = object->Items();
			PyObject* list = PyList_New(static_cast<Py_ssize_t>(items.size()));
			for (std::size_t i = 0; i < items.size(); ++i)
				PyList_SET_ITEM(list, i, ToPython(items[i]));
			return list;
		}
		case ScriptType::Dict:
		{
			PyObject* dict = PyDict_New();
			for (const auto& entry : object->Entries())
			{
				PyObject* key = ToPython(entry.first);
				PyObject* value = ToPython(entry.second);
				PyDict_SetItem(dict, key, value);
				Py_DECREF(key);
				Py_DECREF(value);
			}
			return dict;
		}
		case ScriptType::Module:
		{
			PyObject* module = EnsurePythonModule(*object->Module());
			Py_XINCREF(module);
			return module;
		}
		case ScriptType::Object:
		{
			if (object->Backend() == this && object->Handle())
			{
				PyObject* pythonObject = static_cast<PyObject*>(object->Handle());
				Py_INCREF(pythonObject);
				return pythonObject;
			}

			TraceError("Python: cannot pass a %s object to Python", object->Backend() ? object->Backend()->Name() : "dead");
			Py_RETURN_NONE;
		}
	}

	Py_RETURN_NONE;
}

ScriptObject* CPythonScriptBackend::FromPython(PyObject* object)
{
	if (!object)
		return nullptr;

	if (object == Py_None)
		return Script_None();

	if (PyBool_Check(object))
		return ScriptBool_New(object == Py_True);

	if (PyInt_Check(object))
		return ScriptInt_New(PyInt_AS_LONG(object));

	if (PyLong_Check(object))
	{
		int overflow = 0;
		const PY_LONG_LONG value = PyLong_AsLongLongAndOverflow(object, &overflow);
		if (!overflow && !(value == -1 && PyErr_Occurred()))
			return ScriptInt_New(value);
		PyErr_Clear();
		return Wrap(object);
	}

	if (PyFloat_Check(object))
		return ScriptFloat_New(PyFloat_AS_DOUBLE(object));

	if (PyString_Check(object))
		return ScriptString_NewSize(PyString_AS_STRING(object), static_cast<std::size_t>(PyString_GET_SIZE(object)));

	if (PyTuple_Check(object))
	{
		const Py_ssize_t size = PyTuple_GET_SIZE(object);
		ScriptObject* tuple = ScriptTuple_New(static_cast<std::size_t>(size));
		for (Py_ssize_t i = 0; i < size; ++i)
			ScriptTuple_SetItem(tuple, static_cast<long>(i), FromPython(PyTuple_GET_ITEM(object, i)));
		return tuple;
	}

	if (PyList_Check(object))
	{
		const Py_ssize_t size = PyList_GET_SIZE(object);
		ScriptObject* list = ScriptList_New(static_cast<std::size_t>(size));
		for (Py_ssize_t i = 0; i < size; ++i)
			ScriptTuple_SetItem(list, static_cast<long>(i), FromPython(PyList_GET_ITEM(object, i)));
		return list;
	}

	if (PyDict_Check(object))
	{
		ScriptObject* dict = ScriptDict_New();
		Py_ssize_t pos = 0;
		PyObject* key;
		PyObject* value;
		while (PyDict_Next(object, &pos, &key, &value))
		{
			ScriptObject* scriptKey = FromPython(key);
			ScriptObject* scriptValue = FromPython(value);
			ScriptDict_SetItem(dict, scriptKey, scriptValue);
			Script_DecRef(scriptKey);
			Script_DecRef(scriptValue);
		}
		return dict;
	}

	return Wrap(object);
}

// ---------------------------------------------------------------------------
// Object wrappers
// ---------------------------------------------------------------------------
ScriptObject* CPythonScriptBackend::Wrap(PyObject* object)
{
	auto found = m_wrappers.find(object);
	if (found == m_wrappers.end())
	{
		WrapperEntry entry;
		entry.wrapper = ScriptObject_NewForeign(this, object);

		// Objects without weakref support (bound methods, unicode, ...) keep
		// their entry; a later object at the same address reuses it, which is
		// still correct because the wrapper is just (backend, address).
		if (PyType_SUPPORTS_WEAKREFS(Py_TYPE(object)) && m_weakrefCallback)
		{
			entry.weakref = PyWeakref_NewRef(object, m_weakrefCallback);
			if (entry.weakref)
				m_weakrefKeys[entry.weakref] = object;
			else
				PyErr_Clear();
		}

		found = m_wrappers.emplace(object, entry).first;
	}

	// The result is a new reference: the caller owns one Python reference.
	Py_INCREF(object);
	return found->second.wrapper;
}

PyObject* CPythonScriptBackend::WeakrefCallback(PyObject*, PyObject* weakref)
{
	Instance().OnWeakrefDead(weakref);
	Py_RETURN_NONE;
}

void CPythonScriptBackend::OnWeakrefDead(PyObject* weakref)
{
	auto key = m_weakrefKeys.find(weakref);
	if (key == m_weakrefKeys.end())
		return;

	auto entry = m_wrappers.find(key->second);
	m_weakrefKeys.erase(key);

	if (entry != m_wrappers.end() && entry->second.weakref == weakref)
	{
		ScriptObject_FreeForeign(entry->second.wrapper);
		m_wrappers.erase(entry);
	}

	Py_DECREF(weakref);
}

void CPythonScriptBackend::IncRef(ScriptObject* object)
{
	if (object->Handle())
		Py_INCREF(static_cast<PyObject*>(object->Handle()));
}

void CPythonScriptBackend::DecRef(ScriptObject* object)
{
	if (object->Handle())
		Py_DECREF(static_cast<PyObject*>(object->Handle()));
}

bool CPythonScriptBackend::HasAttr(ScriptObject* object, const char* name)
{
	return PyObject_HasAttrString(static_cast<PyObject*>(object->Handle()), name) != 0;
}

ScriptCallStatus CPythonScriptBackend::CallMethod(ScriptObject* object, const char* name, ScriptObject* args, ScriptObject** result)
{
	PyObject* self = static_cast<PyObject*>(object->Handle());
	PyObject* function = PyObject_GetAttrString(self, name);
	if (!function)
	{
		PyErr_Clear();
		return ScriptCallStatus::NoMethod;
	}

	if (!PyCallable_Check(function))
	{
		Py_DECREF(function);
		return ScriptCallStatus::NoMethod;
	}

	PyObject* pythonArgs = ToPython(args);
	if (pythonArgs && !PyTuple_Check(pythonArgs))
	{
		PyObject* wrapped = PyTuple_Pack(1, pythonArgs);
		Py_DECREF(pythonArgs);
		pythonArgs = wrapped;
	}

	PyObject* pythonResult = PyObject_CallObject(function, pythonArgs);
	Py_DECREF(function);
	Py_XDECREF(pythonArgs);

	if (!pythonResult)
	{
		if (g_pkExceptionSender)
			g_pkExceptionSender->Clear();

		PyErr_Print();

		if (g_pkExceptionSender)
			g_pkExceptionSender->Send();

		return ScriptCallStatus::Error;
	}

	*result = FromPython(pythonResult);
	Py_DECREF(pythonResult);
	return ScriptCallStatus::Ok;
}

std::string CPythonScriptBackend::Repr(ScriptObject* object)
{
	PyObject* repr = PyObject_Repr(static_cast<PyObject*>(object->Handle()));
	if (!repr)
	{
		PyErr_Clear();
		return "<python object>";
	}

	std::string text = PyString_Check(repr) ? PyString_AsString(repr) : "<python object>";
	Py_DECREF(repr);
	return text;
}
