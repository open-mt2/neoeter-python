#include <Neoeter/Python/Bindings/StdAfx.h>
#include <Neoeter/Render/Camera.h>
#include <Neoeter/Render/TextBar.h>

#ifdef _WIN32
#include <shlobj.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

bool ScriptTuple_GetTextBar(ScriptObject* poArgs, int pos, CTextBar** ppTextBar)
{
	return ScriptTuple_GetHandle(poArgs, pos, ppTextBar);
}

ScriptObject* grpCreateTextBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iWidth;
	if (!ScriptTuple_GetInteger(poArgs, 0, &iWidth))
		return Script_BuildException();
	int iHeight;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iHeight))
		return Script_BuildException();

	CTextBar* pTextBar = new CTextBar(12, false);
	if (!pTextBar->Create(NULL, iWidth, iHeight))
	{
		delete pTextBar;
		return Script_BuildHandle(NULL);
	}

	return Script_BuildHandle(pTextBar);
}

ScriptObject* grpCreateBigTextBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iWidth;
	if (!ScriptTuple_GetInteger(poArgs, 0, &iWidth))
		return Script_BuildException();
	int iHeight;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iHeight))
		return Script_BuildException();

	int iFontSize;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iFontSize))
		return Script_BuildException();

	CTextBar* pTextBar = new CTextBar(iFontSize, true);
	if (!pTextBar->Create(NULL, iWidth, iHeight))
	{
		delete pTextBar;
		return Script_BuildHandle(NULL);
	}

	return Script_BuildHandle(pTextBar);
}

ScriptObject* grpDestroyTextBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();

	delete pTextBar;

	return Script_BuildNone();
}

ScriptObject* grpRenderTextBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();
	int ix;
	if (!ScriptTuple_GetInteger(poArgs, 1, &ix))
		return Script_BuildException();
	int iy;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iy))
		return Script_BuildException();

	if (pTextBar)
		pTextBar->Render(ix, iy);

	return Script_BuildNone();
}

ScriptObject* grpTextBarSetTextColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();
	int r;
	if (!ScriptTuple_GetInteger(poArgs, 1, &r))
		return Script_BuildException();
	int g;
	if (!ScriptTuple_GetInteger(poArgs, 2, &g))
		return Script_BuildException();
	int b;
	if (!ScriptTuple_GetInteger(poArgs, 3, &b))
		return Script_BuildException();

	if (pTextBar)
		pTextBar->SetTextColor(r, g, b);

	return Script_BuildNone();
}

ScriptObject* grpTextBarGetTextExtent(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();
	char* szText;
	if (!ScriptTuple_GetString(poArgs, 1, &szText))
		return Script_BuildException();

	SIZE size = {0, 0};
	if (pTextBar)
		pTextBar->GetTextExtent(szText, &size);

	return Script_BuildValue("ii", size.cx, size.cy);
}

ScriptObject* grpTextBarTextOut(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();
	int ix;
	if (!ScriptTuple_GetInteger(poArgs, 1, &ix))
		return Script_BuildException();
	int iy;
	if (!ScriptTuple_GetInteger(poArgs, 2, &iy))
		return Script_BuildException();
	char* szText;
	if (!ScriptTuple_GetString(poArgs, 3, &szText))
		return Script_BuildException();

	if (pTextBar)
		pTextBar->TextOut(ix, iy, szText);

	return Script_BuildNone();
}

ScriptObject* grpClearTextBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();

	if (pTextBar)
		pTextBar->ClearBar();

	return Script_BuildNone();
}

ScriptObject* grpSetTextBarClipRect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CTextBar* pTextBar;
	if (!ScriptTuple_GetTextBar(poArgs, 0, &pTextBar))
		return Script_BuildException();
	int isx;
	if (!ScriptTuple_GetInteger(poArgs, 1, &isx))
		return Script_BuildException();
	int isy;
	if (!ScriptTuple_GetInteger(poArgs, 2, &isy))
		return Script_BuildException();
	int iex;
	if (!ScriptTuple_GetInteger(poArgs, 3, &iex))
		return Script_BuildException();
	int iey;
	if (!ScriptTuple_GetInteger(poArgs, 4, &iey))
		return Script_BuildException();

	if (pTextBar)
	{
		RECT rect;
		rect.left = isx;
		rect.top = isy;
		rect.right = iex;
		rect.bottom = iey;

		pTextBar->SetClipRect(rect);
	}

	return Script_BuildNone();
}

