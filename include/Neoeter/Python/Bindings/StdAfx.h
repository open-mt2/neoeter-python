#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <Platform/Platform.h>
#include <Neoeter/Render/StdAfx.h>
#include <Neoeter/Model/Grn/StdAfx.h>

#include <Neoeter/Script/Script.h>
#include <Neoeter/Script/ScriptExceptionSender.h>

#include <Neoeter/Python/Bindings/Resource.h>
#include <Neoeter/Python/Bindings/ScriptDebugModule.h>

#include <Neoeter/Python/Bindings/PythonGraphic.h>
#include <Neoeter/Python/Bindings/PythonWindowManager.h>

void initgrp();
void initgrpImage();
void initgrpText();
void initgrpThing();
void initscriptWindow();
void initwndMgr();
