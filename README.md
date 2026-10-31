# Neoeter Python

CPython 2.7 host and Python bindings for the OpenMT2 client.

**Status:** scaffold. The `pkg_*` sources are not imported yet (`TB.2`).

| Path | Package | Role target |
|---|---|---|
| `src/ScriptLib/` | `pkg_scriptlib` | `NeoeterPython::Script` |
| `src/EterPythonLib/` | `pkg_eterpythonlib` | `NeoeterPython::Bindings` |

`layout.map` records the old repository → path mapping used by
`devkit/scripts/import-repo.sh`. See `docs/architecture.md`.