ScriptObject* grpCulling(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CCullingManager::Instance().Process();
	return Script_BuildNone();
}

ScriptObject* grpInitScreenEffect(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().InitScreenEffect();
	return Script_BuildNone();
}

ScriptObject* grpClearDepthBuffer(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().ClearDepthBuffer();
	return Script_BuildNone();
}

ScriptObject* grpPushState(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().PushState();
	return Script_BuildNone();
}

ScriptObject* grpPopState(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().PopState();
	return Script_BuildNone();
}

ScriptObject* grpPushMatrix(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().PushMatrix();
	return Script_BuildNone();
}

ScriptObject* grpPopMatrix(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().PopMatrix();
	return Script_BuildNone();
}

ScriptObject* grpTranslate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float x;
	if (!ScriptTuple_GetFloat(poArgs, 0, &x))
		return Script_BuildException("grp.Translate:Wrong X");

	float y;
	if (!ScriptTuple_GetFloat(poArgs, 1, &y))
		return Script_BuildException("grp.Translate:Wrong Y");

	float z;
	if (!ScriptTuple_GetFloat(poArgs, 2, &z))
		return Script_BuildException("grp.Translate:Wrong Z");

	CPythonGraphic::Instance().Translate(x, y, z);

	return Script_BuildNone();
}

ScriptObject* grpRotate(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float Degree;
	if (!ScriptTuple_GetFloat(poArgs, 0, &Degree))
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

	CPythonGraphic::Instance().Rotate(Degree, x, y, z);

	return Script_BuildNone();
}

ScriptObject* grpSetColorRenderState(ScriptObject* poSelf, ScriptObject* poArgs)
{
	return Script_BuildNone();
}

ScriptObject* grpSetAroundCamera(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float distance;
	if (!ScriptTuple_GetFloat(poArgs, 0, &distance))
		return Script_BuildException();

	float pitch;
	if (!ScriptTuple_GetFloat(poArgs, 1, &pitch))
		return Script_BuildException();

	float roll;
	if (!ScriptTuple_GetFloat(poArgs, 2, &roll))
		return Script_BuildException();

	float lookAtZ;
	if (!ScriptTuple_GetFloat(poArgs, 3, &lookAtZ))
		return Script_BuildException();

	CPythonGraphic::Instance().SetAroundCamera(distance, pitch, roll, lookAtZ);
	return Script_BuildNone();
}

ScriptObject* grpSetPositionCamera(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float fx;
	if (!ScriptTuple_GetFloat(poArgs, 0, &fx))
		return Script_BuildException();

	float fy;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fy))
		return Script_BuildException();

	float fz;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fz))
		return Script_BuildException();

	float distance;
	if (!ScriptTuple_GetFloat(poArgs, 3, &distance))
		return Script_BuildException();

	float pitch;
	if (!ScriptTuple_GetFloat(poArgs, 4, &pitch))
		return Script_BuildException();

	float roll;
	if (!ScriptTuple_GetFloat(poArgs, 5, &roll))
		return Script_BuildException();

	CPythonGraphic::Instance().SetPositionCamera(fx, fy, fz, distance, pitch, roll);
	return Script_BuildNone();
}

ScriptObject* grpSetEyeCamera(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float xEye;
	if (!ScriptTuple_GetFloat(poArgs, 0, &xEye))
		return Script_BuildException();

	float yEye;
	if (!ScriptTuple_GetFloat(poArgs, 1, &yEye))
		return Script_BuildException();

	float zEye;
	if (!ScriptTuple_GetFloat(poArgs, 2, &zEye))
		return Script_BuildException();

	float xCenter;
	if (!ScriptTuple_GetFloat(poArgs, 3, &xCenter))
		return Script_BuildException();

	float yCenter;
	if (!ScriptTuple_GetFloat(poArgs, 4, &yCenter))
		return Script_BuildException();

	float zCenter;
	if (!ScriptTuple_GetFloat(poArgs, 5, &zCenter))
		return Script_BuildException();

	float xUp;
	if (!ScriptTuple_GetFloat(poArgs, 6, &xUp))
		return Script_BuildException();

	float yUp;
	if (!ScriptTuple_GetFloat(poArgs, 7, &yUp))
		return Script_BuildException();

	float zUp;
	if (!ScriptTuple_GetFloat(poArgs, 8, &zUp))
		return Script_BuildException();

	CPythonGraphic::Instance().SetEyeCamera(xEye, yEye, zEye, xCenter, yCenter, zCenter, xUp, yUp, zUp);
	return Script_BuildNone();
}

