#pragma once

#include <EffectLib/StdAfx.h>
#include <EterLib/Resource.h>
#include <EterLib/ResourceManager.h>
#include <vector>

enum EResourceTypes
{
	RES_TYPE_UNKNOWN,
};

class CPythonResource : public CSingleton<CPythonResource>
{
	public:
		typedef void (*TDestroyHandler)();

		CPythonResource();
		virtual ~CPythonResource();
		
		void Destroy();

		void DumpFileList(const char * c_szFileName);

		static void RegisterDestroyHandler(TDestroyHandler pfnHandler);

	protected:
		CResourceManager m_resManager;
		static std::vector<TDestroyHandler> ms_destroyHandlers;
};
