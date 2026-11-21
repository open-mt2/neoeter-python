#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

///// Register /////
// Window
PyObject* wndMgrRegister(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindowManager& kWndMgr = UI::CWindowManager::Instance();
	UI::CWindow* pWindow = kWndMgr.RegisterWindow(po, szLayer);
	if (!pWindow)
		return Py_BuildException();

	return Py_BuildHandle(pWindow);
}

// SlotWindow
PyObject* wndMgrRegisterSlotWindow(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterSlotWindow(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// GridSlotWindow
PyObject* wndMgrRegisterGridSlotWindow(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterGridSlotWindow(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// TextLine
PyObject* wndMgrRegisterTextLine(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterTextLine(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// MarkBox
PyObject* wndMgrRegisterMarkBox(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterMarkBox(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// ImageBox
PyObject* wndMgrRegisterImageBox(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterImageBox(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// ExpandedImageBox
PyObject* wndMgrRegisterExpandedImageBox(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterExpandedImageBox(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// AniImageBox
PyObject* wndMgrRegisterAniImageBox(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterAniImageBox(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// RegisterButton
PyObject* wndMgrRegisterButton(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterButton(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// RadioButton
PyObject* wndMgrRegisterRadioButton(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterRadioButton(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// ToggleButton
PyObject* wndMgrRegisterToggleButton(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterToggleButton(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// DragButton
PyObject* wndMgrRegisterDragButton(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterDragButton(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// Box
PyObject* wndMgrRegisterBox(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBox(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// Bar
PyObject* wndMgrRegisterBar(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBar(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// Line
PyObject* wndMgrRegisterLine(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterLine(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// Slot
PyObject* wndMgrRegisterBar3D(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBar3D(po, szLayer);
	return Py_BuildHandle(pWindow);
}

// NumberLine
PyObject* wndMgrRegisterNumberLine(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* po;
	if (!PyTuple_GetObject(poArgs, 0, &po))
		return Py_BuildException();
	char* szLayer;
	if (!PyTuple_GetString(poArgs, 1, &szLayer))
		return Py_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterNumberLine(po, szLayer);
	return Py_BuildHandle(pWindow);
}
///// Register /////
/////////////////////////////////////////////////////////////////////////////////////////////////

PyObject* wndMgrDestroy(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().DestroyWindow(pWin);
	return Py_BuildNone();
}

PyObject* wndMgrIsFocus(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	return Py_BuildValue("i", pWindow == UI::CWindowManager::Instance().GetActivateWindow());
}

PyObject* wndMgrSetFocus(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().ActivateWindow(pWin);
	return Py_BuildNone();
}

PyObject* wndMgrKillFocus(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (PyTuple_GetWindow(poArgs, 0, &pWin))
	{
		if (pWin == UI::CWindowManager::Instance().GetActivateWindow())
		{
			UI::CWindowManager::Instance().DeactivateWindow();
		}
	}
	else
	{
		UI::CWindowManager::Instance().DeactivateWindow();
	}

	return Py_BuildNone();
}

PyObject* wndMgrLock(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().LockWindow(pWin);
	return Py_BuildNone();
}

PyObject* wndMgrUnlock(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindowManager::Instance().UnlockWindow();
	return Py_BuildNone();
}

PyObject* wndMgrSetName(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	char* szName;
	if (!PyTuple_GetString(poArgs, 1, &szName))
		return Py_BuildException();

	pWin->SetName(szName);
	return Py_BuildNone();
}

PyObject* wndMgrSetTop(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetTop(pWin);
	return Py_BuildNone();
}

PyObject* wndMgrShow(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	pWin->Show();
	return Py_BuildNone();
}

PyObject* wndMgrHide(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	pWin->Hide();
	return Py_BuildNone();
}

PyObject* wndMgrIsShow(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin->IsShow());
}

PyObject* wndMgrIsRTL(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin->IsFlag(UI::CWindow::FLAG_RTL));
}

PyObject* wndMgrSetParent(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	UI::CWindow* pParentWin;
	if (!PyTuple_GetWindow(poArgs, 1, &pParentWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetParent(pWin, pParentWin);
	return Py_BuildNone();
}

PyObject* wndMgrSetPickAlways(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindowManager::Instance().SetPickAlways(pWin);
	return Py_BuildNone();
}

PyObject* wndMgrSetWndSize(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int width;
	if (!PyTuple_GetInteger(poArgs, 1, &width))
		return Py_BuildException();
	int height;
	if (!PyTuple_GetInteger(poArgs, 2, &height))
		return Py_BuildException();

	pWin->SetSize(width, height);
	return Py_BuildNone();
}

PyObject* wndMgrSetWndPosition(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int x;
	if (!PyTuple_GetInteger(poArgs, 1, &x))
		return Py_BuildException();
	int y;
	if (!PyTuple_GetInteger(poArgs, 2, &y))
		return Py_BuildException();

	pWin->SetPosition(x, y);
	return Py_BuildNone();
}

PyObject* wndMgrGetName(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("s", pWin->GetName());
}

PyObject* wndMgrGetWndWidth(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin->GetWidth());
}

PyObject* wndMgrGetWndHeight(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin->GetHeight());
}

PyObject* wndMgrGetWndLocalPosition(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	long lx, ly;
	pWin->GetPosition(&lx, &ly);

	return Py_BuildValue("ii", lx, ly);
}

PyObject* wndMgrGetWndGlobalPosition(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	RECT& rRect = pWindow->GetRect();
	return Py_BuildValue("ii", rRect.left, rRect.top);
}

PyObject* wndMgrGetWindowRect(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	RECT& rRect = pWin->GetRect();
	return Py_BuildValue("iiii", rRect.left, rRect.top, rRect.right - rRect.left, rRect.bottom - rRect.top);
}

PyObject* wndMgrSetWindowHorizontalAlign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iAlign;
	if (!PyTuple_GetInteger(poArgs, 1, &iAlign))
		return Py_BuildException();

	pWin->SetHorizontalAlign(iAlign);

	return Py_BuildNone();
}

PyObject* wndMgrSetWindowVerticalAlign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iAlign;
	if (!PyTuple_GetInteger(poArgs, 1, &iAlign))
		return Py_BuildException();

	pWin->SetVerticalAlign(iAlign);

	return Py_BuildNone();
}

PyObject* wndMgrIsIn(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin == UI::CWindowManager::Instance().GetPointWindow());
}

PyObject* wndMgrGetMouseLocalPosition(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	long lx, ly;
	pWin->GetMouseLocalPosition(lx, ly);
	return Py_BuildValue("ii", lx, ly);
}

PyObject* wndMgrGetMousePosition(PyObject* poSelf, PyObject* poArgs)
{
	long lx, ly;
	UI::CWindowManager::Instance().GetMousePosition(lx, ly);
	return Py_BuildValue("ii", lx, ly);
}

PyObject* wndMgrIsDragging(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", UI::CWindowManager::Instance().IsDragging());
}

PyObject* wndMgrIsPickedWindow(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	UI::CWindow* pPickedWin = UI::CWindowManager::Instance().GetPointWindow();
	return Py_BuildValue("i", pWin == pPickedWin ? 1 : 0);
}

PyObject* wndMgrGetChildCount(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	return Py_BuildValue("i", pWin->GetChildCount());
}

PyObject* wndMgrAddFlag(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	char* pszFlag;
	if (!PyTuple_GetString(poArgs, 1, &pszFlag))
		return Py_BuildException();

	if (pszFlag && *pszFlag)
	{
		if (!stricmp(pszFlag, "movable"))
			pWin->AddFlag(UI::CWindow::FLAG_MOVABLE);
		else if (!stricmp(pszFlag, "limit"))
			pWin->AddFlag(UI::CWindow::FLAG_LIMIT);
		else if (!stricmp(pszFlag, "dragable"))
			pWin->AddFlag(UI::CWindow::FLAG_DRAGABLE);
		else if (!stricmp(pszFlag, "attach"))
			pWin->AddFlag(UI::CWindow::FLAG_ATTACH);
		else if (!stricmp(pszFlag, "restrict_x"))
			pWin->AddFlag(UI::CWindow::FLAG_RESTRICT_X);
		else if (!stricmp(pszFlag, "restrict_y"))
			pWin->AddFlag(UI::CWindow::FLAG_RESTRICT_Y);
		else if (!stricmp(pszFlag, "float"))
			pWin->AddFlag(UI::CWindow::FLAG_FLOAT);
		else if (!stricmp(pszFlag, "not_pick"))
			pWin->AddFlag(UI::CWindow::FLAG_NOT_PICK);
		else if (!stricmp(pszFlag, "ignore_size"))
			pWin->AddFlag(UI::CWindow::FLAG_IGNORE_SIZE);
		else if (!stricmp(pszFlag, "rtl"))
			pWin->AddFlag(UI::CWindow::FLAG_RTL);
		else if (!stricmp(pszFlag, "ltr"))
			pWin->RemoveFlag(UI::CWindow::FLAG_RTL);
		else
			TraceError("Unknown window flag %s", pszFlag);
	}

	return Py_BuildNone();
}

PyObject* wndMgrSetLimitBias(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int l;
	if (!PyTuple_GetInteger(poArgs, 1, &l))
		return Py_BuildException();
	int r;
	if (!PyTuple_GetInteger(poArgs, 2, &r))
		return Py_BuildException();
	int t;
	if (!PyTuple_GetInteger(poArgs, 3, &t))
		return Py_BuildException();
	int b;
	if (!PyTuple_GetInteger(poArgs, 4, &b))
		return Py_BuildException();

	pWin->SetLimitBias(l, r, t, b);
	return Py_BuildNone();
}

PyObject* wndMgrUpdateRect(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	pWin->UpdateRect();
	return Py_BuildNone();
}

PyObject* wndBarSetColor(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	int iColor;
	if (!PyTuple_GetInteger(poArgs, 1, &iColor))
		return Py_BuildException();

	if (pWindow->IsType(UI::CBar3D::Type()))
	{
		int iLeftColor = iColor;

		int iRightColor;
		if (!PyTuple_GetInteger(poArgs, 2, &iRightColor))
			return Py_BuildException();
		int iCenterColor;
		if (!PyTuple_GetInteger(poArgs, 3, &iCenterColor))
			return Py_BuildException();

		((UI::CBar3D*)pWindow)->SetColor(iLeftColor, iRightColor, iCenterColor);
	}
	else
	{
		((UI::CWindow*)pWindow)->SetColor(iColor);
	}
	return Py_BuildNone();
}

static PyMethodDef s_methods[] =
	{
		// Window
		{"Register", wndMgrRegister, METH_VARARGS, NULL},
		{"RegisterSlotWindow", wndMgrRegisterSlotWindow, METH_VARARGS, NULL},
		{"RegisterGridSlotWindow", wndMgrRegisterGridSlotWindow, METH_VARARGS, NULL},
		{"RegisterTextLine", wndMgrRegisterTextLine, METH_VARARGS, NULL},
		{"RegisterMarkBox", wndMgrRegisterMarkBox, METH_VARARGS, NULL},
		{"RegisterImageBox", wndMgrRegisterImageBox, METH_VARARGS, NULL},
		{"RegisterExpandedImageBox", wndMgrRegisterExpandedImageBox, METH_VARARGS, NULL},
		{"RegisterAniImageBox", wndMgrRegisterAniImageBox, METH_VARARGS, NULL},
		{"RegisterButton", wndMgrRegisterButton, METH_VARARGS, NULL},
		{"RegisterRadioButton", wndMgrRegisterRadioButton, METH_VARARGS, NULL},
		{"RegisterToggleButton", wndMgrRegisterToggleButton, METH_VARARGS, NULL},
		{"RegisterDragButton", wndMgrRegisterDragButton, METH_VARARGS, NULL},
		{"RegisterBox", wndMgrRegisterBox, METH_VARARGS, NULL},
		{"RegisterBar", wndMgrRegisterBar, METH_VARARGS, NULL},
		{"RegisterLine", wndMgrRegisterLine, METH_VARARGS, NULL},
		{"RegisterBar3D", wndMgrRegisterBar3D, METH_VARARGS, NULL},
		{"RegisterNumberLine", wndMgrRegisterNumberLine, METH_VARARGS, NULL},
		{"Destroy", wndMgrDestroy, METH_VARARGS, NULL},
		{"AddFlag", wndMgrAddFlag, METH_VARARGS, NULL},
		{"IsRTL", wndMgrIsRTL, METH_VARARGS, NULL},
		// Base Window
		{"SetName", wndMgrSetName, METH_VARARGS, NULL},
		{"GetName", wndMgrGetName, METH_VARARGS, NULL},
		{"SetTop", wndMgrSetTop, METH_VARARGS, NULL},
		{"Show", wndMgrShow, METH_VARARGS, NULL},
		{"Hide", wndMgrHide, METH_VARARGS, NULL},
		{"IsShow", wndMgrIsShow, METH_VARARGS, NULL},
		{"SetParent", wndMgrSetParent, METH_VARARGS, NULL},
		{"SetPickAlways", wndMgrSetPickAlways, METH_VARARGS, NULL},
		{"IsFocus", wndMgrIsFocus, METH_VARARGS, NULL},
		{"SetFocus", wndMgrSetFocus, METH_VARARGS, NULL},
		{"KillFocus", wndMgrKillFocus, METH_VARARGS, NULL},
		{"Lock", wndMgrLock, METH_VARARGS, NULL},
		{"Unlock", wndMgrUnlock, METH_VARARGS, NULL},
		{"SetWindowSize", wndMgrSetWndSize, METH_VARARGS, NULL},
		{"SetWindowPosition", wndMgrSetWndPosition, METH_VARARGS, NULL},
		{"GetWindowWidth", wndMgrGetWndWidth, METH_VARARGS, NULL},
		{"GetWindowHeight", wndMgrGetWndHeight, METH_VARARGS, NULL},
		{"GetWindowLocalPosition", wndMgrGetWndLocalPosition, METH_VARARGS, NULL},
		{"GetWindowGlobalPosition", wndMgrGetWndGlobalPosition, METH_VARARGS, NULL},
		{"GetWindowRect", wndMgrGetWindowRect, METH_VARARGS, NULL},
		{"SetWindowHorizontalAlign", wndMgrSetWindowHorizontalAlign, METH_VARARGS, NULL},
		{"SetWindowVerticalAlign", wndMgrSetWindowVerticalAlign, METH_VARARGS, NULL},
		{"GetChildCount", wndMgrGetChildCount, METH_VARARGS, NULL},
		{"IsPickedWindow", wndMgrIsPickedWindow, METH_VARARGS, NULL},
		{"IsIn", wndMgrIsIn, METH_VARARGS, NULL},
		{"GetMouseLocalPosition", wndMgrGetMouseLocalPosition, METH_VARARGS, NULL},
		{"GetMousePosition", wndMgrGetMousePosition, METH_VARARGS, NULL},
		{"IsDragging", wndMgrIsDragging, METH_VARARGS, NULL},
		{"SetLimitBias", wndMgrSetLimitBias, METH_VARARGS, NULL},
		{"UpdateRect", wndMgrUpdateRect, METH_VARARGS, NULL},
		// Bar
		{"SetColor", wndBarSetColor, METH_VARARGS, NULL},

		{NULL, NULL, 0, NULL},
};

const PyMethodDef* WindowModuleMethods(uint32_t* puCount)
{
	*puCount = sizeof(s_methods) / sizeof(s_methods[0]) - 1;
	return s_methods;
}
