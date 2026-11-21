#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

// Text
PyObject* wndTextSetMax(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iMax;
	if (!PyTuple_GetInteger(poArgs, 1, &iMax))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetMax(iMax);
	return Py_BuildNone();
}
PyObject* wndTextSetHorizontalAlign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetHorizontalAlign(iType);
	return Py_BuildNone();
}
PyObject* wndTextSetVerticalAlign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetVerticalAlign(iType);
	return Py_BuildNone();
}
PyObject* wndTextSetSecret(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetSecret(iFlag);
	return Py_BuildNone();
}
PyObject* wndTextSetOutline(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetOutline(iFlag);
	return Py_BuildNone();
}
PyObject* wndTextSetFeather(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetFeather(iFlag);
	return Py_BuildNone();
}
PyObject* wndTextSetMultiLine(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetMultiLine(iFlag);
	return Py_BuildNone();
}
PyObject* wndTextSetFontName(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	char* szFontName;
	if (!PyTuple_GetString(poArgs, 1, &szFontName))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetFontName(szFontName);
	return Py_BuildNone();
}
PyObject* wndTextSetFontColor(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	if (2 == PyTuple_Size(poArgs))
	{
		int iColor;
		if (!PyTuple_GetInteger(poArgs, 1, &iColor))
			return Py_BuildException();
		((UI::CTextLine*)pWindow)->SetFontColor(iColor);
	}
	else if (4 == PyTuple_Size(poArgs))
	{
		float fr;
		if (!PyTuple_GetFloat(poArgs, 1, &fr))
			return Py_BuildException();
		float fg;
		if (!PyTuple_GetFloat(poArgs, 2, &fg))
			return Py_BuildException();
		float fb;
		if (!PyTuple_GetFloat(poArgs, 3, &fb))
			return Py_BuildException();
		float fa = 1.0f;

		uint8_t argb[4] =
			{
				(uint8_t)(255.0f * fb),
				(uint8_t)(255.0f * fg),
				(uint8_t)(255.0f * fr),
				(uint8_t)(255.0f * fa)};
		((UI::CTextLine*)pWindow)->SetFontColor(*((uint32_t*)argb));
	}
	else
	{
		return Py_BuildException();
	}

	return Py_BuildNone();
}
PyObject* wndTextSetLimitWidth(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	float fWidth;
	if (!PyTuple_GetFloat(poArgs, 1, &fWidth))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetLimitWidth(fWidth);
	return Py_BuildNone();
}
PyObject* wndTextSetText(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	char* szText;
	if (!PyTuple_GetString(poArgs, 1, &szText))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->SetText(szText);
	return Py_BuildNone();
}
PyObject* wndTextGetText(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	return Py_BuildValue("s", ((UI::CTextLine*)pWindow)->GetText());
}

PyObject* wndTextGetTextSize(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int nWidth;
	int nHeight;

	UI::CTextLine* pkTextLine = (UI::CTextLine*)pWindow;
	pkTextLine->GetTextSize(&nWidth, &nHeight);

	return Py_BuildValue("(ii)", nWidth, nHeight);
}

PyObject* wndTextShowCursor(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->ShowCursor();
	return Py_BuildNone();
}
PyObject* wndTextHideCursor(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	((UI::CTextLine*)pWindow)->HideCursor();
	return Py_BuildNone();
}
PyObject* wndTextGetCursorPosition(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	return Py_BuildValue("i", ((UI::CTextLine*)pWindow)->GetCursorPosition());
}

static PyMethodDef s_methods[] =
	{
		// TextLine
		{"SetMax", wndTextSetMax, METH_VARARGS, NULL},
		{"SetHorizontalAlign", wndTextSetHorizontalAlign, METH_VARARGS, NULL},
		{"SetVerticalAlign", wndTextSetVerticalAlign, METH_VARARGS, NULL},
		{"SetSecret", wndTextSetSecret, METH_VARARGS, NULL},
		{"SetOutline", wndTextSetOutline, METH_VARARGS, NULL},
		{"SetFeather", wndTextSetFeather, METH_VARARGS, NULL},
		{"SetMultiLine", wndTextSetMultiLine, METH_VARARGS, NULL},
		{"SetText", wndTextSetText, METH_VARARGS, NULL},
		{"SetFontName", wndTextSetFontName, METH_VARARGS, NULL},
		{"SetFontColor", wndTextSetFontColor, METH_VARARGS, NULL},
		{"SetLimitWidth", wndTextSetLimitWidth, METH_VARARGS, NULL},
		{"GetText", wndTextGetText, METH_VARARGS, NULL},
		{"GetTextSize", wndTextGetTextSize, METH_VARARGS, NULL},
		{"ShowCursor", wndTextShowCursor, METH_VARARGS, NULL},
		{"HideCursor", wndTextHideCursor, METH_VARARGS, NULL},
		{"GetCursorPosition", wndTextGetCursorPosition, METH_VARARGS, NULL},

		{NULL, NULL, 0, NULL},
};

const PyMethodDef* TextLineModuleMethods(uint32_t* puCount)
{
	*puCount = sizeof(s_methods) / sizeof(s_methods[0]) - 1;
	return s_methods;
}
