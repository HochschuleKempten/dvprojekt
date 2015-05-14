#pragma once

#include "VGeneral.h"
#include "IViewUIObserver.h"
#include "IViewScreen.h"
#include "../logic/IVTickObserver.h"

NAMESPACE_VIEW_B


class VMaster;
class VScreenIngame;
class VScreenMainMenue;
class VScreenOptions;
class VScreenCredits;
class VScreenLobby;

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
	friend class VScreenIngame;
	friend class VScreenMainMenue;
	friend class VScreenOptions;
	friend class VScreenCredits;
	friend class VScreenLobby;

private:
	VMaster* vMaster;

	//TODO (V) resize viewports?
	CRoot m_zr;
	CFrame m_zf;
	CDeviceKeyboard m_zkKeyboard;
	CDeviceCursor m_zkCursor;
	CDeviceMouse m_zkMouse;

	IViewScreen* activeScreen = nullptr;
	std::map<std::string, IViewScreen*> m_screens;
	std::map<std::string, IViewScreen*>::iterator m_iterScreens;

	bool isQuit;
	bool m_screenChanged = false;
	bool m_BlockCursorLeftPressed = false;

public:
	explicit VUI(VMaster* vMaster);
	virtual ~VUI() override;

	virtual void tick(const float fTimeDelta) override;

	virtual void onNotify(Event events) override;

	void addScreen(const std::string& sName, const IViewScreen::ScreenType);
	void switchScreen(const std::string& switchTo);
	IViewScreen* getScreen(const std::string& sName);

	void initUI(HWND hwnd, CSplash* psplash);

	void resize(int width, int height);
	void updateMoney(const int wert);
	void updatePopulation(const int wert);

	//void checkGUIContainer(IViewGUIContainer* guiContainer);
};


NAMESPACE_VIEW_E
