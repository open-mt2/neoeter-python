#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

PyObject* wndNumberSetNumber(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	char* szNumber;
	if (!PyTuple_GetString(poArgs, 1, &szNumber))
		return Py_BuildException();

	((UI::CNumberLine*)pWindow)->SetNumber(szNumber);

	return Py_BuildNone();
}

PyObject* wndNumberSetNumberHorizontalAlignCenter(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CNumberLine*)pWindow)->SetHorizontalAlign(UI::CWindow::HORIZONTAL_ALIGN_CENTER);

	return Py_BuildNone();
}

PyObject* wndNumberSetNumberHorizontalAlignRight(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CNumberLine*)pWindow)->SetHorizontalAlign(UI::CWindow::HORIZONTAL_ALIGN_RIGHT);

	return Py_BuildNone();
}

PyObject* wndNumberSetPath(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	char* szPath;
	if (!PyTuple_GetString(poArgs, 1, &szPath))
		return Py_BuildException();

	((UI::CNumberLine*)pWindow)->SetPath(szPath);

	return Py_BuildNone();
}

static PyMethodDef s_methods[] =
	{
		// NumberLine
		{"SetNumber", wndNumberSetNumber, METH_VARARGS, NULL},
		{"SetNumberHorizontalAlignCenter", wndNumberSetNumberHorizontalAlignCenter, METH_VARARGS, NULL},
		{"SetNumberHorizontalAlignRight", wndNumberSetNumberHorizontalAlignRight, METH_VARARGS, NULL},
		{"SetPath", wndNumberSetPath, METH_VARARGS, NULL},

		{NULL, NULL, 0, NULL},
};

const PyMethodDef* NumberLineModuleMethods(uint32_t* puCount)
{
	*puCount = sizeof(s_methods) / sizeof(s_methods[0]) - 1;
	return s_methods;
}
