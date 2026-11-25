#include <Neoeter/Python/Bindings/StdAfx.h>

bool ScriptTuple_GetTextInstance(ScriptObject* poArgs, int pos, CGraphicTextInstance** ppTextInstance)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetHandle(poArgs, pos, &pTextInstance))
		return false;

	if (!pTextInstance)
		return false;

	*ppTextInstance = pTextInstance;
	return true;
}

ScriptObject* grpTextGenerate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance = CGraphicTextInstance::New();
	return Script_BuildHandle(pTextInstance);
}

ScriptObject* grpTextDestroy(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	CGraphicTextInstance::Delete(pTextInstance);
	return Script_BuildNone();
}

ScriptObject* grpTextGetSize(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int width, height;
	pTextInstance->GetTextSize(&width, &height);
	return Script_BuildValue("(i, i)", width, height);
}

ScriptObject* grpTextSetPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int ix;
	if (!ScriptTuple_GetInteger(poArgs, 1, &ix))
		return Script_BuildException();
	int iy;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iy))
		return Script_BuildException();

	pTextInstance->SetPosition((float)ix, (float)iy);
	return Script_BuildNone();
}

ScriptObject* grpTextSetText(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	char* szText;
	if (!ScriptTuple_GetString(poArgs, 1, &szText))
		return Script_BuildException();

	pTextInstance->SetValue(szText);
	return Script_BuildNone();
}

ScriptObject* grpTextSetSecret(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	bool bValue;
	if (!ScriptTuple_GetBoolean(poArgs, 1, &bValue))
		return Script_BuildException();

	pTextInstance->SetSecret(bValue);
	return Script_BuildNone();
}

ScriptObject* grpTextOutline(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	bool bValue;
	if (!ScriptTuple_GetBoolean(poArgs, 1, &bValue))
		return Script_BuildException();

	pTextInstance->SetOutline(bValue);
	return Script_BuildNone();
}

ScriptObject* grpTextGetText(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	return Script_BuildValue("s", pTextInstance->GetValueStringReference().c_str());
}

ScriptObject* grpTextSetFontName(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	char* szFontName;
	if (!ScriptTuple_GetString(poArgs, 1, &szFontName))
		return Script_BuildException();

	std::string stFontName = szFontName;
	stFontName += ".fnt";

	CResource* pResource = CResourceManager::Instance().GetResourcePointer(stFontName.c_str());
	pTextInstance->SetTextPointer(static_cast<CGraphicText*>(pResource));
	return Script_BuildNone();
}

ScriptObject* grpTextSetFontColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	if (2 == ScriptTuple_Size(poArgs))
	{
		int iColor;
		if (!ScriptTuple_GetInteger(poArgs, 1, &iColor))
			return Script_BuildException();
		pTextInstance->SetColor(DWORD(iColor));
	}
	else if (4 == ScriptTuple_Size(poArgs))
	{
		float fRed;
		if (!ScriptTuple_GetFloat(poArgs, 1, &fRed))
			return Script_BuildException();
		float fGreen;
		if (!ScriptTuple_GetFloat(poArgs, 2, &fGreen))
			return Script_BuildException();
		float fBlue;
		if (!ScriptTuple_GetFloat(poArgs, 3, &fBlue))
			return Script_BuildException();
		pTextInstance->SetColor(fRed, fGreen, fBlue);
	}
	else
	{
		return Script_BuildException();
	}

	return Script_BuildNone();
}

ScriptObject* grpTextSetOutLineColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	float fRed;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fRed))
		return Script_BuildException();
	float fGreen;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fGreen))
		return Script_BuildException();
	float fBlue;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fBlue))
		return Script_BuildException();

	float fAlpha;
	if (!ScriptTuple_GetFloat(poArgs, 4, &fAlpha))
		return Script_BuildException();

	pTextInstance->SetOutLineColor(fRed, fGreen, fBlue, fAlpha);
	return Script_BuildNone();
}

ScriptObject* grpTextRender(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	pTextInstance->Render();
	return Script_BuildNone();
}

ScriptObject* grpTextUpdate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	pTextInstance->Update();
	return Script_BuildNone();
}

ScriptObject* grpTextShowCursor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	pTextInstance->ShowCursor();
	return Script_BuildNone();
}

ScriptObject* grpTextHideCursor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	pTextInstance->HideCursor();
	return Script_BuildNone();
}

ScriptObject* grpSetHorizontalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int iAlign;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iAlign))
		return Script_BuildException();

	pTextInstance->SetHorizonalAlign(iAlign);
	return Script_BuildNone();
}

ScriptObject* grpSetVerticalAlign(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int iAlign;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iAlign))
		return Script_BuildException();

	pTextInstance->SetVerticalAlign(iAlign);
	return Script_BuildNone();
}

ScriptObject* grpSetMax(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int iValue;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iValue))
		return Script_BuildException();

	pTextInstance->SetMax(iValue);
	return Script_BuildNone();
}

