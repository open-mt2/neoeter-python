#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Python/Bindings/PythonWindow.h>
#include <Neoeter/Python/Bindings/PythonSlotWindow.h>
#include <Neoeter/Python/Bindings/PythonGridSlotWindow.h>

#include "WidgetModule.h"

#include <vector>

bool PyTuple_GetWindow(PyObject* poArgs, int pos, UI::CWindow** ppRetWindow)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetHandle(poArgs, pos, &pWindow))
		return false;
	if (!pWindow)
		return false;

	*ppRetWindow = pWindow;
	return true;
}

typedef const PyMethodDef* (*TModuleMethods)(uint32_t*);

static const TModuleMethods s_moduleMethods[] =
	{
		WindowManagerModuleMethods,
		WindowModuleMethods,
		SlotWindowModuleMethods,
		TextLineModuleMethods,
		NumberLineModuleMethods,
		ImageBoxModuleMethods,
		ButtonModuleMethods,
};

void initwndMgr()
{
	// A PyCFunction points at its PyMethodDef row, so the assembled array must
	// outlive the module dictionary.
	static std::vector<PyMethodDef> s_methodList;
	s_methodList.clear();

	for (uint32_t i = 0; i < sizeof(s_moduleMethods) / sizeof(s_moduleMethods[0]); ++i)
	{
		uint32_t uCount = 0;
		const PyMethodDef* pMethods = s_moduleMethods[i](&uCount);
		s_methodList.insert(s_methodList.end(), pMethods, pMethods + uCount);
	}

	PyMethodDef terminator = {NULL, NULL, 0, NULL};
	s_methodList.push_back(terminator);

	PyObject* poModule = Py_InitModule("wndMgr", &s_methodList[0]);

	PyModule_AddIntConstant(poModule, "SLOT_STYLE_NONE", UI::SLOT_STYLE_NONE);
	PyModule_AddIntConstant(poModule, "SLOT_STYLE_PICK_UP", UI::SLOT_STYLE_PICK_UP);
	PyModule_AddIntConstant(poModule, "SLOT_STYLE_SELECT", UI::SLOT_STYLE_SELECT);

	PyModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_LEFT", CGraphicTextInstance::HORIZONTAL_ALIGN_LEFT);
	PyModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_RIGHT", CGraphicTextInstance::HORIZONTAL_ALIGN_RIGHT);
	PyModule_AddIntConstant(poModule, "TEXT_HORIZONTAL_ALIGN_CENTER", CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
	PyModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_TOP", CGraphicTextInstance::VERTICAL_ALIGN_TOP);
	PyModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_BOTTOM", CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	PyModule_AddIntConstant(poModule, "TEXT_VERTICAL_ALIGN_CENTER", CGraphicTextInstance::VERTICAL_ALIGN_CENTER);

	PyModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_LEFT", UI::CWindow::HORIZONTAL_ALIGN_LEFT);
	PyModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_CENTER", UI::CWindow::HORIZONTAL_ALIGN_CENTER);
	PyModule_AddIntConstant(poModule, "HORIZONTAL_ALIGN_RIGHT", UI::CWindow::HORIZONTAL_ALIGN_RIGHT);
	PyModule_AddIntConstant(poModule, "VERTICAL_ALIGN_TOP", UI::CWindow::VERTICAL_ALIGN_TOP);
	PyModule_AddIntConstant(poModule, "VERTICAL_ALIGN_CENTER", UI::CWindow::VERTICAL_ALIGN_CENTER);
	PyModule_AddIntConstant(poModule, "VERTICAL_ALIGN_BOTTOM", UI::CWindow::VERTICAL_ALIGN_BOTTOM);

	PyModule_AddIntConstant(poModule, "RENDERING_MODE_MODULATE", CGraphicExpandedImageInstance::RENDERING_MODE_MODULATE);
}
