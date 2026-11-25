#pragma once

#include <Python.h>

#include <Neoeter/Script/Script.h>
#include <Neoeter/Script/ScriptBackend.h>

#include <deque>
#include <string>
#include <unordered_map>

// Exposes the runtime-neutral native modules (Neoeter/Script) to the embedded
// Python 2.7 interpreter and represents Python objects as ScriptObjects.
//
// Python objects that are not plain values (instances, functions, ...) become
// identity-stable wrappers holding a borrowed reference, so engine code that
// stores a handler without Script_INCREF behaves exactly like it did with a
// borrowed PyObject*. Wrappers are released through a weakref callback when
// the Python object dies.
class CPythonScriptBackend : public ScriptBackend, public ScriptModuleListener
{
	public:
		static CPythonScriptBackend& Instance();

		// Call after Py_Initialize / before Py_Finalize.
		void Install();
		void Uninstall();
		bool IsInstalled() const { return m_installed; }

		// New references; both return nullptr only for a nullptr input.
		PyObject* ToPython(ScriptObject* object);
		ScriptObject* FromPython(PyObject* object);

		// Raises the pending script error (if any) as a Python exception.
		static bool RaisePendingError();

		// ScriptBackend
		const char* Name() const override { return "python"; }
		void IncRef(ScriptObject* object) override;
		void DecRef(ScriptObject* object) override;
		bool HasAttr(ScriptObject* object, const char* name) override;
		ScriptCallStatus CallMethod(ScriptObject* object, const char* name, ScriptObject* args, ScriptObject** result) override;
		std::string Repr(ScriptObject* object) override;
		bool RunFile(const char* path) override;

		// ScriptModuleListener
		void OnModuleCreated(ScriptModuleData& module) override;
		void OnModuleMethodsAdded(ScriptModuleData& module, std::size_t firstNewMethod) override;
		void OnModuleConstant(ScriptModuleData& module, const std::string& name, ScriptObject* value) override;

	private:
		struct Binding
		{
				PyMethodDef pythonDef;
				ScriptMethodDef scriptDef;
				std::string name;
		};

		struct WrapperEntry
		{
				ScriptObject* wrapper = nullptr;
				PyObject* weakref = nullptr;
		};

		CPythonScriptBackend() = default;

		PyObject* EnsurePythonModule(ScriptModuleData& module);
		void AddFunction(PyObject* pythonModule, const ScriptMethodDef& method);
		ScriptObject* Wrap(PyObject* object);
		void OnWeakrefDead(PyObject* weakref);

		static PyObject* Trampoline(PyObject* self, PyObject* args);
		static PyObject* WeakrefCallback(PyObject* self, PyObject* weakref);

		bool m_installed = false;
		std::deque<Binding> m_bindings;
		std::unordered_map<PyObject*, WrapperEntry> m_wrappers;
		std::unordered_map<PyObject*, PyObject*> m_weakrefKeys;
		PyObject* m_weakrefCallback = nullptr;
};