ScriptObject* grpSetPerspective(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float fov;
	if (!ScriptTuple_GetFloat(poArgs, 0, &fov))
		return Script_BuildException();

	float aspect;
	if (!ScriptTuple_GetFloat(poArgs, 1, &aspect))
		return Script_BuildException();

	float zNear;
	if (!ScriptTuple_GetFloat(poArgs, 2, &zNear))
		return Script_BuildException();

	float zFar;
	if (!ScriptTuple_GetFloat(poArgs, 3, &zFar))
		return Script_BuildException();

	CPythonGraphic::Instance().SetPerspective(fov, aspect, zNear, zFar);
	return Script_BuildNone();
}

ScriptObject* grpSetOrtho2D(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float width;
	if (!ScriptTuple_GetFloat(poArgs, 0, &width))
		return Script_BuildException();

	float height;
	if (!ScriptTuple_GetFloat(poArgs, 1, &height))
		return Script_BuildException();

	float length;
	if (!ScriptTuple_GetFloat(poArgs, 2, &length))
		return Script_BuildException();

	CPythonGraphic::Instance().SetOrtho2D(width, height, length);
	return Script_BuildNone();
}

ScriptObject* grpSetOrtho3D(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float width;
	if (!ScriptTuple_GetFloat(poArgs, 0, &width))
		return Script_BuildException();

	float height;
	if (!ScriptTuple_GetFloat(poArgs, 1, &height))
		return Script_BuildException();

	float zmin;
	if (!ScriptTuple_GetFloat(poArgs, 2, &zmin))
		return Script_BuildException();

	float zmax;
	if (!ScriptTuple_GetFloat(poArgs, 3, &zmax))
		return Script_BuildException();

	CPythonGraphic::Instance().SetOrtho3D(width, height, zmin, zmax);
	return Script_BuildNone();
}

ScriptObject* grpGenerateColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float r;
	if (!ScriptTuple_GetFloat(poArgs, 0, &r))
		return Script_BuildException();

	float g;
	if (!ScriptTuple_GetFloat(poArgs, 1, &g))
		return Script_BuildException();

	float b;
	if (!ScriptTuple_GetFloat(poArgs, 2, &b))
		return Script_BuildException();

	float a;
	if (!ScriptTuple_GetFloat(poArgs, 3, &a))
		return Script_BuildException();

	return Script_BuildValue("l", CPythonGraphic::Instance().GenerateColor(r, g, b, a));
}

ScriptObject* grpSetColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int color;
	if (!ScriptTuple_GetInteger(poArgs, 0, &color))
		return Script_BuildException();

	CPythonGraphic::Instance().SetDiffuseColor(DWORD(color));
	return Script_BuildNone();
}

ScriptObject* grpSetAlpha(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float Alpha;
	if (!ScriptTuple_GetFloat(poArgs, 0, &Alpha))
		return Script_BuildException();

	// CPythonGraphic::Instance().SetAlpha(Alpha);
	return Script_BuildNone();
}

ScriptObject* grpGetCursorPosition3d(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float x, y, z;
	CPythonGraphic::Instance().GetCursorPosition(&x, &y, &z);
	return Script_BuildValue("(fff)", x, y, z);
}

ScriptObject* grpSetCursorPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int ix;
	if (!ScriptTuple_GetInteger(poArgs, 0, &ix))
		return Script_BuildException();
	int iy;
	if (!ScriptTuple_GetInteger(poArgs, 1, &iy))
		return Script_BuildException();

	CPythonGraphic::Instance().SetCursorPosition(ix, iy);
	return Script_BuildNone();
}

ScriptObject* grpRenderLine(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderLine2d((float)x, (float)y, (float)x + width, (float)y + height);
	return Script_BuildNone();
}

