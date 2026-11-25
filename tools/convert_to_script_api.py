#!/usr/bin/env python3
"""Convert CPython-helper based bindings to the runtime-neutral script API.

Usage: convert_to_script_api.py FILE...

The neutral API (Neoeter/Script/Script.h) mirrors the historic helpers name
for name, so most of the work is a token rename. Constructs without a direct
equivalent are reported with file:line so they can be fixed by hand.
Files are rewritten in place; run it on a clean working tree.
"""

import re
import sys

# Order matters: longer / more specific names first.
RENAMES = [
    (r"\bPyCallClassMemberFunc_ByPyString\b", "Script_CallMethod"),
    (r"\bPyCallClassMemberFunc\b", "Script_CallMethod"),
    (r"\bPyMethodDef\b", "ScriptMethodDef"),
    (r"\bMETH_VARARGS\b", "SCRIPT_VARARGS"),
    (r"\bPy_InitModule\b", "ScriptModule_Create"),
    (r"\bPyModule_Add(IntConstant|StringConstant|Object)\b", r"ScriptModule_Add\1"),
    (r"\bPy_BuildValue\b", "Script_BuildValue"),
    (r"\bPy_Build(None|Exception|EmptyTuple|Handle)\b", r"Script_Build\1"),
    (r"\bPy_BadArgument\b", "Script_BadArgument"),
    (r"\bPyTuple_(Get\w*|Size|Check|New|SetItem)\b", r"ScriptTuple_\1"),
    (r"\bPyList_(New|Append|Check)\b", r"ScriptList_\1"),
    (r"\bPyDict_(Check|GetItemString|SetItemString|SetItem|Next|New)\b", r"ScriptDict_\1"),
    (r"\bPyString_(Check|AsString)\b", r"ScriptString_\1"),
    (r"\bPyString_FromStringAndSize\b", "ScriptString_NewSize"),
    (r"\bPyString_FromString\b", "ScriptString_New"),
    (r"\bPy(?:Int|Long)_AsLong\b", "Script_AsLongLong"),
    (r"\bPyFloat_AsDouble\b", "Script_AsDouble"),
    (r"\bPyObject_IsTrue\b", "Script_IsTrue"),
    (r"\bPyObject_HasAttrString\b", "Script_HasAttr"),
    (r"\bPyErr_SetString\(\s*PyExc_(\w+)\s*,", r"ScriptErr_SetString(ScriptErrorType::\1,"),
    (r"\bPyErr_(Clear|Occurred)\b", r"ScriptErr_\1"),
    (r"\bPy_(X?)(INC|DEC)REF\b", r"Script_\1\2REF"),
    (r"\bPy_ssize_t\b", "long"),
    (r"\bPyObject\b", "ScriptObject"),
    # Py_BuildValue("None") never meant None; it built garbage.
    (r'Script_BuildValue\("None"\)', "Script_BuildNone()"),
]

LEFTOVER = re.compile(r"\b(Py[A-Z]\w*|Py_\w+|_Py\w+|PyExc_\w+)\b")


def convert(path):
    with open(path, encoding="utf-8", errors="surrogateescape") as handle:
        text = handle.read()

    original = text
    for pattern, replacement in RENAMES:
        text = re.sub(pattern, replacement, text)

    if text != original:
        with open(path, "w", encoding="utf-8", errors="surrogateescape") as handle:
            handle.write(text)

    leftovers = 0
    for number, line in enumerate(text.splitlines(), 1):
        stripped = line.strip()
        if stripped.startswith("//"):
            continue
        for match in LEFTOVER.finditer(line):
            print(f"{path}:{number}: manual conversion needed: {match.group(1)}")
            leftovers += 1
    return leftovers


def main(paths):
    if not paths:
        print(__doc__)
        return 2
    leftovers = sum(convert(path) for path in paths)
    return 1 if leftovers else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
