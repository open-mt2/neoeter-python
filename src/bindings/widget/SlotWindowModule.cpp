#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

PyObject* wndMgrAppendSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();

	int ixPosition;
	if (!PyTuple_GetInteger(poArgs, 2, &ixPosition))
		return Py_BuildException();

	int iyPosition;
	if (!PyTuple_GetInteger(poArgs, 3, &iyPosition))
		return Py_BuildException();

	int ixCellSize;
	if (!PyTuple_GetInteger(poArgs, 4, &ixCellSize))
		return Py_BuildException();

	int iyCellSize;
	if (!PyTuple_GetInteger(poArgs, 5, &iyCellSize))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->AppendSlot(iIndex, ixPosition, iyPosition, ixCellSize, iyCellSize);

	return Py_BuildNone();
}

PyObject* wndMgrArrangeSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iStartIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iStartIndex))
		return Py_BuildException();

	int ixCellCount;
	if (!PyTuple_GetInteger(poArgs, 2, &ixCellCount))
		return Py_BuildException();

	int iyCellCount;
	if (!PyTuple_GetInteger(poArgs, 3, &iyCellCount))
		return Py_BuildException();

	int ixCellSize;
	if (!PyTuple_GetInteger(poArgs, 4, &ixCellSize))
		return Py_BuildException();

	int iyCellSize;
	if (!PyTuple_GetInteger(poArgs, 5, &iyCellSize))
		return Py_BuildException();

	int ixBlank;
	if (!PyTuple_GetInteger(poArgs, 6, &ixBlank))
		return Py_BuildException();

	int iyBlank;
	if (!PyTuple_GetInteger(poArgs, 7, &iyBlank))
		return Py_BuildException();

	if (!pWin->IsType(UI::CGridSlotWindow::Type()))
	{
		TraceError("wndMgr.ArrangeSlot : not a grid window");
		return Py_BuildException();
	}

	UI::CGridSlotWindow* pGridSlotWin = (UI::CGridSlotWindow*)pWin;
	pGridSlotWin->ArrangeGridSlot(iStartIndex, ixCellCount, iyCellCount, ixCellSize, iyCellSize, ixBlank, iyBlank);

	return Py_BuildNone();
}

PyObject* wndMgrSetSlotBaseImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	char* szFileName;
	if (!PyTuple_GetString(poArgs, 1, &szFileName))
		return Py_BuildException();

	float fr;
	if (!PyTuple_GetFloat(poArgs, 2, &fr))
		return Py_BuildException();
	float fg;
	if (!PyTuple_GetFloat(poArgs, 3, &fg))
		return Py_BuildException();
	float fb;
	if (!PyTuple_GetFloat(poArgs, 4, &fb))
		return Py_BuildException();
	float fa;
	if (!PyTuple_GetFloat(poArgs, 5, &fa))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
	{
		TraceError("wndMgr.ArrangeSlot : not a slot window");
		return Py_BuildException();
	}

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotBaseImage(szFileName, fr, fg, fb, fa);

	return Py_BuildNone();
}

PyObject* wndMgrSetCoverButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	char* szUpImageName;
	if (!PyTuple_GetString(poArgs, 2, &szUpImageName))
		return Py_BuildException();
	char* szOverImageName;
	if (!PyTuple_GetString(poArgs, 3, &szOverImageName))
		return Py_BuildException();
	char* szDownImageName;
	if (!PyTuple_GetString(poArgs, 4, &szDownImageName))
		return Py_BuildException();
	char* szDisableImageName;
	if (!PyTuple_GetString(poArgs, 5, &szDisableImageName))
		return Py_BuildException();

	int iLeftButtonEnable;
	if (!PyTuple_GetInteger(poArgs, 6, &iLeftButtonEnable))
		return Py_BuildException();
	int iRightButtonEnable;
	if (!PyTuple_GetInteger(poArgs, 7, &iRightButtonEnable))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->SetCoverButton(iSlotIndex, szUpImageName, szOverImageName, szDownImageName, szDisableImageName, iLeftButtonEnable, iRightButtonEnable);

	return Py_BuildNone();
}

PyObject* wndMgrEnableCoverButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->EnableCoverButton(iSlotIndex);

	return Py_BuildNone();
}

PyObject* wndMgrDisableCoverButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->DisableCoverButton(iSlotIndex);

	return Py_BuildNone();
}

PyObject* wndMgrIsDisableCoverButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	return Py_BuildValue("i", pSlotWin->IsDisableCoverButton(iSlotIndex));
}

PyObject* wndMgrSetAlwaysRenderCoverButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotIndex;
	bool bAlwaysRender = false;

	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!PyTuple_GetBoolean(poArgs, 2, &bAlwaysRender))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->SetAlwaysRenderCoverButton(iSlotIndex, bAlwaysRender);

	return Py_BuildNone();
}

PyObject* wndMgrAppendSlotButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	char* szUpImageName;
	if (!PyTuple_GetString(poArgs, 1, &szUpImageName))
		return Py_BuildException();
	char* szOverImageName;
	if (!PyTuple_GetString(poArgs, 2, &szOverImageName))
		return Py_BuildException();
	char* szDownImageName;
	if (!PyTuple_GetString(poArgs, 3, &szDownImageName))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->AppendSlotButton(szUpImageName, szOverImageName, szDownImageName);

	return Py_BuildNone();
}

PyObject* wndMgrAppendRequirementSignImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	char* szImageName;
	if (!PyTuple_GetString(poArgs, 1, &szImageName))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->AppendRequirementSignImage(szImageName);

	return Py_BuildNone();
}

PyObject* wndMgrShowSlotButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->ShowSlotButton(iSlotNumber);

	return Py_BuildNone();
}

PyObject* wndMgrHideAllSlotButton(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->HideAllSlotButton();

	return Py_BuildNone();
}

PyObject* wndMgrShowRequirementSign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->ShowRequirementSign(iSlotNumber);

	return Py_BuildNone();
}

PyObject* wndMgrHideRequirementSign(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWindow;
	pSlotWin->HideRequirementSign(iSlotNumber);

	return Py_BuildNone();
}

PyObject* wndMgrRefreshSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->RefreshSlot();

	return Py_BuildNone();
}

PyObject* wndMgrSetUseMode(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetUseMode(iFlag);

	return Py_BuildNone();
}

PyObject* wndMgrSetUsableItem(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetUsableItem(iFlag);

	return Py_BuildNone();
}

PyObject* wndMgrClearSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearSlot(iSlotIndex);

	return Py_BuildNone();
}

PyObject* wndMgrClearAllSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearAllSlot();

	return Py_BuildNone();
}

PyObject* wndMgrHasSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;

	return Py_BuildValue("i", pSlotWin->HasSlot(iSlotIndex));
}

PyObject* wndMgrSetSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iItemIndex))
		return Py_BuildException();

	int iWidth;
	if (!PyTuple_GetInteger(poArgs, 3, &iWidth))
		return Py_BuildException();

	int iHeight;
	if (!PyTuple_GetInteger(poArgs, 4, &iHeight))
		return Py_BuildException();

	CGraphicImage* pImage;
	if (!PyTuple_GetHandle(poArgs, 5, &pImage))
		return Py_BuildException();

	D3DXCOLOR diffuseColor;
	PyObject* pTuple;
	if (!PyTuple_GetObject(poArgs, 6, &pTuple))
	{
		diffuseColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		// return Py_BuildException();
	}
	else
	// get diffuse color from pTuple
	{
		if (PyTuple_Size(pTuple) != 4)
			return Py_BuildException();
		if (!PyTuple_GetFloat(pTuple, 0, &diffuseColor.r))
			return Py_BuildException();
		if (!PyTuple_GetFloat(pTuple, 1, &diffuseColor.g))
			return Py_BuildException();
		if (!PyTuple_GetFloat(pTuple, 2, &diffuseColor.b))
			return Py_BuildException();
		if (!PyTuple_GetFloat(pTuple, 3, &diffuseColor.a))
			return Py_BuildException();
	}

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlot(iSlotIndex, iItemIndex, iWidth, iHeight, pImage, diffuseColor);

	return Py_BuildNone();
}

