#pragma once

#include <Neoeter/Platform/Base/Utils.h>

#include <list>
#include <Python.h>

namespace UI
{
	class CWindow
	{
		public:
			typedef std::list<CWindow*> TWindowContainer;

			static uint32_t Type();
			int32_t IsType(uint32_t dwType);

			enum EHorizontalAlign
			{
				HORIZONTAL_ALIGN_LEFT = 0,
				HORIZONTAL_ALIGN_CENTER = 1,
				HORIZONTAL_ALIGN_RIGHT = 2,
			};

			enum EVerticalAlign
			{
				VERTICAL_ALIGN_TOP = 0,
				VERTICAL_ALIGN_CENTER = 1,
				VERTICAL_ALIGN_BOTTOM = 2,
			};

			enum EFlags
			{
				FLAG_MOVABLE = (1 << 0), // 움직일 수 있는 창
				FLAG_LIMIT = (1 << 1),	 // 창이 화면을 벗어나지 않음
				FLAG_SNAP = (1 << 2),	 // 스냅 될 수 있는 창
				FLAG_DRAGABLE = (1 << 3),
				FLAG_ATTACH = (1 << 4),		// 완전히 부모에 붙어 있는 창 (For Drag / ex. ScriptWindow)
				FLAG_RESTRICT_X = (1 << 5), // 좌우 이동 제한
				FLAG_RESTRICT_Y = (1 << 6), // 상하 이동 제한
				FLAG_NOT_CAPTURE = (1 << 7),
				FLAG_FLOAT = (1 << 8),	  // 공중에 떠있어서 순서 재배치가 되는 창
				FLAG_NOT_PICK = (1 << 9), // 마우스에 의해 Pick되지 않는 창
				FLAG_IGNORE_SIZE = (1 << 10),
				FLAG_RTL = (1 << 11), // Right-to-left
			};

		public:
			CWindow(PyObject* ppyObject);
			virtual ~CWindow();

			void AddChild(CWindow* pWin);

			void Clear();
			void DestroyHandle();
			void Update();
			void Render();

			void SetName(const char* c_szName);
			const char* GetName() { return m_strName.c_str(); }
			void SetSize(long width, long height);
			long GetWidth() { return m_lWidth; }
			long GetHeight() { return m_lHeight; }

			void SetHorizontalAlign(uint32_t dwAlign);
			void SetVerticalAlign(uint32_t dwAlign);
			void SetPosition(long x, long y);
			void GetPosition(long* plx, long* ply);
			long GetPositionX(void) const { return m_x; }
			long GetPositionY(void) const { return m_y; }
			RECT& GetRect() { return m_rect; }
			void GetLocalPosition(long& rlx, long& rly);
			void GetMouseLocalPosition(long& rlx, long& rly);
			long UpdateRect();

			RECT& GetLimitBias() { return m_limitBiasRect; }
			void SetLimitBias(long l, long r, long t, long b) { m_limitBiasRect.left = l, m_limitBiasRect.right = r, m_limitBiasRect.top = t, m_limitBiasRect.bottom = b; }

			void Show();
			void Hide();
			bool IsShow() { return m_bShow; }
			bool IsRendering();

			bool HasParent() { return m_pParent ? true : false; }
			bool HasChild() { return m_pChildList.empty() ? false : true; }
			int GetChildCount() { return m_pChildList.size(); }

			CWindow* GetRoot();
			CWindow* GetParent();
			bool IsChild(CWindow* pWin);
			void DeleteChild(CWindow* pWin);
			void SetTop(CWindow* pWin);

			bool IsIn(long x, long y);
			bool IsIn();
			CWindow* PickWindow(long x, long y);
			CWindow* PickTopWindow(long x, long y); // NOTE : Children으로 내려가지 않고 상위에서만
													//        체크 하는 특화된 함수

			void __RemoveReserveChildren();

			void AddFlag(uint32_t flag) { SET_BIT(m_dwFlag, flag); }
			void RemoveFlag(uint32_t flag) { REMOVE_BIT(m_dwFlag, flag); }
			bool IsFlag(uint32_t flag) { return (m_dwFlag & flag) ? true : false; }
			/////////////////////////////////////

			virtual void OnRender();
			virtual void OnUpdate();
			virtual void OnChangePosition() {}

			virtual void OnSetFocus();
			virtual void OnKillFocus();

			virtual void OnMouseDrag(long lx, long ly);
			virtual void OnMouseOverIn();
			virtual void OnMouseOverOut();
			virtual void OnMouseOver();
			virtual void OnDrop();
			virtual void OnTop();
			virtual void OnIMEUpdate();

			virtual void OnMoveWindow(long x, long y);

			///////////////////////////////////////

			int32_t RunIMETabEvent();
			int32_t RunIMEReturnEvent();
			int32_t RunIMEKeyDownEvent(int ikey);

			CWindow* RunKeyDownEvent(int ikey);
			int32_t RunKeyUpEvent(int ikey);
			int32_t RunPressEscapeKeyEvent();
			int32_t RunPressExitKeyEvent();

