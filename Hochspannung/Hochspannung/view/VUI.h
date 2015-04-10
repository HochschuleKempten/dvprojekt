#pragma once

#include "../logic/IVUI.h"
#include "../logic/IVTickObserver.h"
#include "VGeneral.h"
#include "IViewObserver.h"
#include "VScreen.h"
NAMESPACE_VIEW_B


class VMaster;

class VUI : public IVUI, public IVTickObserver,public IViewObserver
{
private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	std::map<std::string, VScreen*> m_screens;
	std::map<std::string, VScreen*>::iterator m_iterScreens;


	bool isQuit;

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

	void addScreen(string sName, VScreen::ScreenType);

	void switchScreen(string switchTo);
	VScreen* getScreen(string sName);

	virtual void onNotify(IViewObserver::Event);
};


NAMESPACE_VIEW_E