ScriptObject* grpRenderRoundBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	float fx = float(x);
	float fy = float(y);
	float fWidth = float(width);
	float fHeight = float(height);

	CPythonGraphic::Instance().RenderLine2d(fx + 2.0f, fy, fx + 2.0f + (fWidth - 3.0f), fy);
	CPythonGraphic::Instance().RenderLine2d(fx + 2.0f, fy + fHeight, fx + 2.0f + (fWidth - 3.0f), fy + fHeight);
	CPythonGraphic::Instance().RenderLine2d(fx, fy + 2.0f, fx, fy + 2.0f + fHeight - 4.0f);
	CPythonGraphic::Instance().RenderLine2d(fx + fWidth, fy + 1.0f, fx + fWidth, fy + 1.0f + fHeight - 3.0f);
	CPythonGraphic::Instance().RenderLine2d(fx, fy + 2.0f, fx + 2.0f, fy);
	CPythonGraphic::Instance().RenderLine2d(fx, fy + fHeight - 2.0f, fx + 2.0f, fy + fHeight);
	CPythonGraphic::Instance().RenderLine2d(fx + fWidth - 2.0f, fy, fx + fWidth, fy + 2.0f);
	CPythonGraphic::Instance().RenderLine2d(fx + fWidth - 2.0f, fy + fHeight, fx + fWidth, fy + fHeight - 2.0f);
	return Script_BuildNone();
}

ScriptObject* grpRenderBox(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderBox2d((float)x, (float)y, (float)x + width, (float)y + height);
	return Script_BuildNone();
}

ScriptObject* grpRenderBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderBar2d((float)x, (float)y, (float)x + width, (float)y + height);
	return Script_BuildNone();
}

ScriptObject* grpRenderCube(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float sx;
	if (!ScriptTuple_GetFloat(poArgs, 0, &sx))
		return Script_BuildException();

	float sy;
	if (!ScriptTuple_GetFloat(poArgs, 1, &sy))
		return Script_BuildException();

	float sz;
	if (!ScriptTuple_GetFloat(poArgs, 2, &sz))
		return Script_BuildException();

	float ex;
	if (!ScriptTuple_GetFloat(poArgs, 3, &ex))
		return Script_BuildException();

	float ey;
	if (!ScriptTuple_GetFloat(poArgs, 4, &ey))
		return Script_BuildException();

	float ez;
	if (!ScriptTuple_GetFloat(poArgs, 5, &ez))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderCube(sx, sy, sz, ex, ey, ez);
	return Script_BuildNone();
}

ScriptObject* grpRenderBar3d(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int sx;
	if (!ScriptTuple_GetInteger(poArgs, 0, &sx))
		return Script_BuildException();

	int sy;
	if (!ScriptTuple_GetInteger(poArgs, 1, &sy))
		return Script_BuildException();

	int sz;
	if (!ScriptTuple_GetInteger(poArgs, 2, &sz))
		return Script_BuildException();

	int ex;
	if (!ScriptTuple_GetInteger(poArgs, 3, &ex))
		return Script_BuildException();

	int ey;
	if (!ScriptTuple_GetInteger(poArgs, 4, &ey))
		return Script_BuildException();

	int ez;
	if (!ScriptTuple_GetInteger(poArgs, 5, &ez))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderBar3d(sx, sy, sz, ex, ey, ez);
	return Script_BuildNone();
}

ScriptObject* grpRenderGradationBar(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BadArgument();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BadArgument();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BadArgument();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BadArgument();

	int iStartColor;
	if (!ScriptTuple_GetInteger(poArgs, 4, &iStartColor))
		return Script_BadArgument();

	int iEndColor;
	if (!ScriptTuple_GetInteger(poArgs, 5, &iEndColor))
		return Script_BadArgument();

	CPythonGraphic::Instance().RenderGradationBar2d((float)x, (float)y, (float)x + width, (float)y + height, iStartColor, iEndColor);
	return Script_BuildNone();
}

ScriptObject* grpRenderDownButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderDownButton((float)x, (float)y, (float)x + width, (float)y + height);
	return Script_BuildNone();
}

