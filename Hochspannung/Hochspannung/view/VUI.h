#pragma once

#include "../logic/IVUI.h"
#include "../logic/IVTickObserver.h"
#include "VGeneral.h"
#include "IViewUIObserver.h"
#include "IViewScreen.h"
NAMESPACE_VIEW_B


class VMaster;

class VUI : public IVUI, public IVTickObserver,public IViewUIObserver
{
	friend class VMaster;

private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	std::map<std::string, IViewScreen*> m_screens;
	std::map<std::string, IViewScreen*>::iterator m_iterScreens;

	CViewport m_zv;
	CCamera m_zc;
	CPlacement m_zpCamera;
	CScene m_zs;
	CParallelLight m_zl;
	CBackground m_zb;

	bool isQuit;

	void handleInput(float fTimeDelta);

public:
	VUI(VMaster* vMaster, LUI* lUi);
	inline virtual ~VUI()
	{}

	void initUI();

	virtual void tick(const float fTimeDelta);
	

	void addScreen(string sName, IViewScreen::ScreenType);

	void switchScreen(string switchTo);
	IViewScreen* getScreen(string sName);

	virtual void onNotify(IViewUIObserver::Event);
};


NAMESPACE_VIEW_E
