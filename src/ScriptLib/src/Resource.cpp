#include "StdAfx.h"
#include <EterLib/GrpExpandedImageInstance.h>
#include <EterLib/GrpTextInstance.h>
#include <EterLib/GrpMarkInstance.h>
#include <EterLib/GrpSubImage.h>
#include <EterLib/GrpText.h>
#include <EterLib/AttributeData.h>
#include <EterGrnLib/Thing.h>
#include <EterGrnLib/ThingInstance.h>
#include <EffectLib/EffectMesh.h>
#include <EffectLib/EffectInstance.h>

#include "Resource.h"

std::vector<CPythonResource::TDestroyHandler> CPythonResource::ms_destroyHandlers;

CResource * NewImage(const char* c_szFileName)
{
	return new CGraphicImage(c_szFileName);
}

CResource * NewSubImage(const char* c_szFileName)
{
	return new CGraphicSubImage(c_szFileName);
}

CResource * NewText(const char* c_szFileName)
{
	return new CGraphicText(c_szFileName);
}

CResource * NewThing(const char* c_szFileName)
{
	return new CGraphicThing(c_szFileName);
}

CResource * NewEffectMesh(const char* c_szFileName)
{
	return new CEffectMesh(c_szFileName);
}

CResource * NewAttributeData(const char* c_szFileName)
{
	return new CAttributeData(c_szFileName);
}

void CPythonResource::RegisterDestroyHandler(TDestroyHandler pfnHandler)
{
	if (pfnHandler)
		ms_destroyHandlers.push_back(pfnHandler);
}

void CPythonResource::DumpFileList(const char * c_szFileName)
{
	m_resManager.DumpFileListToTextFile(c_szFileName);
}

void CPythonResource::Destroy()
{
	for (size_t i = 0; i < ms_destroyHandlers.size(); ++i)
	{
		if (ms_destroyHandlers[i])
			ms_destroyHandlers[i]();
	}

	CGraphicExpandedImageInstance::DestroySystem();
	CGraphicImageInstance::DestroySystem();	
	CGraphicMarkInstance::DestroySystem();
	CGraphicThingInstance::DestroySystem();
	CGrannyModelInstance::DestroySystem();
	CGraphicTextInstance::DestroySystem();
	CEffectInstance::DestroySystem();
	
	m_resManager.DestroyDeletingList();

	CEffectData::DestroySystem();
	CEffectMesh::SEffectMeshData::DestroySystem();

	m_resManager.Destroy();	
}

CPythonResource::CPythonResource()
{
	m_resManager.RegisterResourceNewFunctionPointer("sub", NewSubImage);
	m_resManager.RegisterResourceNewFunctionPointer("dds", NewImage);
	m_resManager.RegisterResourceNewFunctionPointer("jpg", NewImage);
	m_resManager.RegisterResourceNewFunctionPointer("tga", NewImage);
	m_resManager.RegisterResourceNewFunctionPointer("bmp", NewImage);
	m_resManager.RegisterResourceNewFunctionPointer("fnt", NewText);
	m_resManager.RegisterResourceNewFunctionPointer("gr2", NewThing);
	m_resManager.RegisterResourceNewFunctionPointer("mde", NewEffectMesh);
	m_resManager.RegisterResourceNewFunctionPointer("mdatr", NewAttributeData);
}

CPythonResource::~CPythonResource()
{
	Destroy();
}
