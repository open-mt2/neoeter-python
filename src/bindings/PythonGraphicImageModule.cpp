#include <Neoeter/Python/Bindings/StdAfx.h>

bool ScriptTuple_GetImageInstance(ScriptObject* poArgs, int pos, CGraphicImageInstance** ppRetImageInstance)
{
	CGraphicImageInstance* pImageInstance;

	if (!ScriptTuple_GetHandle(poArgs, pos, &pImageInstance))
		return false;

	if (!pImageInstance)
		return false;

	*ppRetImageInstance = pImageInstance;
	return true;
}

bool ScriptTuple_GetExpandedImageInstance(ScriptObject* poArgs, int pos, CGraphicExpandedImageInstance** ppRetImageInstance)
{
	CGraphicImageInstance* pImageInstance;

	if (!ScriptTuple_GetHandle(poArgs, pos, &pImageInstance))
		return false;

	if (!pImageInstance)
		return false;

	if (!pImageInstance->IsType(CGraphicExpandedImageInstance::Type()))
		return false;

	*ppRetImageInstance = static_cast<CGraphicExpandedImageInstance*>(pImageInstance);

	return true;
}

ScriptObject* grpImageGenerate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szFileName;

	if (!ScriptTuple_GetString(poArgs, 0, &szFileName))
		return Script_BadArgument();

	if (!*szFileName)
		return Script_BuildHandle(NULL);

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(szFileName);

	if (!pResource->IsType(CGraphicImage::Type()))
		return Script_BuildException("Resource is not an image (filename: %s)", szFileName);

	CGraphicImageInstance* pImageInstance = CGraphicImageInstance::New();
	pImageInstance->SetImagePointer(static_cast<CGraphicImage*>(pResource));

	if (pImageInstance->IsEmpty())
		return Script_BuildException("Cannot load image (filename: %s)", szFileName);

	return Script_BuildHandle(pImageInstance);
}

ScriptObject* grpImageGenerateExpanded(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szFileName;

	if (!ScriptTuple_GetString(poArgs, 0, &szFileName))
		return Script_BadArgument();

	if (strlen(szFileName) <= 0)
		return Script_BuildHandle(NULL);

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(szFileName);

	if (!pResource->IsType(CGraphicImage::Type()))
		return Script_BuildException("Resource is not an image (filename: %s)", szFileName);

	CGraphicExpandedImageInstance* pImageInstance = CGraphicExpandedImageInstance::New();
	pImageInstance->SetImagePointer(static_cast<CGraphicImage*>(pResource));

	if (pImageInstance->IsEmpty())
		return Script_BuildException("Cannot load image (filename: %s)", szFileName);

	return Script_BuildHandle(pImageInstance);
}

ScriptObject* grpImageGenerateFromHandle(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImage* pImage;
	if (!ScriptTuple_GetHandle(poArgs, 0, &pImage))
		return Script_BadArgument();

	CGraphicImageInstance* pImageInstance = CGraphicImageInstance::New();
	pImageInstance->SetImagePointer(pImage);

	return Script_BuildHandle(pImageInstance);
}

ScriptObject* grpImageDelete(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;

	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	if (!pImageInstance)
		return Script_BuildNone();

	CGraphicImageInstance::Delete(pImageInstance);

	return Script_BuildNone();
}

ScriptObject* grpImageDeleteExpanded(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicExpandedImageInstance* pExpandedImageInstance;
	if (!ScriptTuple_GetExpandedImageInstance(poArgs, 0, &pExpandedImageInstance))
		return Script_BadArgument();

	CGraphicExpandedImageInstance::Delete(pExpandedImageInstance);
	return Script_BuildNone();
}

ScriptObject* grpImageSetFileName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;
	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	char* szFileName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFileName))
		return Script_BadArgument();

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(szFileName);

	if (!pResource->IsType(CGraphicImage::Type()))
		return Script_BuildException("Resource is not an image (filename: %s)", szFileName);

	pImageInstance->SetImagePointer(static_cast<CGraphicImage*>(pResource));
	return Script_BuildNone();
}

ScriptObject* grpImageRender(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;
	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	pImageInstance->Render();
	return Script_BuildNone();
}

ScriptObject* grpSetImagePosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;
	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float x;
	if (!ScriptTuple_GetFloat(poArgs, 1, &x))
		return Script_BadArgument();

	float y;
	if (!ScriptTuple_GetFloat(poArgs, 2, &y))
		return Script_BadArgument();

	pImageInstance->SetPosition(x, y);
	return Script_BuildNone();
}

