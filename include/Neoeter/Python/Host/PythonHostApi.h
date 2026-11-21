#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define NEOETER_PYTHON_HOST_ABI_VERSION 1u

	typedef enum neoeter_python_result
	{
		NEOETER_PYTHON_OK = 0,
		NEOETER_PYTHON_INVALID_ARGUMENT = 1,
		NEOETER_PYTHON_VERSION_MISMATCH = 2,
		NEOETER_PYTHON_RUNTIME_ERROR = 3,
		NEOETER_PYTHON_SCRIPT_ERROR = 4,
	} neoeter_python_result;

	typedef struct neoeter_python_host neoeter_python_host;

	typedef void (*neoeter_python_register_module)(void);

	typedef struct neoeter_python_module
	{
			const char* name;
			neoeter_python_register_module register_module;
	} neoeter_python_module;

	typedef struct neoeter_python_pack
	{
			uint32_t struct_size;
			uint32_t abi_version;
			const char* pack_name;
			const char* entry;
			const char* command_line;
			int32_t debug;
			const neoeter_python_module* modules;
			uint32_t module_count;
	} neoeter_python_pack;

	neoeter_python_result neoeter_python_host_create(neoeter_python_host** out);
	neoeter_python_result neoeter_python_host_load(neoeter_python_host* host, const neoeter_python_pack* pack);
	neoeter_python_result neoeter_python_host_unload(neoeter_python_host* host);
	void neoeter_python_host_destroy(neoeter_python_host* host);
	const char* neoeter_python_host_last_error(const neoeter_python_host* host);

#ifdef __cplusplus
}
#endif
