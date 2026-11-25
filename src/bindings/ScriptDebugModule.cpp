#include <Neoeter/Python/Bindings/StdAfx.h>

ScriptObject* dbgLogBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szMsg;
	char* szCaption;
	if (!ScriptTuple_GetString(poArgs, 0, &szMsg))
		return Script_BuildException();
	if (!ScriptTuple_GetString(poArgs, 1, &szCaption))
	{
		LogBox(szMsg);
	}
	else
	{
		LogBox(szMsg, szCaption);
	}
	return Script_BuildNone();
}

ScriptObject* dbgTrace(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szMsg;
	if (!ScriptTuple_GetString(poArgs, 0, &szMsg))
		return Script_BuildException();

	Trace(szMsg);
	return Script_BuildNone();
}

ScriptObject* dbgTracen(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szMsg;
	if (!ScriptTuple_GetString(poArgs, 0, &szMsg))
		return Script_BuildException();

	Tracen(szMsg);
	return Script_BuildNone();
}

ScriptObject* dbgTraceError(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szMsg;
	if (!ScriptTuple_GetString(poArgs, 0, &szMsg))
		return Script_BuildException();

	TraceError("%s", szMsg);
	return Script_BuildNone();
}

ScriptObject* dbgRegisterExceptionString(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szMsg;
	if (!ScriptTuple_GetString(poArgs, 0, &szMsg))
		return Script_BuildException();

	if (g_pkExceptionSender)
		g_pkExceptionSender->RegisterExceptionString(szMsg);

	return Script_BuildNone();
}

void initdbg()
{
	static ScriptMethodDef s_methods[] =
		{
			{"LogBox", dbgLogBox, SCRIPT_VARARGS, NULL},
			{"Trace", dbgTrace, SCRIPT_VARARGS, NULL},
			{"Tracen", dbgTracen, SCRIPT_VARARGS, NULL},
			{"TraceError", dbgTraceError, SCRIPT_VARARGS, NULL},
			{"RegisterExceptionString", dbgRegisterExceptionString, SCRIPT_VARARGS, NULL},
			{NULL, NULL, 0, NULL},
		};

	ScriptModule_Create("dbg", s_methods);
}