ScriptObject* grpSetImageOrigin(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicExpandedImageInstance* pImageInstance;
	if (!ScriptTuple_GetExpandedImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float x;
	if (!ScriptTuple_GetFloat(poArgs, 1, &x))
		return Script_BadArgument();
	float y;
	if (!ScriptTuple_GetFloat(poArgs, 2, &y))
		return Script_BadArgument();

	pImageInstance->SetOrigin(x, y);
	return Script_BuildNone();
}

ScriptObject* grpSetImageRotation(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicExpandedImageInstance* pImageInstance;
	if (!ScriptTuple_GetExpandedImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float Degree;
	if (!ScriptTuple_GetFloat(poArgs, 1, &Degree))
		return Script_BadArgument();

	pImageInstance->SetRotation(Degree);
	return Script_BuildNone();
}

ScriptObject* grpSetImageScale(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicExpandedImageInstance* pImageInstance;
	if (!ScriptTuple_GetExpandedImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float x;
	if (!ScriptTuple_GetFloat(poArgs, 1, &x))
		return Script_BadArgument();
	float y;
	if (!ScriptTuple_GetFloat(poArgs, 2, &y))
		return Script_BadArgument();

	pImageInstance->SetScale(x, y);
	return Script_BuildNone();
}

ScriptObject* grpSetRenderingRect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicExpandedImageInstance* pImageInstance;
	if (!ScriptTuple_GetExpandedImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float fLeft;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fLeft))
		return Script_BadArgument();
	float fTop;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fTop))
		return Script_BadArgument();
	float fRight;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fRight))
		return Script_BadArgument();
	float fBottom;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fBottom))
		return Script_BadArgument();

	pImageInstance->SetRenderingRect(fLeft, fTop, fRight, fBottom);
	return Script_BuildNone();
}

ScriptObject* grpSetImageDiffuseColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;
	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	float r;
	if (!ScriptTuple_GetFloat(poArgs, 1, &r))
		return Script_BadArgument();
	float g;
	if (!ScriptTuple_GetFloat(poArgs, 2, &g))
		return Script_BadArgument();
	float b;
	if (!ScriptTuple_GetFloat(poArgs, 3, &b))
		return Script_BadArgument();
	float a;
	if (!ScriptTuple_GetFloat(poArgs, 4, &a))
		return Script_BadArgument();

	pImageInstance->SetDiffuseColor(r, g, b, a);
	return Script_BuildNone();
}

ScriptObject* grpGetWidth(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;

	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	if (pImageInstance->IsEmpty())
		return Script_BuildException("Image is empty");

	return Script_BuildValue("i", pImageInstance->GetWidth());
}

ScriptObject* grpGetHeight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicImageInstance* pImageInstance;

	if (!ScriptTuple_GetImageInstance(poArgs, 0, &pImageInstance))
		return Script_BadArgument();

	if (pImageInstance->IsEmpty())
		return Script_BuildException("Image is empty");

	return Script_BuildValue("i", pImageInstance->GetHeight());
}

void initgrpImage()
{
	static ScriptMethodDef s_methods[] =
		{
			{"Render", grpImageRender, SCRIPT_VARARGS, NULL},
			{"SetPosition", grpSetImagePosition, SCRIPT_VARARGS, NULL},
			{"Generate", grpImageGenerate, SCRIPT_VARARGS, NULL},
			{"GenerateExpanded", grpImageGenerateExpanded, SCRIPT_VARARGS, NULL},
			{"GenerateFromHandle", grpImageGenerateFromHandle, SCRIPT_VARARGS, NULL},
			{"Delete", grpImageDelete, SCRIPT_VARARGS, NULL},
			{"DeleteExpanded", grpImageDeleteExpanded, SCRIPT_VARARGS, NULL},
			{"SetFileName", grpImageSetFileName, SCRIPT_VARARGS, NULL},
			{"SetOrigin", grpSetImageOrigin, SCRIPT_VARARGS, NULL},
			{"SetRotation", grpSetImageRotation, SCRIPT_VARARGS, NULL},
			{"SetScale", grpSetImageScale, SCRIPT_VARARGS, NULL},
			{"SetRenderingRect", grpSetRenderingRect, SCRIPT_VARARGS, NULL},
			{"SetDiffuseColor", grpSetImageDiffuseColor, SCRIPT_VARARGS, NULL},
			{"GetWidth", grpGetWidth, SCRIPT_VARARGS, NULL},
			{"GetHeight", grpGetHeight, SCRIPT_VARARGS, NULL},
			{NULL, NULL, 0, NULL},
		};

	ScriptModule_Create("grpImage", s_methods);
}
