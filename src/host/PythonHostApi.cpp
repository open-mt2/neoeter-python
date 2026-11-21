#include <Neoeter/Python/Host/PythonHostApi.h>

#include <Neoeter/Python/Host/StdAfx.h>

#include <cstring>
#include <string>

struct neoeter_python_host
{
	CPythonLauncher* launcher = nullptr;
	std::string lastError;
	bool loaded = false;
};

namespace
{
	void SetError(neoeter_python_host* host, const char* message)
	{
		host->lastError = message ? message : "";
	}

	std::string EscapePythonString(const char* value)
	{
		std::string escaped;

		if (!value)
			return escaped;

		for (const char* it = value; *it != '\0'; ++it)
		{
			if (*it == '\\' || *it == '"')
				escaped += '\\';
			escaped += *it;
		}

		return escaped;
	}

	bool RunDebugFlag(neoeter_python_host* host, int32_t debug)
	{
		return host->launcher->RunLine(debug ? "__DEBUG__ = 1" : "__DEBUG__ = 0");
	}

	bool RunCommandLine(neoeter_python_host* host, const char* commandLine)
	{
		const std::string line = "__COMMAND_LINE__ = \"" + EscapePythonString(commandLine) + "\"";
		return host->launcher->RunLine(line.c_str());
	}

	void CaptureHostError(neoeter_python_host* host, const char* prefix)
	{
		host->lastError = prefix ? prefix : "";
		const char* error = host->launcher->GetError();
		if (error && error[0] != '\0')
		{
			host->lastError += ": ";
			host->lastError += error;
		}
	}
}

extern "C"
{
	neoeter_python_result neoeter_python_host_create(neoeter_python_host** out)
	{
		if (!out)
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		*out = nullptr;

		neoeter_python_host* host = new neoeter_python_host();
		host->launcher = new CPythonLauncher();

		if (!host->launcher->Create("eter.python"))
		{
			SetError(host, "the CPython launcher did not start");
			neoeter_python_host_destroy(host);
			return NEOETER_PYTHON_RUNTIME_ERROR;
		}

		*out = host;
		return NEOETER_PYTHON_OK;
	}

	neoeter_python_result neoeter_python_host_load(neoeter_python_host* host, const neoeter_python_pack* pack)
	{
		if (!host || !host->launcher || !pack)
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		if (pack->struct_size < sizeof(neoeter_python_pack))
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		if (pack->abi_version != NEOETER_PYTHON_HOST_ABI_VERSION)
			return NEOETER_PYTHON_VERSION_MISMATCH;

		if (!pack->entry || pack->entry[0] == '\0')
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		if (pack->module_count > 0 && !pack->modules)
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		for (uint32_t i = 0; i < pack->module_count; ++i)
		{
			if (!pack->modules[i].register_module)
				return NEOETER_PYTHON_INVALID_ARGUMENT;
		}

		if (host->loaded)
		{
			SetError(host, "the host already has a pack loaded");
			return NEOETER_PYTHON_INVALID_ARGUMENT;
		}

		if (!RunDebugFlag(host, pack->debug))
		{
			CaptureHostError(host, "could not set __DEBUG__");
			return NEOETER_PYTHON_SCRIPT_ERROR;
		}

		if (!RunCommandLine(host, pack->command_line))
		{
			CaptureHostError(host, "could not set __COMMAND_LINE__");
			return NEOETER_PYTHON_SCRIPT_ERROR;
		}

		for (uint32_t i = 0; i < pack->module_count; ++i)
			pack->modules[i].register_module();

		host->loaded = true;

		if (!host->launcher->RunFile(pack->entry))
		{
			CaptureHostError(host, "the pack entry failed");
			return NEOETER_PYTHON_SCRIPT_ERROR;
		}

		return NEOETER_PYTHON_OK;
	}

	neoeter_python_result neoeter_python_host_unload(neoeter_python_host* host)
	{
		if (!host)
			return NEOETER_PYTHON_INVALID_ARGUMENT;

		if (host->loaded && host->launcher)
		{
			host->launcher->Clear();
			host->loaded = false;
		}

		return NEOETER_PYTHON_OK;
	}

	void neoeter_python_host_destroy(neoeter_python_host* host)
	{
		if (!host)
			return;

		if (host->loaded && host->launcher)
			host->launcher->Clear();

		delete host->launcher;
		delete host;
	}

	const char* neoeter_python_host_last_error(const neoeter_python_host* host)
	{
		if (!host)
			return "";

		return host->lastError.c_str();
	}
}
