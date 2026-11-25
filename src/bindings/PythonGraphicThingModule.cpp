#include <Neoeter/Python/Bindings/StdAfx.h>

bool ScriptTuple_GetThingInstance(ScriptObject* poArgs, int pos, CGraphicThingInstance** ppRetThingInstance)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetHandle(poArgs, pos, &pThingInstance))
		return false;

	if (!pThingInstance)
		return false;

	*ppRetThingInstance = pThingInstance;
	return true;
}

ScriptObject* grpThingGenerate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 0, &szFileName))
		return Script_BuildException();

	if (strlen(szFileName) <= 0)
		return Script_BuildHandle(NULL);

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(szFileName);

	if (!pResource->IsType(CGraphicThing::Type()))
		return Script_BuildException();

	CGraphicThingInstance* pThingInstance = CGraphicThingInstance::New();
	pThingInstance->ReserveModelThing(1);
	pThingInstance->ReserveModelInstance(1);
	pThingInstance->RegisterModelThing(0, static_cast<CGraphicThing*>(pResource));
	pThingInstance->SetModelInstance(0, 0, 0);
	return Script_BuildHandle(pThingInstance);
}

ScriptObject* grpThingDelete(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	CGraphicThingInstance::Delete(pThingInstance);
	return Script_BuildNone();
}

ScriptObject* grpThingSetFileName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BuildException();

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(szFileName);

	if (!pResource->IsType(CGraphicThing::Type()))
		return Script_BuildException();

	pThingInstance->Clear();
	pThingInstance->ReserveModelThing(1);
	pThingInstance->ReserveModelInstance(1);
	pThingInstance->RegisterModelThing(0, static_cast<CGraphicThing*>(pResource));
	pThingInstance->SetModelInstance(0, 0, 0);
	return Script_BuildNone();
}

ScriptObject* grpThingRender(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	pThingInstance->Render();
	return Script_BuildNone();
}

ScriptObject* grpThingUpdate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	pThingInstance->Update();
	pThingInstance->Deform();
	return Script_BuildNone();
}

ScriptObject* grpSetThingPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	float x;
	if (!ScriptTuple_GetFloat(poArgs, 1, &x))
		return Script_BuildException();

	float y;
	if (!ScriptTuple_GetFloat(poArgs, 2, &y))
		return Script_BuildException();

	float z;
	if (!ScriptTuple_GetFloat(poArgs, 3, &z))
		return Script_BuildException();

	pThingInstance->SetPosition(x, y, z);
	return Script_BuildNone();
}

ScriptObject* grpSetThingRotation(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	float fDegree;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fDegree))
		return Script_BuildException();

	pThingInstance->SetRotation(fDegree);
	return Script_BuildNone();
}

ScriptObject* grpSetThingScale(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicThingInstance* pThingInstance;
	if (!ScriptTuple_GetThingInstance(poArgs, 0, &pThingInstance))
		return Script_BuildException();

	float x;
	if (!ScriptTuple_GetFloat(poArgs, 1, &x))
		return Script_BuildException();
	float y;
	if (!ScriptTuple_GetFloat(poArgs, 2, &y))
		return Script_BuildException();
	float z;
	if (!ScriptTuple_GetFloat(poArgs, 3, &z))
		return Script_BuildException();

	pThingInstance->SetScale(x, y, z);
	return Script_BuildNone();
}

void initgrpThing()
{
	static ScriptMethodDef s_methods[] =
		{
			{"Update", grpThingUpdate, SCRIPT_VARARGS, NULL},
			{"Render", grpThingRender, SCRIPT_VARARGS, NULL},
			{"SetPosition", grpSetThingPosition, SCRIPT_VARARGS, NULL},
			{"Generate", grpThingGenerate, SCRIPT_VARARGS, NULL},
			{"Delete", grpThingDelete, SCRIPT_VARARGS, NULL},
			{"SetFileName", grpThingSetFileName, SCRIPT_VARARGS, NULL},
			{"SetRotation", grpSetThingRotation, SCRIPT_VARARGS, NULL},
			{"SetScale", grpSetThingScale, SCRIPT_VARARGS, NULL},
			{NULL, NULL, 0, NULL},
		};

	ScriptModule_Create("grpThing", s_methods);
}