			virtual int32_t OnIMETabEvent();
			virtual int32_t OnIMEReturnEvent();
			virtual int32_t OnIMEKeyDownEvent(int ikey);

			virtual int32_t OnIMEChangeCodePage();
			virtual int32_t OnIMEOpenCandidateListEvent();
			virtual int32_t OnIMECloseCandidateListEvent();
			virtual int32_t OnIMEOpenReadingWndEvent();
			virtual int32_t OnIMECloseReadingWndEvent();

			virtual int32_t OnMouseLeftButtonDown();
			virtual int32_t OnMouseLeftButtonUp();
			virtual int32_t OnMouseLeftButtonDoubleClick();
			virtual int32_t OnMouseRightButtonDown();
			virtual int32_t OnMouseRightButtonUp();
			virtual int32_t OnMouseRightButtonDoubleClick();
			virtual int32_t OnMouseMiddleButtonDown();
			virtual int32_t OnMouseMiddleButtonUp();

			virtual int32_t OnKeyDown(int ikey);
			virtual int32_t OnKeyUp(int ikey);
			virtual int32_t OnPressEscapeKey();
			virtual int32_t OnPressExitKey();
			///////////////////////////////////////

			virtual void SetColor(uint32_t dwColor) {}
			virtual int32_t OnIsType(uint32_t dwType);
			/////////////////////////////////////

			virtual int32_t IsWindow() { return TRUE; }
			/////////////////////////////////////

		protected:
			std::string m_strName;

			EHorizontalAlign m_HorizontalAlign;
			EVerticalAlign m_VerticalAlign;
			long m_x, m_y;			  // X,Y 상대좌표
			long m_lWidth, m_lHeight; // 크기
			RECT m_rect;			  // Global 좌표
			RECT m_limitBiasRect;	  // limit bias 값

			bool m_bMovable;
			bool m_bShow;

			uint32_t m_dwFlag;

			PyObject* m_poHandler;

			CWindow* m_pParent;
			TWindowContainer m_pChildList;

			int32_t m_isUpdatingChildren;
			TWindowContainer m_pReserveChildList;

#ifdef _DEBUG
		public:
			uint32_t DEBUG_dwCounter;
#endif
	};

	class CLayer : public CWindow
	{
		public:
			CLayer(PyObject* ppyObject) : CWindow(ppyObject) {}
			virtual ~CLayer() {}

			int32_t IsWindow() { return FALSE; }
	};

	class CBox : public CWindow
	{
		public:
			CBox(PyObject* ppyObject);
			virtual ~CBox();

			void SetColor(uint32_t dwColor);

		protected:
			void OnRender();

		protected:
			uint32_t m_dwColor;
	};

	class CBar : public CWindow
	{
		public:
			CBar(PyObject* ppyObject);
			virtual ~CBar();

			void SetColor(uint32_t dwColor);

		protected:
			void OnRender();

		protected:
			uint32_t m_dwColor;
	};

	class CLine : public CWindow
	{
		public:
			CLine(PyObject* ppyObject);
			virtual ~CLine();

			void SetColor(uint32_t dwColor);

		protected:
			void OnRender();

		protected:
			uint32_t m_dwColor;
	};

	class CBar3D : public CWindow
	{
		public:
			static uint32_t Type();

		public:
			CBar3D(PyObject* ppyObject);
			virtual ~CBar3D();

			using CWindow::SetColor;

			void SetColor(uint32_t dwLeft, uint32_t dwRight, uint32_t dwCenter);

		protected:
			void OnRender();

		protected:
			uint32_t m_dwLeftColor;
			uint32_t m_dwRightColor;
			uint32_t m_dwCenterColor;
	};

	// Text
	class CTextLine : public CWindow
	{
		public:
			CTextLine(PyObject* ppyObject);
			virtual ~CTextLine();

			void SetMax(int iMax);
			void SetHorizontalAlign(int iType);
			void SetVerticalAlign(int iType);
			void SetSecret(int32_t bFlag);
			void SetOutline(int32_t bFlag);
			void SetFeather(int32_t bFlag);
			void SetMultiLine(int32_t bFlag);
			void SetFontName(const char* c_szFontName);
			void SetFontColor(uint32_t dwColor);
			void SetLimitWidth(float fWidth);

			void ShowCursor();
			void HideCursor();
			int GetCursorPosition();

			void SetText(const char* c_szText);
			const char* GetText();

			void GetTextSize(int* pnWidth, int* pnHeight);

		protected:
			void OnUpdate();
			void OnRender();
			void OnChangePosition();

			virtual void OnSetText(const char* c_szText);

		protected:
			CGraphicTextInstance m_TextInstance;
	};

	class CNumberLine : public CWindow
	{
		public:
			CNumberLine(PyObject* ppyObject);
			CNumberLine(CWindow* pParent);
			virtual ~CNumberLine();

			void SetPath(const char* c_szPath);
			void SetHorizontalAlign(int iType);
			void SetNumber(const char* c_szNumber);

		protected:
			void ClearNumber();
			void OnRender();
			void OnChangePosition();

		protected:
			std::string m_strPath;
			std::string m_strNumber;
			std::vector<CGraphicImageInstance*> m_ImageInstanceVector;

