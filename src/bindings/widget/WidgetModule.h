#pragma once

#include <Neoeter/Python/Bindings/StdAfx.h>

bool PyTuple_GetWindow(PyObject* poArgs, int pos, UI::CWindow** ppRetWindow);

const PyMethodDef* WindowManagerModuleMethods(uint32_t* puCount);
const PyMethodDef* WindowModuleMethods(uint32_t* puCount);
const PyMethodDef* SlotWindowModuleMethods(uint32_t* puCount);
const PyMethodDef* TextLineModuleMethods(uint32_t* puCount);
const PyMethodDef* NumberLineModuleMethods(uint32_t* puCount);
const PyMethodDef* ImageBoxModuleMethods(uint32_t* puCount);
const PyMethodDef* ButtonModuleMethods(uint32_t* puCount);
