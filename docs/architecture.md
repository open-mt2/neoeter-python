# Architecture — Neoeter Python

## Role

Two libraries that together make gameplay code (`bin/root/*.py`) run inside the
client:

| Package | Responsibility |
|---|---|
| `ScriptLib` | owns the interpreter: `Py_Initialize`/`Py_Finalize`, `RunFile`, `RunLine`, trace hook, `dbg`/`time`/`math`, error text |
| `EterPythonLib` | typed Python wrappers for the renderer's UI objects: `wndMgr`, `grpImage`, `grpText`, `grpThing`, `wndSlot`, `wndText` |

It does not own the game modules. `player`, `item`, `skill`, `chrmgr`, `quest`,
… live in `client/src/UserInterface` and register themselves through
`Py_InitModule` after the interpreter is up; that is the seam that keeps the
bridge a boundary instead of a monolith.

## Host contract

Any script host — Python today, C# in the future — must do exactly these things
in this order:

1. **Start** after the engine device exists and before the first frame.
2. **Register modules** by name (`player`, `item`, …), each a set of callable
   symbols. Name collisions are errors; a module is owned by exactly one host.
3. **Run the boot script** (`root/uibla.py` and friends) on the main thread.
4. **Pump per frame**: call the host's update hook on the same thread, without
   holding engine locks across the call.
5. **Shut down** before the device is destroyed; release all host objects.

Errors never cross the boundary as exceptions: the host converts them to a
status + message (the C ABI does this with `neoeter_result`,
`../neoeter/docs/abi.md`).

## Version policy

CPython **2.7** is deliberate (`D3`): the content and the 38 existing modules are
2.7 code, and the Windows build vendors PSF's `python27.dll` + a `dlltool`
import library. This repository is the only place that knows about `Python.h`.

A second host does not change that: `neoeter-csharp` is a sibling repository
that consumes the same engine and registers the same module names. The C#
integration plan is in `../../neoeter/docs/scripting-hosts.md`.

## Tests that keep the boundary honest

- headless interpreter boot (`TA.6`);
- API-surface snapshots for `ScriptLib`, `EterPythonLib` and `client`,
  hashed in `golden/api.sha256`;
- the full client suite (`49` CTest cases) after the move.

Any host that claims to replace a Python module must produce the same
snapshot before the Python module is removed.
