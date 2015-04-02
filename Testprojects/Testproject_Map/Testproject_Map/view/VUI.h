#pragma once

#include "../logic/IVUI.h"
#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class VUI : public IVUI
{
private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

public:
	inline VUI(VMaster* vMaster, LUI* lUi)
		: vMaster(vMaster), IVUI(lUi)
	{}
	inline virtual ~VUI()
	{}

	virtual void initUI();

	void handleInput(float fTimeDelta);
};


NAMESPACE_VIEW_E
