#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

bool ScriptTuple_GetWindow(ScriptObject* poArgs, int pos, UI::CWindow** ppRetWindow)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetHandle(poArgs, pos, &pWindow))
		return false;
	if (!pWindow)
		return false;

	*ppRetWindow = pWindow;
	return true;
}

ScriptObject* wndMgrGetAspect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	return Script_BuildValue("f", UI::CWindowManager::Instance().GetAspect());
}

ScriptObject* wndMgrOnceIgnoreMouseLeftButtonUpEvent(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindowManager::Instance().OnceIgnoreMouseLeftButtonUpEvent();
	return Script_BuildNone();
}

ScriptObject* wndMgrSetMouseHandler(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* poHandler;
	if (!ScriptTuple_GetObject(poArgs, 0, &poHandler))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetMouseHandler(poHandler);
	return Script_BuildNone();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///// Register /////
// Window
ScriptObject* wndMgrRegister(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindowManager& kWndMgr = UI::CWindowManager::Instance();
	UI::CWindow* pWindow = kWndMgr.RegisterWindow(po, szLayer);
	if (!pWindow)
		return Script_BuildException();

	return Script_BuildHandle(pWindow);
}

// SlotWindow
ScriptObject* wndMgrRegisterSlotWindow(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterSlotWindow(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// GridSlotWindow
ScriptObject* wndMgrRegisterGridSlotWindow(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterGridSlotWindow(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// TextLine
ScriptObject* wndMgrRegisterTextLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterTextLine(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// MarkBox
ScriptObject* wndMgrRegisterMarkBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterMarkBox(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// ImageBox
ScriptObject* wndMgrRegisterImageBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterImageBox(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// ExpandedImageBox
ScriptObject* wndMgrRegisterExpandedImageBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterExpandedImageBox(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// AniImageBox
ScriptObject* wndMgrRegisterAniImageBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterAniImageBox(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// RegisterButton
ScriptObject* wndMgrRegisterButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterButton(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// RadioButton
ScriptObject* wndMgrRegisterRadioButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterRadioButton(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// ToggleButton
ScriptObject* wndMgrRegisterToggleButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterToggleButton(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// DragButton
ScriptObject* wndMgrRegisterDragButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterDragButton(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// Box
ScriptObject* wndMgrRegisterBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBox(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// Bar
ScriptObject* wndMgrRegisterBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBar(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// Line
ScriptObject* wndMgrRegisterLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterLine(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// Slot
ScriptObject* wndMgrRegisterBar3D(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterBar3D(po, szLayer);
	return Script_BuildHandle(pWindow);
}

// NumberLine
ScriptObject* wndMgrRegisterNumberLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	ScriptObject* po;
	if (!ScriptTuple_GetObject(poArgs, 0, &po))
		return Script_BuildException();
	char* szLayer;
	if (!ScriptTuple_GetString(poArgs, 1, &szLayer))
		return Script_BuildException();

	UI::CWindow* pWindow = UI::CWindowManager::Instance().RegisterNumberLine(po, szLayer);
	return Script_BuildHandle(pWindow);
}
///// Register /////
/////////////////////////////////////////////////////////////////////////////////////////////////

ScriptObject* wndMgrDestroy(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().DestroyWindow(pWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrIsFocus(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("i", pWindow == UI::CWindowManager::Instance().GetActivateWindow());
}

ScriptObject* wndMgrSetFocus(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().ActivateWindow(pWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrKillFocus(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (ScriptTuple_GetWindow(poArgs, 0, &pWin))
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

	return Script_BuildNone();
}

ScriptObject* wndMgrLock(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().LockWindow(pWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrUnlock(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindowManager::Instance().UnlockWindow();
	return Script_BuildNone();
}

ScriptObject* wndMgrSetName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	char* szName;
	if (!ScriptTuple_GetString(poArgs, 1, &szName))
		return Script_BuildException();

	pWin->SetName(szName);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetTop(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetTop(pWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrShow(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	pWin->Show();
	return Script_BuildNone();
}

ScriptObject* wndMgrHide(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	pWin->Hide();
	return Script_BuildNone();
}

ScriptObject* wndMgrIsShow(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin->IsShow());
}

ScriptObject* wndMgrIsRTL(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin->IsFlag(UI::CWindow::FLAG_RTL));
}

ScriptObject* wndMgrSetScreenSize(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int width;
	if (!ScriptTuple_GetInteger(poArgs, 0, &width))
		return Script_BuildException();
	int height;
	if (!ScriptTuple_GetInteger(poArgs, 1, &height))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetScreenSize(width, height);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetParent(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	UI::CWindow* pParentWin;
	if (!ScriptTuple_GetWindow(poArgs, 1, &pParentWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetParent(pWin, pParentWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetPickAlways(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetPickAlways(pWin);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetWndSize(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int width;
	if (!ScriptTuple_GetInteger(poArgs, 1, &width))
		return Script_BuildException();
	int height;
	if (!ScriptTuple_GetInteger(poArgs, 2, &height))
		return Script_BuildException();

	pWin->SetSize(width, height);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetWndPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 1, &x))
		return Script_BuildException();
	int y;
	if (!ScriptTuple_GetInteger(poArgs, 2, &y))
		return Script_BuildException();

	pWin->SetPosition(x, y);
	return Script_BuildNone();
}

ScriptObject* wndMgrGetName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("s", pWin->GetName());
}

ScriptObject* wndMgrGetWndWidth(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin->GetWidth());
}

ScriptObject* wndMgrGetWndHeight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin->GetHeight());
}

ScriptObject* wndMgrGetWndLocalPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	long lx, ly;
	pWin->GetPosition(&lx, &ly);

	return Script_BuildValue("ii", lx, ly);
}

ScriptObject* wndMgrGetWndGlobalPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	RECT& rRect = pWindow->GetRect();
	return Script_BuildValue("ii", rRect.left, rRect.top);
}

ScriptObject* wndMgrGetWindowRect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	RECT& rRect = pWin->GetRect();
	return Script_BuildValue("iiii", rRect.left, rRect.top, rRect.right - rRect.left, rRect.bottom - rRect.top);
}

ScriptObject* wndMgrSetWindowHorizontalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iAlign;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iAlign))
		return Script_BuildException();

	pWin->SetHorizontalAlign(iAlign);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetWindowVerticalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iAlign;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iAlign))
		return Script_BuildException();

	pWin->SetVerticalAlign(iAlign);

	return Script_BuildNone();
}

ScriptObject* wndMgrIsIn(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin == UI::CWindowManager::Instance().GetPointWindow());
}

ScriptObject* wndMgrGetMouseLocalPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	long lx, ly;
	pWin->GetMouseLocalPosition(lx, ly);
	return Script_BuildValue("ii", lx, ly);
}

ScriptObject* wndMgrGetHyperlink(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char retBuf[1024];
	int retLen = CGraphicTextInstance::Hyperlink_GetText(retBuf, sizeof(retBuf) - 1);
	retBuf[retLen] = '\0';

	return Script_BuildValue("s#", retBuf, retLen);
}

ScriptObject* wndMgrGetScreenWidth(ScriptObject* poSelf, ScriptObject* poArgs)
{
	return Script_BuildValue("i", UI::CWindowManager::Instance().GetScreenWidth());
}

ScriptObject* wndMgrGetScreenHeight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	return Script_BuildValue("i", UI::CWindowManager::Instance().GetScreenHeight());
}

ScriptObject* wndMgrGetMousePosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	long lx, ly;
	UI::CWindowManager::Instance().GetMousePosition(lx, ly);
	return Script_BuildValue("ii", lx, ly);
}

ScriptObject* wndMgrIsDragging(ScriptObject* poSelf, ScriptObject* poArgs)
{
	return Script_BuildValue("i", UI::CWindowManager::Instance().IsDragging());
}

ScriptObject* wndMgrIsPickedWindow(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	UI::CWindow* pPickedWin = UI::CWindowManager::Instance().GetPointWindow();
	return Script_BuildValue("i", pWin == pPickedWin ? 1 : 0);
}

ScriptObject* wndMgrGetChildCount(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	return Script_BuildValue("i", pWin->GetChildCount());
}

ScriptObject* wndMgrAddFlag(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	char* pszFlag;
	if (!ScriptTuple_GetString(poArgs, 1, &pszFlag))
		return Script_BuildException();

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

	return Script_BuildNone();
}

ScriptObject* wndMgrSetLimitBias(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int l;
	if (!ScriptTuple_GetInteger(poArgs, 1, &l))
		return Script_BuildException();
	int r;
	if (!ScriptTuple_GetInteger(poArgs, 2, &r))
		return Script_BuildException();
	int t;
	if (!ScriptTuple_GetInteger(poArgs, 3, &t))
		return Script_BuildException();
	int b;
	if (!ScriptTuple_GetInteger(poArgs, 4, &b))
		return Script_BuildException();

	pWin->SetLimitBias(l, r, t, b);
	return Script_BuildNone();
}

ScriptObject* wndMgrUpdateRect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	pWin->UpdateRect();
	return Script_BuildNone();
}

ScriptObject* wndMgrAppendSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iIndex))
		return Script_BuildException();

	int ixPosition;
	if (!ScriptTuple_GetInteger(poArgs, 2, &ixPosition))
		return Script_BuildException();

	int iyPosition;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iyPosition))
		return Script_BuildException();

	int ixCellSize;
	if (!ScriptTuple_GetInteger(poArgs, 4, &ixCellSize))
		return Script_BuildException();

	int iyCellSize;
	if (!ScriptTuple_GetInteger(poArgs, 5, &iyCellSize))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->AppendSlot(iIndex, ixPosition, iyPosition, ixCellSize, iyCellSize);

	return Script_BuildNone();
}

ScriptObject* wndMgrArrangeSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iStartIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iStartIndex))
		return Script_BuildException();

	int ixCellCount;
	if (!ScriptTuple_GetInteger(poArgs, 2, &ixCellCount))
		return Script_BuildException();

	int iyCellCount;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iyCellCount))
		return Script_BuildException();

	int ixCellSize;
	if (!ScriptTuple_GetInteger(poArgs, 4, &ixCellSize))
		return Script_BuildException();

	int iyCellSize;
	if (!ScriptTuple_GetInteger(poArgs, 5, &iyCellSize))
		return Script_BuildException();

	int ixBlank;
	if (!ScriptTuple_GetInteger(poArgs, 6, &ixBlank))
		return Script_BuildException();

	int iyBlank;
	if (!ScriptTuple_GetInteger(poArgs, 7, &iyBlank))
		return Script_BuildException();

	if (!pWin->IsType(UI::CGridSlotWindow::Type()))
	{
		TraceError("wndMgr.ArrangeSlot : not a grid window");
		return Script_BuildException();
	}

	UI::CGridSlotWindow* pGridSlotWin = (UI::CGridSlotWindow*)pWin;
	pGridSlotWin->ArrangeGridSlot(iStartIndex, ixCellCount, iyCellCount, ixCellSize, iyCellSize, ixBlank, iyBlank);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotBaseImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	float fr;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fr))
		return Script_BuildException();
	float fg;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fg))
		return Script_BuildException();
	float fb;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fb))
		return Script_BuildException();
	float fa;
	if (!ScriptTuple_GetFloat(poArgs, 5, &fa))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
	{
		TraceError("wndMgr.ArrangeSlot : not a slot window");
		return Script_BuildException();
	}

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotBaseImage(szFileName, fr, fg, fb, fa);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetCoverButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	char* szUpImageName;
	if (!ScriptTuple_GetString(poArgs, 2, &szUpImageName))
		return Script_BuildException();
	char* szOverImageName;
	if (!ScriptTuple_GetString(poArgs, 3, &szOverImageName))
		return Script_BuildException();
	char* szDownImageName;
	if (!ScriptTuple_GetString(poArgs, 4, &szDownImageName))
		return Script_BuildException();
	char* szDisableImageName;
	if (!ScriptTuple_GetString(poArgs, 5, &szDisableImageName))
		return Script_BuildException();

	int iLeftButtonEnable;
	if (!ScriptTuple_GetInteger(poArgs, 6, &iLeftButtonEnable))
		return Script_BuildException();
	int iRightButtonEnable;
	if (!ScriptTuple_GetInteger(poArgs, 7, &iRightButtonEnable))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->SetCoverButton(iSlotIndex, szUpImageName, szOverImageName, szDownImageName, szDisableImageName, iLeftButtonEnable, iRightButtonEnable);

	return Script_BuildNone();
}

ScriptObject* wndMgrEnableCoverButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->EnableCoverButton(iSlotIndex);

	return Script_BuildNone();
}

ScriptObject* wndMgrDisableCoverButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->DisableCoverButton(iSlotIndex);

	return Script_BuildNone();
}

ScriptObject* wndMgrIsDisableCoverButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	return Script_BuildValue("i", pSlotWin->IsDisableCoverButton(iSlotIndex));
}

ScriptObject* wndMgrSetAlwaysRenderCoverButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotIndex;
	bool bAlwaysRender = false;

	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!ScriptTuple_GetBoolean(poArgs, 2, &bAlwaysRender))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->SetAlwaysRenderCoverButton(iSlotIndex, bAlwaysRender);

	return Script_BuildNone();
}

ScriptObject* wndMgrAppendSlotButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	char* szUpImageName;
	if (!ScriptTuple_GetString(poArgs, 1, &szUpImageName))
		return Script_BuildException();
	char* szOverImageName;
	if (!ScriptTuple_GetString(poArgs, 2, &szOverImageName))
		return Script_BuildException();
	char* szDownImageName;
	if (!ScriptTuple_GetString(poArgs, 3, &szDownImageName))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->AppendSlotButton(szUpImageName, szOverImageName, szDownImageName);

	return Script_BuildNone();
}

