#include <Neoeter/Python/Host/PythonHostApi.h>

#include <Neoeter/IO/EterPackManager.h>

#include <support/TestAssert.h>

#include <Python.h>

#include <cstdio>
#include <cstring>

namespace
{
	int g_registeredModules = 0;

	void CountModule()
	{
		++g_registeredModules;
	}

	neoeter_python_module g_modules[] = {
		{"first", CountModule},
		{"second", CountModule},
	};

	neoeter_python_module g_brokenModule[] = {
		{"broken", nullptr},
	};

	neoeter_python_pack MakePack(const char* entry)
	{
		neoeter_python_pack pack;
		std::memset(&pack, 0, sizeof(pack));
		pack.struct_size = sizeof(pack);
		pack.abi_version = NEOETER_PYTHON_HOST_ABI_VERSION;
		pack.pack_name = "test";
		pack.entry = entry;
		pack.command_line = "-test";
		pack.debug = 1;
		pack.modules = g_modules;
		pack.module_count = 2;
		return pack;
	}

	neoeter_python_host* CreateHost()
	{
		neoeter_python_host* host = nullptr;
		TEST_ASSERT(neoeter_python_host_create(&host) == NEOETER_PYTHON_OK);
		TEST_ASSERT(host != nullptr);
		return host;
	}
}

int main()
{
	CEterPackManager packManager;
	packManager.SetSearchMode(false);

	TEST_SECTION("version and argument validation");
	neoeter_python_host* host = CreateHost();
	TEST_ASSERT(Py_IsInitialized() != 0);

	neoeter_python_pack pack = MakePack("test_python_host_api_entry.py");

	neoeter_python_pack shortPack = pack;
	shortPack.struct_size = sizeof(uint32_t);
	TEST_ASSERT(neoeter_python_host_load(host, &shortPack) == NEOETER_PYTHON_INVALID_ARGUMENT);

	neoeter_python_pack futurePack = pack;
	futurePack.abi_version = NEOETER_PYTHON_HOST_ABI_VERSION + 1;
	TEST_ASSERT(neoeter_python_host_load(host, &futurePack) == NEOETER_PYTHON_VERSION_MISMATCH);

	neoeter_python_pack noEntry = pack;
	noEntry.entry = nullptr;
	TEST_ASSERT(neoeter_python_host_load(host, &noEntry) == NEOETER_PYTHON_INVALID_ARGUMENT);

	neoeter_python_pack noModules = pack;
	noModules.modules = nullptr;
	TEST_ASSERT(neoeter_python_host_load(host, &noModules) == NEOETER_PYTHON_INVALID_ARGUMENT);

	neoeter_python_pack brokenModule = pack;
	brokenModule.modules = g_brokenModule;
	brokenModule.module_count = 1;
	TEST_ASSERT(neoeter_python_host_load(host, &brokenModule) == NEOETER_PYTHON_INVALID_ARGUMENT);

	TEST_SECTION("entry failure");
	neoeter_python_pack missingEntry = MakePack("test_python_host_api_missing.py");
	TEST_ASSERT(neoeter_python_host_load(host, &missingEntry) == NEOETER_PYTHON_SCRIPT_ERROR);
	TEST_ASSERT(std::strlen(neoeter_python_host_last_error(host)) > 0);

	TEST_SECTION("unload");
	TEST_ASSERT(neoeter_python_host_unload(host) == NEOETER_PYTHON_OK);
	TEST_ASSERT(Py_IsInitialized() == 0);
	neoeter_python_host_destroy(host);

	TEST_SECTION("module dispatch and entry");
	host = CreateHost();
	g_registeredModules = 0;

	const char* entryName = "test_python_host_api_entry.py";
	FILE* entry = std::fopen(entryName, "wb");
	TEST_ASSERT(entry != nullptr);
	std::fputs("host_entry_value = 42\n", entry);
	std::fclose(entry);

	TEST_ASSERT(neoeter_python_host_load(host, &pack) == NEOETER_PYTHON_OK);
	TEST_ASSERT(g_registeredModules == 2);
	TEST_ASSERT(std::strlen(neoeter_python_host_last_error(host)) == 0);
	TEST_ASSERT(neoeter_python_host_load(host, &pack) == NEOETER_PYTHON_INVALID_ARGUMENT);

	TEST_SECTION("destroy");
	neoeter_python_host_destroy(host);
	TEST_ASSERT(Py_IsInitialized() == 0);
	std::remove(entryName);

	std::printf("[PASS] python host ABI\n");
	return 0;
}
