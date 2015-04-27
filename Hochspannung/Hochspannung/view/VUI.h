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
	NON_COPYABLE(VUI);
	friend class VMaster;

private:
	VMaster* vMaster;

	//TODO (V) resize viewports?
	CRoot m_zr;
	CFrame m_zf;
	CScene m_zs;
	CPlacement m_zpCamera;
	CParallelLight m_zl;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	std::map<std::string, IViewScreen*> m_screens;
	std::map<std::string, IViewScreen*>::iterator m_iterScreens;

	bool isQuit;
	bool m_screenChanged = false;
	bool m_BlockCursorLeftPressed = false;

private:
	void handleInput(float fTimeDelta);
	std::map<int, std::vector<int>> pickElements();

public:
	VUI(VMaster* vMaster);
	virtual ~VUI() override;

	virtual void tick(const float fTimeDelta) override;

	virtual void onNotify(Event events) override;

	void addScreen(string sName, IViewScreen::ScreenType);
	void switchScreen(string switchTo);
	IViewScreen* getScreen(string sName);


	void initUI(HWND hwnd, CSplash* psplash);

	void resize(int width, int height);
	void updateMoney(const int wert);
	void updatePopulation(const int wert);
	void updateInfofield(const int wert);

	void checkGUIContainer(IViewGUIContainer* guiContainer);
};


NAMESPACE_VIEW_E
