#pragma once

#include <Neoeter/Python/Bindings/PythonSlotWindow.h>

namespace UI
{
	class CGridSlotWindow : public CSlotWindow
	{
		public:
			static uint32_t Type();

		public:
			CGridSlotWindow(PyObject* ppyObject);
			virtual ~CGridSlotWindow();

			void Destroy();

			void ArrangeGridSlot(uint32_t dwStartIndex, uint32_t dwxCount, uint32_t dwyCount, int ixSlotSize, int iySlotSize, int ixTemporarySize, int iyTemporarySize);

		protected:
			void __Initialize();

			int32_t GetPickedSlotPointer(TSlot** ppSlot);
			int32_t GetPickedSlotList(int iWidth, int iHeight, std::list<TSlot*>* pSlotPointerList);
			int32_t GetGridSlotPointer(int ix, int iy, TSlot** ppSlot);
			int32_t GetPickedGridSlotPosition(int ixLocal, int iyLocal, int* pix, int* piy);
			int32_t CheckMoving(uint32_t dwSlotNumber, uint32_t dwItemIndex, const std::list<TSlot*>& c_rSlotList);

			int32_t OnIsType(uint32_t dwType);

			void OnRefreshSlot();
			void OnRenderPickingSlot();

		protected:
			uint32_t m_dwxCount;
			uint32_t m_dwyCount;

			std::vector<TSlot*> m_SlotVector;
	};
};