ScriptObject* grpGetSplitingTextLineCount(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szText;
	if (!ScriptTuple_GetString(poArgs, 0, &szText))
		return Script_BuildException();

	int iLineLimitation;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iLineLimitation))
		return Script_BuildException();

	int iPosition = 0;
	int iLineCount = 0;

	for (DWORD i = 0; i < strlen(szText);)
	{
		if ('|' == szText[i])
		{
			i += 1;

			// 자동 줄 바꿈되고 바로 | 가 있을 경우
			if (iPosition > 0)
				++iLineCount;

			iPosition = 0;
			continue;
		}

		if (szText[i] & 0x80)
		{
			i += 2;
			iPosition += 2;
		}
		else
		{
			i += 1;
			iPosition += 1;
		}

		if (iPosition >= iLineLimitation)
		{
			++iLineCount;
			iPosition = 0;
		}
	}

	if (iPosition > 0)
		++iLineCount;

	return Script_BuildValue("i", iLineCount);
}

ScriptObject* grpGetSplitingTextLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szText;
	if (!ScriptTuple_GetString(poArgs, 0, &szText))
		return Script_BuildException();

	int iLineLimitation;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iLineLimitation))
		return Script_BuildException();

	int iGettingLine;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iGettingLine))
		return Script_BuildException();

	std::string strLine = "";
	int iPosition = 0;
	int iLineCount = 0;

	// 1차 : 조금 더 깔끔하게 안될까 -_-a
	// 2차 : 오.. 좀 나아졌다 +_+
	for (DWORD i = 0; i < strlen(szText);)
	{
		if ('|' == szText[i])
		{
			i += 1;

			// 자동 줄 바꿈되고 바로 | 가 있을 경우
			if (iPosition > 0)
				++iLineCount;
			iPosition = 0;
			continue;
		}

		if (szText[i] & 0x80)
		{
			if (iLineCount == iGettingLine)
				strLine.append(szText + i, 2);

			i += 2;
			iPosition += 2;
		}
		else
		{
			if (iLineCount == iGettingLine)
				strLine += szText[i];

			i += 1;
			iPosition += 1;
		}

		if (iPosition >= iLineLimitation)
		{
			++iLineCount;
			iPosition = 0;
		}
	}

	return Script_BuildValue("s", strLine.c_str());
}

ScriptObject* grpTextPixelPositionToCharacterPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CGraphicTextInstance* pTextInstance;
	if (!ScriptTuple_GetTextInstance(poArgs, 0, &pTextInstance))
		return Script_BuildException();

	int iPixelPosition;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iPixelPosition))
		return Script_BuildException();

	int iCharacterPosition = pTextInstance->PixelPositionToCharacterPosition(iPixelPosition);

	return Script_BuildValue("i", iCharacterPosition);
}

void initgrpText()
{
	static ScriptMethodDef s_methods[] =
		{
			{"Update", grpTextUpdate, SCRIPT_VARARGS, NULL},
			{"Render", grpTextRender, SCRIPT_VARARGS, NULL},
			{"Generate", grpTextGenerate, SCRIPT_VARARGS, NULL},
			{"Destroy", grpTextDestroy, SCRIPT_VARARGS, NULL},
			{"SetFontName", grpTextSetFontName, SCRIPT_VARARGS, NULL},
			{"SetFontColor", grpTextSetFontColor, SCRIPT_VARARGS, NULL},
			{"SetOutLineColor", grpTextSetOutLineColor, SCRIPT_VARARGS, NULL},
			{"SetSecret", grpTextSetSecret, SCRIPT_VARARGS, NULL},
			{"SetOutline", grpTextOutline, SCRIPT_VARARGS, NULL},
			{"SetText", grpTextSetText, SCRIPT_VARARGS, NULL},
			{"GetText", grpTextGetText, SCRIPT_VARARGS, NULL},
			{"GetSize", grpTextGetSize, SCRIPT_VARARGS, NULL},
			{"SetPosition", grpTextSetPosition, SCRIPT_VARARGS, NULL},
			{"ShowCursor", grpTextShowCursor, SCRIPT_VARARGS, NULL},
			{"HideCursor", grpTextHideCursor, SCRIPT_VARARGS, NULL},
			{"SetHorizontalAlign", grpSetHorizontalAlign, SCRIPT_VARARGS, NULL},
			{"SetVerticalAlign", grpSetVerticalAlign, SCRIPT_VARARGS, NULL},
			{"SetMax", grpSetMax, SCRIPT_VARARGS, NULL},
			{"GetSplitingTextLineCount", grpGetSplitingTextLineCount, SCRIPT_VARARGS, NULL},
			{"GetSplitingTextLine", grpGetSplitingTextLine, SCRIPT_VARARGS, NULL},
			{"PixelPositionToCharacterPosition", grpTextPixelPositionToCharacterPosition, SCRIPT_VARARGS, NULL},
			{NULL, NULL, 0, NULL},
		};

	ScriptModule_Create("grpText", s_methods);
}