PyObject* wndMgrSetSlotCount(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	int iCount;
	if (!PyTuple_GetInteger(poArgs, 2, &iCount))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCount(iSlotIndex, iCount);

	return Py_BuildNone();
}

PyObject* wndMgrSetSlotCountNew(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	int iGrade;
	if (!PyTuple_GetInteger(poArgs, 2, &iGrade))
		return Py_BuildException();

	int iCount;
	if (!PyTuple_GetInteger(poArgs, 3, &iCount))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCountNew(iSlotIndex, iGrade, iCount);

	return Py_BuildNone();
}

PyObject* wndMgrSetSlotCoolTime(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	float fCoolTime;
	if (!PyTuple_GetFloat(poArgs, 2, &fCoolTime))
		return Py_BuildException();

	float fElapsedTime = 0.0f;
	PyTuple_GetFloat(poArgs, 3, &fElapsedTime);

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotCoolTime(iSlotIndex, fCoolTime, fElapsedTime);

	return Py_BuildNone();
}

PyObject* wndMgrSetToggleSlot(PyObject* poSelf, PyObject* poArgs)
{
	assert(!"wndMgrSetToggleSlot - \xBB\xE7\xBF\xEB\xC7\xCF\xC1\xF6 \xBE\xCA\xB4\xC2 \xC7\xD4\xBC\xF6");
	return Py_BuildNone();
}

