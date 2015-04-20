#pragma once

#include "VGeneral.h"
#include "IViewObserver.h"
#include "VScreen.h"
#include "../logic/IVTickObserver.h"

NAMESPACE_VIEW_B


class VMaster;

/**
 * @brief The VUI class is responsible for representing the interface to the user and handles the user input.
 *
 * The Vektoria-Objects can have a name (<code>.setName()</code>). This is needed to find out what elements have been clicked by the user.
 * To distinct between needed names for the game logic and names for debugging purposes, all debug names shall start with a # to
 * introduce a comment in the name system.
 */
class VUI : public IVTickObserver, public IViewObserver
{
	friend class VMaster;

private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	std::map<std::string, VScreen*> m_screens;
	std::map<std::string, VScreen*>::iterator m_iterScreens;

	CViewport m_zv;
	CCamera m_zc;
	CPlacement m_zpCamera;
	CScene m_zs;
	CParallelLight m_zl;
	CBackground m_zb;

	bool isQuit;

	void handleInput(float fTimeDelta);

public:
	VUI(VMaster* vMaster);
	virtual ~VUI();

	void initUI();

	virtual void tick(const float fTimeDelta);
	

	void addScreen(string sName, VScreen::ScreenType);

	void switchScreen(string switchTo);
	VScreen* getScreen(string sName);

	virtual void onNotify(IViewObserver::Event);
};


NAMESPACE_VIEW_E
