#pragma once

#include "../logic/IVUI.h"
#include "../logic/IVTickObserver.h"
#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaster;

class VUI : public IVUI, public IVTickObserver
{
private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	void handleInput(float fTimeDelta);

public:
	VUI(VMaster* vMaster, LUI* lUi);
	inline virtual ~VUI()
	{}

	void initUI();

	inline virtual void tick(const float fTimeDelta)
	{
		handleInput(fTimeDelta);
	}

};


NAMESPACE_VIEW_E