PyObject* wndMgrActivateSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ActivateSlot(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrDeactivateSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->DeactivateSlot(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrEnableSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->EnableSlot(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrDisableSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->DisableSlot(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrShowSlotBaseImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ShowSlotBaseImage(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrHideSlotBaseImage(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->HideSlotBaseImage(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrSetSlotType(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotType(iType);

	return Py_BuildNone();
}

PyObject* wndMgrSetSlotStyle(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iStyle;
	if (!PyTuple_GetInteger(poArgs, 1, &iStyle))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SetSlotStyle(iStyle);

	return Py_BuildNone();
}

PyObject* wndMgrSelectSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->SelectSlot(iIndex);

	return Py_BuildNone();
}

PyObject* wndMgrClearSelected(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->ClearSelected();

	return Py_BuildNone();
}

PyObject* wndMgrGetSelectedSlotCount(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Py_BuildValue("i", pSlotWin->GetSelectedSlotCount());
}

PyObject* wndMgrGetSelectedSlotNumber(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Py_BuildValue("i", pSlotWin->GetSelectedSlotNumber(iSlotNumber));
}

PyObject* wndMgrIsSelectedSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotNumber))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Py_BuildValue("i", pSlotWin->isSelectedSlot(iSlotNumber));
}

PyObject* wndMgrGetSlotCount(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	return Py_BuildValue("i", pSlotWin->GetSlotCount());
}

PyObject* wndMgrLockSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->LockSlot(iSlotIndex);
	return Py_BuildNone();
}

PyObject* wndMgrUnlockSlot(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWin;
	if (!PyTuple_GetWindow(poArgs, 0, &pWin))
		return Py_BuildException();
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
		return Py_BuildException();

	if (!pWin->IsType(UI::CSlotWindow::Type()))
		return Py_BuildException();

	UI::CSlotWindow* pSlotWin = (UI::CSlotWindow*)pWin;
	pSlotWin->UnlockSlot(iSlotIndex);
	return Py_BuildNone();
}

static PyMethodDef s_methods[] =
	{
		// Slot Window
		{"AppendSlot", wndMgrAppendSlot, METH_VARARGS, NULL},
		{"ArrangeSlot", wndMgrArrangeSlot, METH_VARARGS, NULL},
		{"ClearSlot", wndMgrClearSlot, METH_VARARGS, NULL},
		{"ClearAllSlot", wndMgrClearAllSlot, METH_VARARGS, NULL},
		{"HasSlot", wndMgrHasSlot, METH_VARARGS, NULL},
		{"SetSlot", wndMgrSetSlot, METH_VARARGS, NULL},
		{"SetSlotCount", wndMgrSetSlotCount, METH_VARARGS, NULL},
		{"SetSlotCountNew", wndMgrSetSlotCountNew, METH_VARARGS, NULL},
		{"SetSlotCoolTime", wndMgrSetSlotCoolTime, METH_VARARGS, NULL},
		{"SetToggleSlot", wndMgrSetToggleSlot, METH_VARARGS, NULL},
		{"ActivateSlot", wndMgrActivateSlot, METH_VARARGS, NULL},
		{"DeactivateSlot", wndMgrDeactivateSlot, METH_VARARGS, NULL},
		{"EnableSlot", wndMgrEnableSlot, METH_VARARGS, NULL},
		{"DisableSlot", wndMgrDisableSlot, METH_VARARGS, NULL},
		{"ShowSlotBaseImage", wndMgrShowSlotBaseImage, METH_VARARGS, NULL},
		{"HideSlotBaseImage", wndMgrHideSlotBaseImage, METH_VARARGS, NULL},
		{"SetSlotType", wndMgrSetSlotType, METH_VARARGS, NULL},
		{"SetSlotStyle", wndMgrSetSlotStyle, METH_VARARGS, NULL},
		{"SetSlotBaseImage", wndMgrSetSlotBaseImage, METH_VARARGS, NULL},
		{"SetCoverButton", wndMgrSetCoverButton, METH_VARARGS, NULL},
		{"EnableCoverButton", wndMgrEnableCoverButton, METH_VARARGS, NULL},
		{"DisableCoverButton", wndMgrDisableCoverButton, METH_VARARGS, NULL},
		{"IsDisableCoverButton", wndMgrIsDisableCoverButton, METH_VARARGS, NULL},
		{"SetAlwaysRenderCoverButton", wndMgrSetAlwaysRenderCoverButton, METH_VARARGS, NULL},
		{"AppendSlotButton", wndMgrAppendSlotButton, METH_VARARGS, NULL},
		{"AppendRequirementSignImage", wndMgrAppendRequirementSignImage, METH_VARARGS, NULL},
		{"ShowSlotButton", wndMgrShowSlotButton, METH_VARARGS, NULL},
		{"HideAllSlotButton", wndMgrHideAllSlotButton, METH_VARARGS, NULL},
		{"ShowRequirementSign", wndMgrShowRequirementSign, METH_VARARGS, NULL},
		{"HideRequirementSign", wndMgrHideRequirementSign, METH_VARARGS, NULL},
		{"RefreshSlot", wndMgrRefreshSlot, METH_VARARGS, NULL},
		{"SetUseMode", wndMgrSetUseMode, METH_VARARGS, NULL},
		{"SetUsableItem", wndMgrSetUsableItem, METH_VARARGS, NULL},
		{"SelectSlot", wndMgrSelectSlot, METH_VARARGS, NULL},
		{"ClearSelected", wndMgrClearSelected, METH_VARARGS, NULL},
		{"GetSelectedSlotCount", wndMgrGetSelectedSlotCount, METH_VARARGS, NULL},
		{"GetSelectedSlotNumber", wndMgrGetSelectedSlotNumber, METH_VARARGS, NULL},
		{"IsSelectedSlot", wndMgrIsSelectedSlot, METH_VARARGS, NULL},
		{"GetSlotCount", wndMgrGetSlotCount, METH_VARARGS, NULL},
		{"LockSlot", wndMgrLockSlot, METH_VARARGS, NULL},
		{"UnlockSlot", wndMgrUnlockSlot, METH_VARARGS, NULL},

		{NULL, NULL, 0, NULL},
};

const PyMethodDef* SlotWindowModuleMethods(uint32_t* puCount)
{
	*puCount = sizeof(s_methods) / sizeof(s_methods[0]) - 1;
	return s_methods;
}