ScriptObject* grpRenderUpButton(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int x;
	if (!ScriptTuple_GetInteger(poArgs, 0, &x))
		return Script_BuildException();

	int y;
	if (!ScriptTuple_GetInteger(poArgs, 1, &y))
		return Script_BuildException();

	int width;
	if (!ScriptTuple_GetInteger(poArgs, 2, &width))
		return Script_BuildException();

	int height;
	if (!ScriptTuple_GetInteger(poArgs, 3, &height))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderUpButton((float)x, (float)y, (float)x + width, (float)y + height);
	return Script_BuildNone();
}

ScriptObject* grpRenderBox3d(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float sx;
	if (!ScriptTuple_GetFloat(poArgs, 0, &sx))
		return Script_BuildException();

	float sy;
	if (!ScriptTuple_GetFloat(poArgs, 1, &sy))
		return Script_BuildException();

	float sz;
	if (!ScriptTuple_GetFloat(poArgs, 2, &sz))
		return Script_BuildException();

	float ex;
	if (!ScriptTuple_GetFloat(poArgs, 3, &ex))
		return Script_BuildException();

	float ey;
	if (!ScriptTuple_GetFloat(poArgs, 4, &ey))
		return Script_BuildException();

	float ez;
	if (!ScriptTuple_GetFloat(poArgs, 5, &ez))
		return Script_BuildException();

	CPythonGraphic::Instance().RenderBox3d((float)sx, (float)sy, (float)sz, (float)ex, (float)ey, (float)ez);
	return Script_BuildNone();
}

ScriptObject* grpSetClearColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float fr;
	if (!ScriptTuple_GetFloat(poArgs, 0, &fr))
		return Script_BuildException();

	float fg;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fg))
		return Script_BuildException();

	float fb;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fb))
		return Script_BuildException();

	CPythonGraphic::Instance().SetClearColor(fr, fg, fb, 1.0f);
	return Script_BuildNone();
}

ScriptObject* grpSetDiffuseColor(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float r;
	if (!ScriptTuple_GetFloat(poArgs, 0, &r))
		return Script_BuildException();

	float g;
	if (!ScriptTuple_GetFloat(poArgs, 1, &g))
		return Script_BuildException();

	float b;
	if (!ScriptTuple_GetFloat(poArgs, 2, &b))
		return Script_BuildException();

	float a;
	if (!ScriptTuple_GetFloat(poArgs, 3, &a))
		return Script_BuildException();

	CPythonGraphic::Instance().SetDiffuseColor(r, g, b, a);
	return Script_BuildNone();
}

ScriptObject* grpIdentity(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().Identity();
	return Script_BuildNone();
}

ScriptObject* grpGetAvailableMemory(ScriptObject* poSelf, ScriptObject* poArgs)
{
	int iValue = CPythonGraphic::Instance().GetAvailableMemory();
	return Script_BuildValue("i", iValue);
}

// SCREENSHOT_CWDSAVE
ScriptObject* grpSaveScreenShotToPath(ScriptObject* poSelf, ScriptObject* poArgs)
{
	char* szBasePath;
	if (!ScriptTuple_GetString(poArgs, 0, &szBasePath))
		return Script_BuildException();

	struct tm* tmNow;
	time_t ct;

	ct = time(0);
	tmNow = localtime(&ct);

	char szPath[MAX_PATH + 256];
	snprintf(szPath, sizeof(szPath), "%s%02d%02d_%02d%02d%02d.jpg",
			 szBasePath,
			 tmNow->tm_mon + 1,
			 tmNow->tm_mday,
			 tmNow->tm_hour,
			 tmNow->tm_min,
			 tmNow->tm_sec);

	BOOL bResult = CPythonGraphic::Instance().SaveScreenShot(szPath);
	return Script_BuildValue("(is)", bResult, szPath);
}
// END_OF_SCREENSHOT_CWDSAVE

ScriptObject* grpSaveScreenShot(ScriptObject* poSelf, ScriptObject* poArgs)
{
	struct tm* tmNow;
	time_t ct;

	ct = time(0);
	tmNow = localtime(&ct);

	char szPath[MAX_PATH + 256];
#ifdef _WIN32
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_PERSONAL, TRUE);
	strcat(szPath, "\\METIN2\\");
#else
	const char* home = getenv("HOME");
	if (home)
		snprintf(szPath, sizeof(szPath), "%s/.metin2/screenshots/", home);
	else
		snprintf(szPath, sizeof(szPath), "./screenshots/");