			int m_iHorizontalAlign;
			uint32_t m_dwWidthSummary;
	};

	// Image
	class CImageBox : public CWindow
	{
		public:
			CImageBox(PyObject* ppyObject);
			virtual ~CImageBox();

			int32_t LoadImage(const char* c_szFileName);
			void SetDiffuseColor(float fr, float fg, float fb, float fa);

			int GetWidth();
			int GetHeight();

		protected:
			virtual void OnCreateInstance();
			virtual void OnDestroyInstance();

			virtual void OnUpdate();
			virtual void OnRender();
			void OnChangePosition();

		protected:
			CGraphicImageInstance* m_pImageInstance;
	};
	class CMarkBox : public CWindow
	{
		public:
			CMarkBox(PyObject* ppyObject);
			virtual ~CMarkBox();

			void LoadImage(const char* c_szFilename);
			void SetDiffuseColor(float fr, float fg, float fb, float fa);
			void SetIndex(uint32_t uIndex);
			void SetScale(float fScale);

		protected:
			virtual void OnCreateInstance();
			virtual void OnDestroyInstance();

			virtual void OnUpdate();
			virtual void OnRender();
			void OnChangePosition();

		protected:
			CGraphicMarkInstance* m_pMarkInstance;
	};
	class CExpandedImageBox : public CImageBox
	{
		public:
			static uint32_t Type();

		public:
			CExpandedImageBox(PyObject* ppyObject);
			virtual ~CExpandedImageBox();

			void SetScale(float fx, float fy);
			void SetOrigin(float fx, float fy);
			void SetRotation(float fRotation);
			void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
			void SetRenderingMode(int iMode);

		protected:
			void OnCreateInstance();
			void OnDestroyInstance();

			virtual void OnUpdate();
			virtual void OnRender();

			int32_t OnIsType(uint32_t dwType);
	};
	class CAniImageBox : public CWindow
	{
		public:
			static uint32_t Type();

		public:
			CAniImageBox(PyObject* ppyObject);
			virtual ~CAniImageBox();

			void SetDelay(int iDelay);
			void AppendImage(const char* c_szFileName);
			void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
			void SetRenderingMode(int iMode);

			void ResetFrame();

		protected:
			void OnUpdate();
			void OnRender();
			void OnChangePosition();
			virtual void OnEndFrame();

			int32_t OnIsType(uint32_t dwType);

		protected:
			uint8_t m_bycurDelay;
			uint8_t m_byDelay;
			uint8_t m_bycurIndex;
			std::vector<CGraphicExpandedImageInstance*> m_ImageVector;
	};

	// Button
	class CButton : public CWindow
	{
		public:
			CButton(PyObject* ppyObject);
			virtual ~CButton();

			int32_t SetUpVisual(const char* c_szFileName);
			int32_t SetOverVisual(const char* c_szFileName);
			int32_t SetDownVisual(const char* c_szFileName);
			int32_t SetDisableVisual(const char* c_szFileName);

			const char* GetUpVisualFileName();
			const char* GetOverVisualFileName();
			const char* GetDownVisualFileName();

			void Flash();
			void Enable();
			void Disable();

			void SetUp();
			void Up();
			void Over();
			void Down();

			int32_t IsDisable();
			int32_t IsPressed();

		protected:
			void OnUpdate();
			void OnRender();
			void OnChangePosition();

			int32_t OnMouseLeftButtonDown();
			int32_t OnMouseLeftButtonDoubleClick();
			int32_t OnMouseLeftButtonUp();
			void OnMouseOverIn();
			void OnMouseOverOut();

			int32_t IsEnable();

			void SetCurrentVisual(CGraphicImageInstance* pVisual);

		protected:
			int32_t m_bEnable;
			int32_t m_isPressed;
			int32_t m_isFlash;
			CGraphicImageInstance* m_pcurVisual;
			CGraphicImageInstance m_upVisual;
			CGraphicImageInstance m_overVisual;
			CGraphicImageInstance m_downVisual;
			CGraphicImageInstance m_disableVisual;
	};
	class CRadioButton : public CButton
	{
		public:
			CRadioButton(PyObject* ppyObject);
			virtual ~CRadioButton();

		protected:
			int32_t OnMouseLeftButtonDown();
			int32_t OnMouseLeftButtonUp();
			void OnMouseOverIn();
			void OnMouseOverOut();
	};
	class CToggleButton : public CButton
	{
		public:
			CToggleButton(PyObject* ppyObject);
			virtual ~CToggleButton();

		protected:
			int32_t OnMouseLeftButtonDown();
			int32_t OnMouseLeftButtonUp();
			void OnMouseOverIn();
			void OnMouseOverOut();
	};
	class CDragButton : public CButton
	{
		public:
			CDragButton(PyObject* ppyObject);
			virtual ~CDragButton();

			void SetRestrictMovementArea(int ix, int iy, int iwidth, int iheight);

		protected:
			void OnChangePosition();
			void OnMouseOverIn();
			void OnMouseOverOut();

		protected:
			RECT m_restrictArea;
	};
};

extern int32_t g_bOutlineBoxEnable;
