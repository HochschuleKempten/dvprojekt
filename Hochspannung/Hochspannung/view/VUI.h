#pragma once

#include "VGeneral.h"
#include "IViewUIObserver.h"
#include "IViewScreen.h"
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
class VUI : public IVTickObserver, public IViewUIObserver
{
	friend class VMaster;

private:
	VMaster* vMaster;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	std::map<std::string, IViewScreen*> m_screens;
	std::map<std::string, IViewScreen*>::iterator m_iterScreens;

	//TODO (V) resize viewports?
	CPlacement m_zpCamera;
	CScene m_zs;
	CParallelLight m_zl;

	bool isQuit;
	bool m_screenChanged = false;
	void handleInput(float fTimeDelta);
	bool m_BlockCursorLeftPressed=false;

public:
	VUI(VMaster* vMaster);
	virtual ~VUI();

	void initUI();

	virtual void tick(const float fTimeDelta) override;
	

	void addScreen(string sName, IViewScreen::ScreenType);

	void switchScreen(string switchTo);
	IViewScreen* getScreen(string sName);

	virtual void onNotify(IViewUIObserver::Event) override;
	void resize(int width, int height);

	void updateMoney(const int wert);
	void updatePopulation(const int wert);
	void updateInfofield(const int wert);

	void checkGUIContainer(IViewGUIContainer* guiContainer);
};


NAMESPACE_VIEW_E