ScriptObject* wndMgrAppendRequirementSignImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	char* szImageName;
	if (!ScriptTuple_GetString(poArgs, 1, &szImageName))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->AppendRequirementSignImage(szImageName);

	return Script_BuildNone();
}

ScriptObject* wndMgrShowSlotButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->ShowSlotButton(iSlotNumber);

	return Script_BuildNone();
}

ScriptObject* wndMgrHideAllSlotButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->HideAllSlotButton();

	return Script_BuildNone();
}

ScriptObject* wndMgrShowRequirementSign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->ShowRequirementSign(iSlotNumber);

	return Script_BuildNone();
}

ScriptObject* wndMgrHideRequirementSign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->HideRequirementSign(iSlotNumber);

	return Script_BuildNone();
}

ScriptObject* wndMgrRefreshSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->RefreshSlot();

	return Script_BuildNone();
}

ScriptObject* wndMgrSetUseMode(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetUseMode(iFlag);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetUsableItem(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetUsableItem(iFlag);

	return Script_BuildNone();
}

ScriptObject* wndMgrClearSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearSlot(iSlotIndex);

	return Script_BuildNone();
}

ScriptObject* wndMgrClearAllSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearAllSlot();

	return Script_BuildNone();
}

ScriptObject* wndMgrHasSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;

	return Script_BuildValue("i", pSlotWin->HasSlot(iSlotIndex));
}

ScriptObject* wndMgrSetSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	int iItemIndex;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iItemIndex))
		return Script_BuildException();

	int iWidth;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iWidth))
		return Script_BuildException();

	int iHeight;
	if (!ScriptTuple_GetInteger(poArgs, 4, &iHeight))
		return Script_BuildException();

	CGraphicImage* pImage;
	if (!ScriptTuple_GetHandle(poArgs, 5, &pImage))
		return Script_BuildException();

	D3DXCOLOR diffuseColor;
	ScriptObject* pTuple;
	if (!ScriptTuple_GetObject(poArgs, 6, &pTuple))
	{
		diffuseColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		// return Script_BuildException();
	}
	else
	// get diffuse color from pTuple
	{
		if (ScriptTuple_Size(pTuple) != 4)
			return Script_BuildException();
		if (!ScriptTuple_GetFloat(pTuple, 0, &diffuseColor.r))
			return Script_BuildException();
		if (!ScriptTuple_GetFloat(pTuple, 1, &diffuseColor.g))
			return Script_BuildException();
		if (!ScriptTuple_GetFloat(pTuple, 2, &diffuseColor.b))
			return Script_BuildException();
		if (!ScriptTuple_GetFloat(pTuple, 3, &diffuseColor.a))
			return Script_BuildException();
	}

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlot(iSlotIndex, iItemIndex, iWidth, iHeight, pImage, diffuseColor);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotCount(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	int iCount;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iCount))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCount(iSlotIndex, iCount);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotCountNew(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	int iGrade;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iGrade))
		return Script_BuildException();

	int iCount;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iCount))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCountNew(iSlotIndex, iGrade, iCount);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotCoolTime(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	float fCoolTime;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fCoolTime))
		return Script_BuildException();

	float fElapsedTime = 0.0f;
	ScriptTuple_GetFloat(poArgs, 3, &fElapsedTime);

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCoolTime(iSlotIndex, fCoolTime, fElapsedTime);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetToggleSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	assert(!"wndMgrSetToggleSlot - \xBB\xE7\xBF\xEB\xC7\xCF\xC1\xF6 \xBE\xCA\xB4\xC2 \xC7\xD4\xBC\xF6");
	return Script_BuildNone();
}

ScriptObject* wndMgrActivateSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ActivateSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrDeactivateSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->DeactivateSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrEnableSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->EnableSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrDisableSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->DisableSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrShowSlotBaseImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ShowSlotBaseImage(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrHideSlotBaseImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->HideSlotBaseImage(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotType(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iType;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iType))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotType(iType);

	return Script_BuildNone();
}

ScriptObject* wndMgrSetSlotStyle(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iStyle;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iStyle))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotStyle(iStyle);

	return Script_BuildNone();
}

ScriptObject* wndMgrSelectSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	int iIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SelectSlot(iIndex);

	return Script_BuildNone();
}

ScriptObject* wndMgrClearSelected(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearSelected();

	return Script_BuildNone();
}

ScriptObject* wndMgrGetSelectedSlotCount(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Script_BuildValue("i", pSlotWin->GetSelectedSlotCount());
}

ScriptObject* wndMgrGetSelectedSlotNumber(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Script_BuildValue("i", pSlotWin->GetSelectedSlotNumber(iSlotNumber));
}

ScriptObject* wndMgrIsSelectedSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Script_BuildValue("i", pSlotWin->isSelectedSlot(iSlotNumber));
}

ScriptObject* wndMgrGetSlotCount(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Script_BuildValue("i", pSlotWin->GetSlotCount());
}

ScriptObject* wndMgrLockSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->LockSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndMgrUnlockSlot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWin;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWin))
		return Script_BuildException();
	int iSlotIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Script_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Script_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->UnlockSlot(iSlotIndex);
	return Script_BuildNone();
}

