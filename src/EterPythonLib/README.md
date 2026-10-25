# EterPythonLib (`pkg_eterpythonlib`)

[![EterPythonLib CI](https://github.com/open-mt2/pkg_eterpythonlib/actions/workflows/ci.yml/badge.svg)](https://github.com/open-mt2/pkg_eterpythonlib/actions)

`EterPythonLib` provides the high-level Python C extension bindings for 2D/3D graphics, user interface window hierarchy (`wndMgr`), widgets (`CWindow`, `CButton`, `CTextLine`, `CSlotWindow`, `CGridSlotWindow`), and graphics instances (`grp`, `grpImage`, `grpText`, `grpThing`).

## Architecture & Linux Porting Notes

- **64-Bit Address Safe Python C-API Integration**:
  - Replaced legacy 32-bit pointer truncation in handle conversions (`Py_BuildValue("i", pWindow)` / `PyTuple_GetInteger`) with 64-bit address-safe integer representations (`Py_BuildValue("l", (intptr_t)pWindow)` and `PyTuple_GetLong`).
  - Audited and updated all pointer handle decoders across `wndMgr`, `grpImage`, `grpText`, `grpThing`, and `grpTextBar`.
- **Cross-Platform Compatibility**:
  - Replaced Windows-specific Shell API (`SHGetSpecialFolderPath`) in screenshot generation (`grpSaveScreenShot`) with POSIX standard directory management (`$HOME/.metin2/screenshots/`).
  - Added compatibility stubs and types (`D3DGAMMARAMP`, `D3DSURFACE_DESC`, `GetBackBuffer`, `SetGammaRamp`) to `DirectXMathCompat.h`.
  - Added global `timeGetTime()` helper based on monotonic clock to `Platform.h`.
- **Python <-> C++ Bi-Directional Integration Testing**:
  - Implemented unit tests validating window creation, property synchronization, parent-child nesting hierarchy, specialized control behaviors (`CButton`, `CTextLine`), C++ event dispatch to Python event handlers (`OnMouseLeftButtonDown`, `OnMoveWindow`), and graphic color operations (`grp.GenerateColor`).

## Directory Layout (Pitchfork Standard)

- `include/EterPythonLib/` — Public headers (`PythonGraphic.h`, `PythonGridSlotWindow.h`, `PythonSlotWindow.h`, `PythonWindow.h`, `PythonWindowManager.h`, `StdAfx.h`)
- `include/Platform/` — Bundled cross-platform compatibility headers (`Platform.h`, `DirectXMathCompat.h`)
- `include/python2.7/` — Bundled Python 2.7 C-API headers
- `src/` — Implementation files (`PythonGraphic.cpp`, `PythonGraphicImageModule.cpp`, `PythonGraphicModule.cpp`, `PythonGraphicTextModule.cpp`, `PythonGraphicThingModule.cpp`, `PythonGridSlotWindow.cpp`, `PythonSlotWindow.cpp`, `PythonWindow.cpp`, `PythonWindowManager.cpp`, `PythonWindowManagerModule.cpp`, `StdAfx.cpp`)
- `tests/` — CTest unit & smoke test suite (`test_eterpythonlib.cpp`)

## Building & Testing Standalone

```bash
cmake -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```
