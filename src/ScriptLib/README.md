# ScriptLib (`pkg_scriptlib`)

[![ScriptLib CI](https://github.com/open-mt2/pkg_scriptlib/actions/workflows/ci.yml/badge.svg)](https://github.com/open-mt2/pkg_scriptlib/actions)

`ScriptLib` is the Python 2.7 scripting engine integration and marshaling bridge of the OpenMT2 client (`CPythonLauncher`, `PythonUtils`, `PythonMarshal`, `dbg` debug module, `CPythonResource`).

## Architecture & Linux Porting Notes

- **Python 2.7 Embedded Runtime & C++17 Conformance**:
  - Embedded Python 2.7 runtime initialization with non-interactive flag (`Py_NoSiteFlag = 1`) to prevent external dependency failures during early bootstrap.
  - Resolved C++17 compatibility with legacy Python 2.7 headers by suppressing invalid `register` storage class specifier warnings/errors (`-Wno-register`).
  - Adjusted 64-bit buffer length types (`Py_ssize_t` replacing legacy 32-bit `int` in `PyObject_AsCharBuffer`).
- **Decoupled Architectural Layering**:
  - Eliminated cyclic dependency on unported higher-tier gameplay modules (`GameLib`) within `CPythonResource::Destroy()`.
  - Introduced dynamic destroy handler registration (`CPythonResource::RegisterDestroyHandler`) allowing higher-level modules (`GameLib`, `UserInterface`) to register cleanup callbacks at runtime without polluting lower-level library dependencies.
- **Python-C++ Marshaling & Utilities**:
  - Full suite of type extraction utilities (`PyTuple_GetInteger`, `PyTuple_GetString`, `PyTuple_GetFloat`, `PyTuple_GetBoolean`, `PyTuple_GetByte`).
  - Class member function invocation (`PyCallClassMemberFunc`).
  - Python marshaling support (`_PyMarshal_ReadLongFromFile`).
  - In-engine Python debugger module `dbg` (`dbg.Trace`, `dbg.Tracen`, `dbg.LogBox`, `dbg.RegisterExceptionString`).

## Directory Layout (Pitchfork Standard)

- `include/ScriptLib/` — Public headers (`PythonLauncher.h`, `PythonUtils.h`, `PythonMarshal.h`, `Resource.h`, `StdAfx.h`)
- `include/Platform/` — Bundled cross-platform compatibility headers (`Platform.h`, `DirectXMathCompat.h`)
- `include/python2.7/` — Bundled Python 2.7 C-API headers
- `src/` — Implementation files (`PythonLauncher.cpp`, `PythonUtils.cpp`, `PythonMarshal.cpp`, `PythonDebugModule.cpp`, `Resource.cpp`, `StdAfx.cpp`)
- `tests/` — CTest unit & smoke test suite (`test_scriptlib.cpp`)

## Building & Testing Standalone

```bash
cmake -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

The embedded Python 2.7 surface is pinned by `test_python_scriptlib_api`
(`tests/data/python_api_scriptlib.txt`). After adding, removing or renaming a
binding, regenerate the golden file deliberately:

```bash
OPENMT2_UPDATE_PYTHON_API=1 ctest --test-dir build -R python --output-on-failure
```