#endif

	if (-1 == _access(szPath, 0))
		if (!CreateDirectory(szPath, NULL))
		{
			TraceError("Failed to create directory [%s]\n", szPath);
			return Script_BuildValue("(is)", FALSE, "");
		}

	sprintf(szPath + strlen(szPath), "%02d%02d_%02d%02d%02d.jpg",
			tmNow->tm_mon + 1,
			tmNow->tm_mday,
			tmNow->tm_hour,
			tmNow->tm_min,
			tmNow->tm_sec);

	BOOL bResult = CPythonGraphic::Instance().SaveScreenShot(szPath);
	return Script_BuildValue("(is)", bResult, szPath);
}

ScriptObject* grpSetGamma(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float gamma;

	if (!ScriptTuple_GetFloat(poArgs, 0, &gamma))
		return Script_BuildException();

	CPythonGraphic::Instance().SetGamma(gamma);
	return Script_BuildNone();
}

ScriptObject* grpSetInterfaceRenderState(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().SetInterfaceRenderState();
	return Script_BuildNone();
}

ScriptObject* grpSetGameRenderState(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().SetGameRenderState();
	return Script_BuildNone();
}

ScriptObject* grpSetViewport(ScriptObject* poSelf, ScriptObject* poArgs)
{
	float fx;
	if (!ScriptTuple_GetFloat(poArgs, 0, &fx))
		return Script_BuildException();
	float fy;
	if (!ScriptTuple_GetFloat(poArgs, 1, &fy))
		return Script_BuildException();

	float fWidth;
	if (!ScriptTuple_GetFloat(poArgs, 2, &fWidth))
		return Script_BuildException();
	float fHeight;
	if (!ScriptTuple_GetFloat(poArgs, 3, &fHeight))
		return Script_BuildException();

	UINT uWidth;
	UINT uHeight;
	CPythonGraphic::Instance().GetBackBufferSize(&uWidth, &uHeight);
	CPythonGraphic::Instance().SetViewport(fx * uWidth, fy * uHeight, fWidth * uWidth, fHeight * uHeight);
	return Script_BuildNone();
}

ScriptObject* grpRestoreViewport(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().RestoreViewport();
	return Script_BuildNone();
}

ScriptObject* grpSetOmniLight(ScriptObject* poSelf, ScriptObject* poArgs)
{
	CPythonGraphic::Instance().SetOmniLight();
	return Script_BuildNone();
}

ScriptObject* grpGetCameraPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	D3DXVECTOR3 v3Eye = CCameraManager::Instance().GetCurrentCamera()->GetEye();
	return Script_BuildValue("fff", v3Eye.x, v3Eye.y, v3Eye.z);
}

ScriptObject* grpGetTargetPosition(ScriptObject* poSelf, ScriptObject* poArgs)
{
	D3DXVECTOR3 v3Target = CCameraManager::Instance().GetCurrentCamera()->GetTarget();
	return Script_BuildValue("fff", v3Target.x, v3Target.y, v3Target.z);
}