ScriptObject* wndBarSetColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iColor;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iColor))
		return Script_BuildException();

	if (pWindow->IsType(UI::CBar3D::Type()))
	{
		int iLeftColor = iColor;

		int iRightColor;
		if (!ScriptTuple_GetInteger(poArgs, 2, &iRightColor))
			return Script_BuildException();
		int iCenterColor;
		if (!ScriptTuple_GetInteger(poArgs, 3, &iCenterColor))
			return Script_BuildException();

		((UI::CBar3D*)pWindow)->SetColor(iLeftColor, iRightColor, iCenterColor);
	}
	else
	{
		((UI::CWindow*)pWindow)->SetColor(iColor);
	}
	return Script_BuildNone();
}

ScriptObject* wndMgrAttachIcon(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iType;
	if (!ScriptTuple_GetInteger(poArgs, 0, &iType))
		return Script_BuildException();
	int iIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iIndex))
		return Script_BuildException();
	int iSlotNumber;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iSlotNumber))
		return Script_BuildException();
	int iWidth;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iWidth))
		return Script_BuildException();
	int iHeight;
	if (!ScriptTuple_GetInteger(poArgs, 4, &iHeight))
		return Script_BuildException();

	UI::CWindowManager::Instance().AttachIcon(iType, iIndex, iSlotNumber, iWidth, iHeight);
	return Script_BuildNone();
}

ScriptObject* wndMgrDeattachIcon(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindowManager::Instance().DeattachIcon();
	return Script_BuildNone();
}

ScriptObject* wndMgrSetAttachingFlag(ScriptObject* poSelf, ScriptObject* poArgs)
{
	BOOL bFlag;
	if (!ScriptTuple_GetInteger(poArgs, 0, &bFlag))
		return Script_BuildException();

	UI::CWindowManager::Instance().SetAttachingFlag(bFlag);
	return Script_BuildNone();
}

// Text
ScriptObject* wndTextSetMax(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iMax;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iMax))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetMax(iMax);
	return Script_BuildNone();
}
ScriptObject* wndTextSetHorizontalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iType;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iType))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetHorizontalAlign(iType);
	return Script_BuildNone();
}
ScriptObject* wndTextSetVerticalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iType;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iType))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetVerticalAlign(iType);
	return Script_BuildNone();
}
ScriptObject* wndTextSetSecret(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetSecret(iFlag);
	return Script_BuildNone();
}
ScriptObject* wndTextSetOutline(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetOutline(iFlag);
	return Script_BuildNone();
}
ScriptObject* wndTextSetFeather(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetFeather(iFlag);
	return Script_BuildNone();
}
ScriptObject* wndTextSetMultiLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iFlag))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetMultiLine(iFlag);
	return Script_BuildNone();
}
ScriptObject* wndTextSetFontName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFontName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFontName))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetFontName(szFontName);
	return Script_BuildNone();
}
ScriptObject* wndTextSetFontColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	if (2 == ScriptTuple_Size(poArgs))
	{
		int iColor;
		if (!ScriptTuple_GetInteger(poArgs, 1, &iColor))
			return Script_BuildException();
		((UI::CTextLine*)pWindow)->SetFontColor(iColor);
	}
	else if (4 == ScriptTuple_Size(poArgs))
	{
		float fr;
		if (!ScriptTuple_GetFloat(poArgs, 1, &fr))
			return Script_BuildException();
		float fg;
		if (!ScriptTuple_GetFloat(poArgs, 2, &fg))
			return Script_BuildException();
		float fb;
		if (!ScriptTuple_GetFloat(poArgs, 3, &fb))
			return Script_BuildException();
		float fa = 1.0f;

		BYTE argb[4] =
			{
				(BYTE)(255.0f * fb),
				(BYTE)(255.0f * fg),
				(BYTE)(255.0f * fr),
				(BYTE)(255.0f * fa)};
		((UI::CTextLine*)pWindow)->SetFontColor(*((DWORD*)argb));
	}
	else
	{
		return Script_BuildException();
	}

	return Script_BuildNone();
}
ScriptObject* wndTextSetLimitWidth(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fWidth;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fWidth))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetLimitWidth(fWidth);
	return Script_BuildNone();
}
ScriptObject* wndTextSetText(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szText;
	if (!ScriptTuple_GetString(poArgs, 1, &szText))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->SetText(szText);
	return Script_BuildNone();
}
ScriptObject* wndTextGetText(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("s", ((UI::CTextLine*)pWindow)->GetText());
}

ScriptObject* wndTextGetTextSize(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int nWidth;
	int nHeight;

	UI::CTextLine* pkTextLine = (UI::CTextLine*)pWindow;
	pkTextLine->GetTextSize(&nWidth, &nHeight);

	return Script_BuildValue("(ii)", nWidth, nHeight);
}

ScriptObject* wndTextShowCursor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->ShowCursor();
	return Script_BuildNone();
}
ScriptObject* wndTextHideCursor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CTextLine*)pWindow)->HideCursor();
	return Script_BuildNone();
}
ScriptObject* wndTextGetCursorPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("i", ((UI::CTextLine*)pWindow)->GetCursorPosition());
}

ScriptObject* wndNumberSetNumber(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szNumber;
	if (!ScriptTuple_GetString(poArgs, 1, &szNumber))
		return Script_BuildException();

	((UI::CNumberLine*)pWindow)->SetNumber(szNumber);

	return Script_BuildNone();
}

ScriptObject* wndNumberSetNumberHorizontalAlignCenter(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CNumberLine*)pWindow)->SetHorizontalAlign(UI::CWindow::HORIZONTAL_ALIGN_CENTER);

	return Script_BuildNone();
}

ScriptObject* wndNumberSetNumberHorizontalAlignRight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CNumberLine*)pWindow)->SetHorizontalAlign(UI::CWindow::HORIZONTAL_ALIGN_RIGHT);

	return Script_BuildNone();
}

ScriptObject* wndNumberSetPath(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szPath;
	if (!ScriptTuple_GetString(poArgs, 1, &szPath))
		return Script_BuildException();

	((UI::CNumberLine*)pWindow)->SetPath(szPath);

	return Script_BuildNone();
}

ScriptObject* wndMarkBox_SetImageFilename(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CMarkBox*)pWindow)->LoadImage(szFileName);
	return Script_BuildNone();
}

ScriptObject* wndMarkBox_SetImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	// 아무것도 하지 않음
	return Script_BuildNone();
}

ScriptObject* wndMarkBox_Load(ScriptObject* poSelf, ScriptObject* poArgs)
{
	// 아무것도 하지 않음
	return Script_BuildNone();
}

ScriptObject* wndMarkBox_SetIndex(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	int nIndex;
	if (!ScriptTuple_GetInteger(poArgs, 1, &nIndex))
		return Script_BuildException();

	((UI::CMarkBox*)pWindow)->SetIndex(nIndex);
	return Script_BuildNone();
}

