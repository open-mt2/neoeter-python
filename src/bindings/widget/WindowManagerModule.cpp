#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

PyObject* wndMgrGetAspect(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("f", UI::CWindowManager::Instance().GetAspect());
}

PyObject* wndMgrOnceIgnoreMouseLeftButtonUpEvent(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindowManager::Instance().OnceIgnoreMouseLeftButtonUpEvent();
	return Py_BuildNone();
}

PyObject* wndMgrSetMouseHandler(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* poHandler;
	if (!PyTuple_GetObject(poArgs, 0, &poHandler))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetMouseHandler(poHandler);
	return Py_BuildNone();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

PyObject* wndMgrAttachIcon(PyObject* poSelf, PyObject* poArgs)
{
	int iType;
	if (!PyTuple_GetInteger(poArgs, 0, &iType))
		return Py_BuildException();
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();
	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 2, &iSlotNumber))
		return Py_BuildException();
	int iWidth;
	if (!PyTuple_GetInteger(poArgs, 3, &iWidth))
		return Py_BuildException();
	int iHeight;
	if (!PyTuple_GetInteger(poArgs, 4, &iHeight))
		return Py_BuildException();

	UI::CWindowManager::Instance().AttachIcon(iType, iIndex, iSlotNumber, iWidth, iHeight);
	return Py_BuildNone();
}

PyObject* wndMgrDeattachIcon(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindowManager::Instance().DeattachIcon();
	return Py_BuildNone();
}

PyObject* wndMgrSetAttachingFlag(PyObject* poSelf, PyObject* poArgs)
{
	int32_t bFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &bFlag))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetAttachingFlag(bFlag);
	return Py_BuildNone();
}

extern int32_t g_bOutlineBoxEnable;
extern int32_t g_bShowOverInWindowName;

PyObject* wndMgrSetOutlineFlag(PyObject* poSelf, PyObject* poArgs)
{
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &iFlag))
		return Py_BuildException();

	g_bOutlineBoxEnable = iFlag;

	return Py_BuildNone();
}

PyObject* wndMgrShowOverInWindowName(PyObject* poSelf, PyObject* poArgs)
{
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &iFlag))
		return Py_BuildException();

	g_bShowOverInWindowName = iFlag;

	return Py_BuildNone();
}

PyObject* wndMgrGetHyperlink(PyObject* poSelf, PyObject* poArgs)
{
	char retBuf[1024];
	int retLen = CGraphicTextInstance::Hyperlink_GetText(retBuf, sizeof(retBuf) - 1);
	retBuf[retLen] = '\0';

	return Py_BuildValue("s#", retBuf, retLen);
}

PyObject* wndMgrGetScreenWidth(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", UI::CWindowManager::Instance().GetScreenWidth());
}

PyObject* wndMgrGetScreenHeight(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", UI::CWindowManager::Instance().GetScreenHeight());
}

PyObject* wndMgrSetScreenSize(PyObject* poSelf, PyObject* poArgs)
{
	int width;
	if (!PyTuple_GetInteger(poArgs, 0, &width))
		return Py_BuildException();
	int height;
	if (!PyTuple_GetInteger(poArgs, 1, &height))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetScreenSize(width, height);
	return Py_BuildNone();
}

static PyMethodDef s_methods[] =
	{
		// WindowManager
		{"SetMouseHandler", wndMgrSetMouseHandler, METH_VARARGS, NULL},
		{"SetScreenSize", wndMgrSetScreenSize, METH_VARARGS, NULL},
		{"GetScreenWidth", wndMgrGetScreenWidth, METH_VARARGS, NULL},
		{"GetScreenHeight", wndMgrGetScreenHeight, METH_VARARGS, NULL},
		{"AttachIcon", wndMgrAttachIcon, METH_VARARGS, NULL},
		{"DeattachIcon", wndMgrDeattachIcon, METH_VARARGS, NULL},
		{"SetAttachingFlag", wndMgrSetAttachingFlag, METH_VARARGS, NULL},
		{"GetAspect", wndMgrGetAspect, METH_VARARGS, NULL},
		{"GetHyperlink", wndMgrGetHyperlink, METH_VARARGS, NULL},
		{"OnceIgnoreMouseLeftButtonUpEvent", wndMgrOnceIgnoreMouseLeftButtonUpEvent, METH_VARARGS, NULL},
		// For Debug
		{"SetOutlineFlag", wndMgrSetOutlineFlag, METH_VARARGS, NULL},
		{"ShowOverInWindowName", wndMgrShowOverInWindowName, METH_VARARGS, NULL},

		{NULL, NULL, 0, NULL},
};

const PyMethodDef* WindowManagerModuleMethods(uint32_t* puCount)
{
	*puCount = sizeof(s_methods) / sizeof(s_methods[0]) - 1;
	return s_methods;
}