void initgrp()
{
	static ScriptMethodDef s_methods[] =
		{
			{"InitScreenEffect", grpInitScreenEffect, SCRIPT_VARARGS, NULL},
			{"Culling", grpCulling, SCRIPT_VARARGS, NULL},
			{"ClearDepthBuffer", grpClearDepthBuffer, SCRIPT_VARARGS, NULL},
			{"Identity", grpIdentity, SCRIPT_VARARGS, NULL},
			{"GenerateColor", grpGenerateColor, SCRIPT_VARARGS, NULL},
			{"PopState", grpPopState, SCRIPT_VARARGS, NULL},
			{"PushState", grpPushState, SCRIPT_VARARGS, NULL},
			{"PushMatrix", grpPushMatrix, SCRIPT_VARARGS, NULL},
			{"PopMatrix", grpPopMatrix, SCRIPT_VARARGS, NULL},
			{"Translate", grpTranslate, SCRIPT_VARARGS, NULL},
			{"Rotate", grpRotate, SCRIPT_VARARGS, NULL},
			{"SetColorRenderState", grpSetColorRenderState, SCRIPT_VARARGS, NULL},
			{"SetAroundCamera", grpSetAroundCamera, SCRIPT_VARARGS, NULL},
			{"SetPositionCamera", grpSetPositionCamera, SCRIPT_VARARGS, NULL},
			{"SetEyeCamera", grpSetEyeCamera, SCRIPT_VARARGS, NULL},
			{"SetPerspective", grpSetPerspective, SCRIPT_VARARGS, NULL},
			{"SetOrtho2d", grpSetOrtho2D, SCRIPT_VARARGS, NULL},
			{"SetOrtho3d", grpSetOrtho3D, SCRIPT_VARARGS, NULL},
			{"SetColor", grpSetColor, SCRIPT_VARARGS, NULL},
			{"SetAlpha", grpSetAlpha, SCRIPT_VARARGS, NULL},
			{"SetDiffuseColor", grpSetDiffuseColor, SCRIPT_VARARGS, NULL},
			{"SetClearColor", grpSetClearColor, SCRIPT_VARARGS, NULL},
			{"GetCursorPosition3d", grpGetCursorPosition3d, SCRIPT_VARARGS, NULL},
			{"SetCursorPosition", grpSetCursorPosition, SCRIPT_VARARGS, NULL},
			{"RenderLine", grpRenderLine, SCRIPT_VARARGS, NULL},
			{"RenderBox", grpRenderBox, SCRIPT_VARARGS, NULL},
			{"RenderRoundBox", grpRenderRoundBox, SCRIPT_VARARGS, NULL},
			{"RenderBox3d", grpRenderBox3d, SCRIPT_VARARGS, NULL},
			{"RenderBar", grpRenderBar, SCRIPT_VARARGS, NULL},
			{"RenderBar3d", grpRenderBar3d, SCRIPT_VARARGS, NULL},
			{"RenderGradationBar", grpRenderGradationBar, SCRIPT_VARARGS, NULL},
			{"RenderCube", grpRenderCube, SCRIPT_VARARGS, NULL},
			{"RenderDownButton", grpRenderDownButton, SCRIPT_VARARGS, NULL},
			{"RenderUpButton", grpRenderUpButton, SCRIPT_VARARGS, NULL},
			{"GetAvailableMemory", grpGetAvailableMemory, SCRIPT_VARARGS, NULL},
			{"SaveScreenShot", grpSaveScreenShot, SCRIPT_VARARGS, NULL},
			{"SaveScreenShotToPath", grpSaveScreenShotToPath, SCRIPT_VARARGS, NULL},
			{"SetGamma", grpSetGamma, SCRIPT_VARARGS, NULL},
			{"SetInterfaceRenderState", grpSetInterfaceRenderState, SCRIPT_VARARGS, NULL},
			{"SetGameRenderState", grpSetGameRenderState, SCRIPT_VARARGS, NULL},
			{"SetViewport", grpSetViewport, SCRIPT_VARARGS, NULL},
			{"RestoreViewport", grpRestoreViewport, SCRIPT_VARARGS, NULL},
			{"SetOmniLight", grpSetOmniLight, SCRIPT_VARARGS, NULL},
			{"GetCameraPosition", grpGetCameraPosition, SCRIPT_VARARGS, NULL},
			{"GetTargetPosition", grpGetTargetPosition, SCRIPT_VARARGS, NULL},

			{"CreateTextBar", grpCreateTextBar, SCRIPT_VARARGS, NULL},
			{"CreateBigTextBar", grpCreateBigTextBar, SCRIPT_VARARGS, NULL},
			{"DestroyTextBar", grpDestroyTextBar, SCRIPT_VARARGS, NULL},
			{"RenderTextBar", grpRenderTextBar, SCRIPT_VARARGS, NULL},
			{"TextBarTextOut", grpTextBarTextOut, SCRIPT_VARARGS, NULL},
			{"TextBarSetTextColor", grpTextBarSetTextColor, SCRIPT_VARARGS, NULL},
			{"TextBarGetTextExtent", grpTextBarGetTextExtent, SCRIPT_VARARGS, NULL},
			{"ClearTextBar", grpClearTextBar, SCRIPT_VARARGS, NULL},
			{"SetTextBarClipRect", grpSetTextBarClipRect, SCRIPT_VARARGS, NULL},

			{NULL, NULL, 0, NULL},
		};

	ScriptModule_Create("grp", s_methods);
}