ScriptObject* wndMarkBox_SetScale(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	float fScale;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fScale))
		return Script_BuildException();

	((UI::CMarkBox*)pWindow)->SetScale(fScale);
	return Script_BuildNone();
}

ScriptObject* wndMarkBox_SetDiffuseColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fr;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fr))
		return Script_BuildException();
	float fg;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fg))
		return Script_BuildException();
	float fb;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fb))
		return Script_BuildException();
	float fa;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fa))
		return Script_BuildException();

	((UI::CMarkBox*)pWindow)->SetDiffuseColor(fr, fg, fb, fa);

	return Script_BuildNone();
}

ScriptObject* wndImageLoadImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	if (!((UI::CImageBox*)pWindow)->LoadImage(szFileName))
		return Script_BuildException("Failed to load image (filename: %s)", szFileName);

	return Script_BuildNone();
}

ScriptObject* wndImageSetDiffuseColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fr;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fr))
		return Script_BuildException();
	float fg;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fg))
		return Script_BuildException();
	float fb;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fb))
		return Script_BuildException();
	float fa;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fa))
		return Script_BuildException();

	((UI::CImageBox*)pWindow)->SetDiffuseColor(fr, fg, fb, fa);

	return Script_BuildNone();
}

ScriptObject* wndImageGetWidth(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("i", ((UI::CImageBox*)pWindow)->GetWidth());
}

ScriptObject* wndImageGetHeight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("i", ((UI::CImageBox*)pWindow)->GetHeight());
}

ScriptObject* wndImageSetScale(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fx;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fx))
		return Script_BuildException();
	float fy;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fy))
		return Script_BuildException();

	((UI::CExpandedImageBox*)pWindow)->SetScale(fx, fy);

	return Script_BuildNone();
}
ScriptObject* wndImageSetOrigin(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fx;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fx))
		return Script_BuildException();
	float fy;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fy))
		return Script_BuildException();

	((UI::CExpandedImageBox*)pWindow)->SetOrigin(fx, fy);

	return Script_BuildNone();
}
ScriptObject* wndImageSetRotation(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fRotation;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fRotation))
		return Script_BuildException();

	((UI::CExpandedImageBox*)pWindow)->SetRotation(fRotation);

	return Script_BuildNone();
}
ScriptObject* wndImageSetRenderingRect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fLeft;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fLeft))
		return Script_BuildException();
	float fTop;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fTop))
		return Script_BuildException();
	float fRight;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fRight))
		return Script_BuildException();
	float fBottom;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fBottom))
		return Script_BuildException();

	if (pWindow->IsType(UI::CExpandedImageBox::Type()))
		((UI::CExpandedImageBox*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);
	else if (pWindow->IsType(UI::CAniImageBox::Type()))
		((UI::CAniImageBox*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);

	return Script_BuildNone();
}
ScriptObject* wndImageSetRenderingMode(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int iMode;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iMode))
		return Script_BuildException();

	if (pWindow->IsType(UI::CExpandedImageBox::Type()))
		((UI::CExpandedImageBox*)pWindow)->SetRenderingMode(iMode);

	return Script_BuildNone();
}
ScriptObject* wndImageSetDelay(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	float fDelay;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fDelay))
		return Script_BuildException();

	((UI::CAniImageBox*)pWindow)->SetDelay(fDelay);

	return Script_BuildNone();
}
ScriptObject* wndImageAppendImage(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CAniImageBox*)pWindow)->AppendImage(szFileName);

	return Script_BuildNone();
}

ScriptObject* wndButtonSetUpVisual(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CButton*)pWindow)->SetUpVisual(szFileName);

	return Script_BuildNone();
}
ScriptObject* wndButtonSetOverVisual(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CButton*)pWindow)->SetOverVisual(szFileName);

	return Script_BuildNone();
}
ScriptObject* wndButtonSetDownVisual(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CButton*)pWindow)->SetDownVisual(szFileName);

	return Script_BuildNone();
}
ScriptObject* wndButtonSetDisableVisual(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	((UI::CButton*)pWindow)->SetDisableVisual(szFileName);

	return Script_BuildNone();
}
ScriptObject* wndButtonGetUpVisualFileName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("s", ((UI::CButton*)pWindow)->GetUpVisualFileName());
}
ScriptObject* wndButtonGetOverVisualFileName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("s", ((UI::CButton*)pWindow)->GetOverVisualFileName());
}
ScriptObject* wndButtonGetDownVisualFileName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("s", ((UI::CButton*)pWindow)->GetDownVisualFileName());
}
ScriptObject* wndButtonFlash(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CButton*)pWindow)->Flash();

	return Script_BuildNone();
}
ScriptObject* wndButtonEnable(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CButton*)pWindow)->Enable();

	return Script_BuildNone();
}
ScriptObject* wndButtonDisable(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CButton*)pWindow)->Disable();

	return Script_BuildNone();
}
ScriptObject* wndButtonDown(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CButton*)pWindow)->Down();

	return Script_BuildNone();
}
ScriptObject* wndButtonSetUp(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	((UI::CButton*)pWindow)->SetUp();

	return Script_BuildNone();
}
ScriptObject* wndButtonSetRestrictMovementArea(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();
	int ix;
	if (!ScriptTuple_GetInteger(poArgs, 1, &ix))
		return Script_BuildException();
	int iy;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iy))
		return Script_BuildException();
	int iwidth;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iwidth))
		return Script_BuildException();
	int iheight;
	if (!ScriptTuple_GetInteger(poArgs, 4, &iheight))
		return Script_BuildException();

	((UI::CDragButton*)pWindow)->SetRestrictMovementArea(ix, iy, iwidth, iheight);

	return Script_BuildNone();
}

ScriptObject* wndButtonIsDown(ScriptObject* poSelf, ScriptObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!ScriptTuple_GetWindow(poArgs, 0, &pWindow))
		return Script_BuildException();

	return Script_BuildValue("i", ((UI::CButton*)pWindow)->IsPressed());
}

extern BOOL g_bOutlineBoxEnable;
extern BOOL g_bShowOverInWindowName;

ScriptObject* wndMgrSetOutlineFlag(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 0, &iFlag))
		return Script_BuildException();

	g_bOutlineBoxEnable = iFlag;

	return Script_BuildNone();
}

ScriptObject* wndMgrShowOverInWindowName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iFlag;
	if (!ScriptTuple_GetInteger(poArgs, 0, &iFlag))
		return Script_BuildException();

	g_bShowOverInWindowName = iFlag;

	return Script_BuildNone();
}

void initwndMgr()
{
	static ScriptMethodDef s_methods[] =
		{
			// WindowManager
			{"SetMouseHandler", wndMgrSetMouseHandler, SCRIPT_VARARGS, NULL},
			{"SetScreenSize", wndMgrSetScreenSize, SCRIPT_VARARGS, NULL},
			{"GetScreenWidth", wndMgrGetScreenWidth, SCRIPT_VARARGS, NULL},
			{"GetScreenHeight", wndMgrGetScreenHeight, SCRIPT_VARARGS, NULL},
			{"AttachIcon", wndMgrAttachIcon, SCRIPT_VARARGS, NULL},
			{"DeattachIcon", wndMgrDeattachIcon, SCRIPT_VARARGS, NULL},
			{"SetAttachingFlag", wndMgrSetAttachingFlag, SCRIPT_VARARGS, NULL},
			{"GetAspect", wndMgrGetAspect, SCRIPT_VARARGS, NULL},
			{"GetHyperlink", wndMgrGetHyperlink, SCRIPT_VARARGS, NULL},
			{"OnceIgnoreMouseLeftButtonUpEvent", wndMgrOnceIgnoreMouseLeftButtonUpEvent, SCRIPT_VARARGS, NULL},

			// Window
			{"Register", wndMgrRegister, SCRIPT_VARARGS, NULL},
			{"RegisterSlotWindow", wndMgrRegisterSlotWindow, SCRIPT_VARARGS, NULL},
			{"RegisterGridSlotWindow", wndMgrRegisterGridSlotWindow, SCRIPT_VARARGS, NULL},
			{"RegisterTextLine", wndMgrRegisterTextLine, SCRIPT_VARARGS, NULL},
			{"RegisterMarkBox", wndMgrRegisterMarkBox, SCRIPT_VARARGS, NULL},
			{"RegisterImageBox", wndMgrRegisterImageBox, SCRIPT_VARARGS, NULL},
			{"RegisterExpandedImageBox", wndMgrRegisterExpandedImageBox, SCRIPT_VARARGS, NULL},
			{"RegisterAniImageBox", wndMgrRegisterAniImageBox, SCRIPT_VARARGS, NULL},
			{"RegisterButton", wndMgrRegisterButton, SCRIPT_VARARGS, NULL},
			{"RegisterRadioButton", wndMgrRegisterRadioButton, SCRIPT_VARARGS, NULL},
			{"RegisterToggleButton", wndMgrRegisterToggleButton, SCRIPT_VARARGS, NULL},
			{"RegisterDragButton", wndMgrRegisterDragButton, SCRIPT_VARARGS, NULL},
			{"RegisterBox", wndMgrRegisterBox, SCRIPT_VARARGS, NULL},
			{"RegisterBar", wndMgrRegisterBar, SCRIPT_VARARGS, NULL},
			{"RegisterLine", wndMgrRegisterLine, SCRIPT_VARARGS, NULL},
			{"RegisterBar3D", wndMgrRegisterBar3D, SCRIPT_VARARGS, NULL},
			{"RegisterNumberLine", wndMgrRegisterNumberLine, SCRIPT_VARARGS, NULL},
			{"Destroy", wndMgrDestroy, SCRIPT_VARARGS, NULL},
			{"AddFlag", wndMgrAddFlag, SCRIPT_VARARGS, NULL},
			{"IsRTL", wndMgrIsRTL, SCRIPT_VARARGS, NULL},

			// Base Window
			{"SetName", wndMgrSetName, SCRIPT_VARARGS, NULL},
			{"GetName", wndMgrGetName, SCRIPT_VARARGS, NULL},

			{"SetTop", wndMgrSetTop, SCRIPT_VARARGS, NULL},
			{"Show", wndMgrShow, SCRIPT_VARARGS, NULL},
			{"Hide", wndMgrHide, SCRIPT_VARARGS, NULL},
			{"IsShow", wndMgrIsShow, SCRIPT_VARARGS, NULL},
			{"SetParent", wndMgrSetParent, SCRIPT_VARARGS, NULL},
			{"SetPickAlways", wndMgrSetPickAlways, SCRIPT_VARARGS, NULL},

			{"IsFocus", wndMgrIsFocus, SCRIPT_VARARGS, NULL},
			{"SetFocus", wndMgrSetFocus, SCRIPT_VARARGS, NULL},
			{"KillFocus", wndMgrKillFocus, SCRIPT_VARARGS, NULL},
			{"Lock", wndMgrLock, SCRIPT_VARARGS, NULL},
			{"Unlock", wndMgrUnlock, SCRIPT_VARARGS, NULL},

			{"SetWindowSize", wndMgrSetWndSize, SCRIPT_VARARGS, NULL},
			{"SetWindowPosition", wndMgrSetWndPosition, SCRIPT_VARARGS, NULL},
			{"GetWindowWidth", wndMgrGetWndWidth, SCRIPT_VARARGS, NULL},
			{"GetWindowHeight", wndMgrGetWndHeight, SCRIPT_VARARGS, NULL},
			{"GetWindowLocalPosition", wndMgrGetWndLocalPosition, SCRIPT_VARARGS, NULL},
			{"GetWindowGlobalPosition", wndMgrGetWndGlobalPosition, SCRIPT_VARARGS, NULL},
			{"GetWindowRect", wndMgrGetWindowRect, SCRIPT_VARARGS, NULL},
			{"SetWindowHorizontalAlign", wndMgrSetWindowHorizontalAlign, SCRIPT_VARARGS, NULL},
			{"SetWindowVerticalAlign", wndMgrSetWindowVerticalAlign, SCRIPT_VARARGS, NULL},

			{"GetChildCount", wndMgrGetChildCount, SCRIPT_VARARGS, NULL},

			{"IsPickedWindow", wndMgrIsPickedWindow, SCRIPT_VARARGS, NULL},
			{"IsIn", wndMgrIsIn, SCRIPT_VARARGS, NULL},
			{"GetMouseLocalPosition", wndMgrGetMouseLocalPosition, SCRIPT_VARARGS, NULL},
			{"GetMousePosition", wndMgrGetMousePosition, SCRIPT_VARARGS, NULL},
			{"IsDragging", wndMgrIsDragging, SCRIPT_VARARGS, NULL},

			{"SetLimitBias", wndMgrSetLimitBias, SCRIPT_VARARGS, NULL},

			{"UpdateRect", wndMgrUpdateRect, SCRIPT_VARARGS, NULL},

			// Slot Window
			{"AppendSlot", wndMgrAppendSlot, SCRIPT_VARARGS, NULL},
			{"ArrangeSlot", wndMgrArrangeSlot, SCRIPT_VARARGS, NULL},
			{"ClearSlot", wndMgrClearSlot, SCRIPT_VARARGS, NULL},
			{"ClearAllSlot", wndMgrClearAllSlot, SCRIPT_VARARGS, NULL},
			{"HasSlot", wndMgrHasSlot, SCRIPT_VARARGS, NULL},
			{"SetSlot", wndMgrSetSlot, SCRIPT_VARARGS, NULL},
			{"SetSlotCount", wndMgrSetSlotCount, SCRIPT_VARARGS, NULL},
			{"SetSlotCountNew", wndMgrSetSlotCountNew, SCRIPT_VARARGS, NULL},
			{"SetSlotCoolTime", wndMgrSetSlotCoolTime, SCRIPT_VARARGS, NULL},
			{"SetToggleSlot", wndMgrSetToggleSlot, SCRIPT_VARARGS, NULL},
			{"ActivateSlot", wndMgrActivateSlot, SCRIPT_VARARGS, NULL},
			{"DeactivateSlot", wndMgrDeactivateSlot, SCRIPT_VARARGS, NULL},
			{"EnableSlot", wndMgrEnableSlot, SCRIPT_VARARGS, NULL},
			{"DisableSlot", wndMgrDisableSlot, SCRIPT_VARARGS, NULL},
			{"ShowSlotBaseImage", wndMgrShowSlotBaseImage, SCRIPT_VARARGS, NULL},
			{"HideSlotBaseImage", wndMgrHideSlotBaseImage, SCRIPT_VARARGS, NULL},
			{"SetSlotType", wndMgrSetSlotType, SCRIPT_VARARGS, NULL},
			{"SetSlotStyle", wndMgrSetSlotStyle, SCRIPT_VARARGS, NULL},
			{"SetSlotBaseImage", wndMgrSetSlotBaseImage, SCRIPT_VARARGS, NULL},

			{"SetCoverButton", wndMgrSetCoverButton, SCRIPT_VARARGS, NULL},
			{"EnableCoverButton", wndMgrEnableCoverButton, SCRIPT_VARARGS, NULL},
			{"DisableCoverButton", wndMgrDisableCoverButton, SCRIPT_VARARGS, NULL},
			{"IsDisableCoverButton", wndMgrIsDisableCoverButton, SCRIPT_VARARGS, NULL},
			{"SetAlwaysRenderCoverButton", wndMgrSetAlwaysRenderCoverButton, SCRIPT_VARARGS, NULL},

			{"AppendSlotButton", wndMgrAppendSlotButton, SCRIPT_VARARGS, NULL},
			{"AppendRequirementSignImage", wndMgrAppendRequirementSignImage, SCRIPT_VARARGS, NULL},
			{"ShowSlotButton", wndMgrShowSlotButton, SCRIPT_VARARGS, NULL},
			{"HideAllSlotButton", wndMgrHideAllSlotButton, SCRIPT_VARARGS, NULL},
			{"ShowRequirementSign", wndMgrShowRequirementSign, SCRIPT_VARARGS, NULL},
			{"HideRequirementSign", wndMgrHideRequirementSign, SCRIPT_VARARGS, NULL},
			{"RefreshSlot", wndMgrRefreshSlot, SCRIPT_VARARGS, NULL},
			{"SetUseMode", wndMgrSetUseMode, SCRIPT_VARARGS, NULL},
			{"SetUsableItem", wndMgrSetUsableItem, SCRIPT_VARARGS, NULL},

			{"SelectSlot", wndMgrSelectSlot, SCRIPT_VARARGS, NULL},
			{"ClearSelected", wndMgrClearSelected, SCRIPT_VARARGS, NULL},
			{"GetSelectedSlotCount", wndMgrGetSelectedSlotCount, SCRIPT_VARARGS, NULL},
			{"GetSelectedSlotNumber", wndMgrGetSelectedSlotNumber, SCRIPT_VARARGS, NULL},
			{"IsSelectedSlot", wndMgrIsSelectedSlot, SCRIPT_VARARGS, NULL},
			{"GetSlotCount", wndMgrGetSlotCount, SCRIPT_VARARGS, NULL},
			{"LockSlot", wndMgrLockSlot, SCRIPT_VARARGS, NULL},
			{"UnlockSlot", wndMgrUnlockSlot, SCRIPT_VARARGS, NULL},

			// Bar
			{"SetColor", wndBarSetColor, SCRIPT_VARARGS, NULL},

			// TextLine
			{"SetMax", wndTextSetMax, SCRIPT_VARARGS, NULL},
			{"SetHorizontalAlign", wndTextSetHorizontalAlign, SCRIPT_VARARGS, NULL},
			{"SetVerticalAlign", wndTextSetVerticalAlign, SCRIPT_VARARGS, NULL},
			{"SetSecret", wndTextSetSecret, SCRIPT_VARARGS, NULL},
			{"SetOutline", wndTextSetOutline, SCRIPT_VARARGS, NULL},
			{"SetFeather", wndTextSetFeather, SCRIPT_VARARGS, NULL},
			{"SetMultiLine", wndTextSetMultiLine, SCRIPT_VARARGS, NULL},
			{"SetText", wndTextSetText, SCRIPT_VARARGS, NULL},
			{"SetFontName", wndTextSetFontName, SCRIPT_VARARGS, NULL},
			{"SetFontColor", wndTextSetFontColor, SCRIPT_VARARGS, NULL},
			{"SetLimitWidth", wndTextSetLimitWidth, SCRIPT_VARARGS, NULL},
			{"GetText", wndTextGetText, SCRIPT_VARARGS, NULL},
			{"GetTextSize", wndTextGetTextSize, SCRIPT_VARARGS, NULL},
			{"ShowCursor", wndTextShowCursor, SCRIPT_VARARGS, NULL},
			{"HideCursor", wndTextHideCursor, SCRIPT_VARARGS, NULL},
			{"GetCursorPosition", wndTextGetCursorPosition, SCRIPT_VARARGS, NULL},
			// NumberLine
			{"SetNumber", wndNumberSetNumber, SCRIPT_VARARGS, NULL},
			{"SetNumberHorizontalAlignCenter", wndNumberSetNumberHorizontalAlignCenter, SCRIPT_VARARGS, NULL},
			{"SetNumberHorizontalAlignRight", wndNumberSetNumberHorizontalAlignRight, SCRIPT_VARARGS, NULL},
			{"SetPath", wndNumberSetPath, SCRIPT_VARARGS, NULL},

			// ImageBox
			{"MarkBox_SetImage", wndMarkBox_SetImage, SCRIPT_VARARGS, NULL},
			{"MarkBox_SetImageFilename", wndMarkBox_SetImageFilename, SCRIPT_VARARGS, NULL},
			{"MarkBox_Load", wndMarkBox_Load, SCRIPT_VARARGS, NULL},
			{"MarkBox_SetIndex", wndMarkBox_SetIndex, SCRIPT_VARARGS, NULL},
			{"MarkBox_SetScale", wndMarkBox_SetScale, SCRIPT_VARARGS, NULL},
			{"MarkBox_SetDiffuseColor", wndMarkBox_SetDiffuseColor, SCRIPT_VARARGS, NULL},

			// ImageBox
			{"LoadImage", wndImageLoadImage, SCRIPT_VARARGS, NULL},
			{"SetDiffuseColor", wndImageSetDiffuseColor, SCRIPT_VARARGS, NULL},
			{"GetWidth", wndImageGetWidth, SCRIPT_VARARGS, NULL},
			{"GetHeight", wndImageGetHeight, SCRIPT_VARARGS, NULL},
			// ExpandedImageBox
			{"SetScale", wndImageSetScale, SCRIPT_VARARGS, NULL},
			{"SetOrigin", wndImageSetOrigin, SCRIPT_VARARGS, NULL},
			{"SetRotation", wndImageSetRotation, SCRIPT_VARARGS, NULL},
			{"SetRenderingRect", wndImageSetRenderingRect, SCRIPT_VARARGS, NULL},
			{"SetRenderingMode", wndImageSetRenderingMode, SCRIPT_VARARGS, NULL},
			// AniImageBox
			{"SetDelay", wndImageSetDelay, SCRIPT_VARARGS, NULL},
			{"AppendImage", wndImageAppendImage, SCRIPT_VARARGS, NULL},

			// Button
			{"SetUpVisual", wndButtonSetUpVisual, SCRIPT_VARARGS, NULL},
			{"SetOverVisual", wndButtonSetOverVisual, SCRIPT_VARARGS, NULL},
			{"SetDownVisual", wndButtonSetDownVisual, SCRIPT_VARARGS, NULL},
			{"SetDisableVisual", wndButtonSetDisableVisual, SCRIPT_VARARGS, NULL},
			{"GetUpVisualFileName", wndButtonGetUpVisualFileName, SCRIPT_VARARGS, NULL},
			{"GetOverVisualFileName", wndButtonGetOverVisualFileName, SCRIPT_VARARGS, NULL},
			{"GetDownVisualFileName", wndButtonGetDownVisualFileName, SCRIPT_VARARGS, NULL},
			{"Flash", wndButtonFlash, SCRIPT_VARARGS, NULL},
			{"Enable", wndButtonEnable, SCRIPT_VARARGS, NULL},
			{"Disable", wndButtonDisable, SCRIPT_VARARGS, NULL},
			{"Down", wndButtonDown, SCRIPT_VARARGS, NULL},
			{"SetUp", wndButtonSetUp, SCRIPT_VARARGS, NULL},
			{"IsDown", wndButtonIsDown, SCRIPT_VARARGS, NULL},

			// DragButton
			{"SetRestrictMovementArea", wndButtonSetRestrictMovementArea, SCRIPT_VARARGS, NULL},

			// For Debug
			{"SetOutlineFlag", wndMgrSetOutlineFlag, SCRIPT_VARARGS, NULL},
			{"ShowOverInWindowName", wndMgrShowOverInWindowName, SCRIPT_VARARGS, NULL},

			{NULL, NULL, 0, NULL},
		};

	ScriptObject* poModule = ScriptModule_Create("wndMgr", s_methods);

	// 하나의 딕셔너리에 너무 많은 Function이 포함 되는 것 같아 이런식으로 딕셔너리를 나누는 것을 고려 중 - [levites]
	//	ScriptObject * poMgrModule = ScriptModule_Create("wndMgr", s_methods);
	//	ScriptObject * poTextModule = ScriptModule_Create("wndText", s_methods);
	//	ScriptObject * poSlotModule = ScriptModule_Create("wndSlot", s_methods);

	ScriptModule_AddIntConstant(poModule, "SLOT_STYLE_NONE", UI::SLOT_STYLE_NONE);
	ScriptModule_AddIntConstant(poModule, "SLOT_STYLE_PICK_UP", UI::SLOT_STYLE_PICK_UP);
	ScriptModule_AddIntConstant(poModule, "SLOT_STYLE_SELECT", UI::SLOT_STYLE_SELECT);

	ScriptModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_LEFT", CGraphicTextInstance::HORIZONTAL_ALIGN_LEFT);
	ScriptModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_RIGHT", CGraphicTextInstance::HORIZONTAL_ALIGN_RIGHT);
	ScriptModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_CENTER", CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
	ScriptModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_TOP", CGraphicTextInstance::VERTICAL_ALIGN_TOP);
	ScriptModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_BOTTOM", CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	ScriptModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_CENTER", CGraphicTextInstance::VERTICAL_ALIGN_CENTER);

	ScriptModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_LEFT", UI::CWindow::HORIZONTAL_ALIGN_LEFT);
	ScriptModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_CENTER", UI::CWindow::HORIZONTAL_ALIGN_CENTER);
	ScriptModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_RIGHT", UI::CWindow::HORIZONTAL_ALIGN_RIGHT);
	ScriptModule_AddIntConstant(poModule, "VERTICAL_ALIGN_TOP", UI::CWindow::VERTICAL_ALIGN_TOP);
	ScriptModule_AddIntConstant(poModule, "VERTICAL_ALIGN_CENTER", UI::CWindow::VERTICAL_ALIGN_CENTER);
	ScriptModule_AddIntConstant(poModule, "VERTICAL_ALIGN_BOTTOM", UI::CWindow::VERTICAL_ALIGN_BOTTOM);

	ScriptModule_AddIntConstant(poModule, "RENDERING_MODE_MODULATE", CGraphicExpandedImageInstance::RENDERING_MODE_MODULATE);
}
