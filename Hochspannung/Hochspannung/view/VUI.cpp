#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "IViewScreen.h"
#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenLobby.h"
#include "VScreenCredits.h"
#include "VScreenOptions.h"
#include "../logic/LMaster.h"

NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster)
	: vMaster(vMaster), isQuit(false)
{
	vMaster->registerObserver(this);
}

VUI::~VUI()
{}

void VUI::initUI(HWND hwnd, CSplash* psplash)
{
	//TODO (V) clean up
	m_zr.Init(psplash);
	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput, eApiSound_DirectSound, eShaderCreation_ForceCompile, eShaderAutoRecompilation_Disabled);
	m_zr.AddFrameHere(&m_zf);

	m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);

	addScreen("MainMenue", IViewScreen::MainMenue);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Ingame", IViewScreen::Ingame);

	for (const std::pair<std::string, IViewScreen*>& screenPair : m_screens) {
		screenPair.second->switchOff();
	}

	activeScreen = getScreen("MainMenue");
	switchScreen("MainMenue");
}

void VUI::onNotify(Event evente)
{
	switch (evente) {
		case START_GAME:
			vMaster->lMaster->startNewGame();
			switchScreen("Ingame");
			break;
		case QUIT_GAME:
			isQuit = true;
			PostQuitMessage(0);
			break;
		case SEARCH_IP:
			break;

			/*case SWITCH_TO_SPIELMODUS:
		
		switchScreen("Spielmoduswahl");
		break;*/
		case SWITCH_TO_LOBBY:
			switchScreen("Lobby");
			break;
		case SWITCH_TO_MAINMENUE:
			switchScreen("MainMenue");
			break;
		case SWITCH_TO_CREDITS:
			switchScreen("Credits");
			break;
		case SWITCH_TO_OPTIONS:
			switchScreen("Options");
			break;
		default:
			break;
	}
}

void VUI::resize(int width, int height)
{
	m_zf.ReSize(width, height);
	activeScreen->resize(width, height);

	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++) {
		m_iterScreens->second->resize(width, height);
	}
}

void VUI::addScreen(const string& sName, const IViewScreen::ScreenType screenType)
{
	switch (screenType) {
		case IViewScreen::ScreenType::MainMenue:
			m_screens[sName] = new VScreenMainMenue(this);
			m_screens[sName]->addObserver(this);
			break;

		case IViewScreen::Lobby:
			m_screens[sName] = new VScreenLobby(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::ScreenType::Ingame:
			m_screens[sName] = new VScreenIngame(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Options:
			m_screens[sName] = new VScreenOptions(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Credits:
			m_screens[sName] = new VScreenCredits(this);
			m_screens[sName]->addObserver(this);
			break;
		default: break;

	}
}

void VUI::switchScreen(const std::string& switchTo)
{
	ASSERT(activeScreen != nullptr, "No screen is initalized");
	ASSERT(m_screens.count(switchTo) > 0, "Screen" << switchTo << "not available");

	activeScreen->switchOff();
	activeScreen = m_screens[switchTo];
	activeScreen->switchOn();
}

IViewScreen* VUI::getScreen(const std::string& sName)
{
	ASSERT(m_screens.count(sName) > 0, "Screen" << sName << "not available");
	return m_screens[sName];
}

void VUI::updateMoney(const int wert)
{
	dynamic_cast<VScreenIngame*>(m_screens["Ingame"])->updateMoney(wert);
}

void VUI::updatePopulation(const int wert)
{
	dynamic_cast<VScreenIngame*>(m_screens["Ingame"])->updatePopulation(wert);
}

void VUI::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
{
	//TODO (UI) clean up
	float CurPosX;
	float CurPosY;
	m_zkCursor.GetFractional(CurPosX, CurPosY, false);
	map<string, IViewGUIContainer*> tempmapGuicontainer;
	map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
	map<string, IViewGUIObject*> tempList;
	map<string, IViewGUIObject*>::iterator tempIter;

	tempmapGuicontainer = tempGuicontainer->getGuiContainerMap();

	for (tempIterGuicontainer = tempmapGuicontainer.begin(); tempIterGuicontainer != tempmapGuicontainer.end(); tempIterGuicontainer++) {
		//Check if Container is on
		if (tempIterGuicontainer->second->isOn()) {

			tempList = tempIterGuicontainer->second->getGuiObjectList();
			//for all GUI-Objects in the container
			for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++) {
				if (tempIter->second->isOn()) {//check if cursor is over
					tempIter->second->checkHover(CurPosX, CurPosY);

					if (!m_BlockCursorLeftPressed) {
						//check for events
						tempIter->second->checkEvent(&m_zkCursor, &m_zkKeyboard);
					}

					//if screen was changed
					if (m_screenChanged) {
						m_screenChanged = false;
						m_BlockCursorLeftPressed = true;
						return;
					}

				}
			}
			if (tempIterGuicontainer->second->getGuiContainerMap().size() > 0) {
				checkGUIContainer(tempIterGuicontainer->second);
			}
		}


	}
	if (m_zkCursor.ButtonPressedLeft()) {
		m_BlockCursorLeftPressed = true;
	}
}


void VUI::tick(const float fTimeDelta)
{
	m_zr.Tick(const_cast<float&>(fTimeDelta));
	activeScreen->tick();

	//TODO (UI) move to classes
	float CurPosX;
	float CurPosY;
	m_zkCursor.GetFractional(CurPosX, CurPosY, false);

	//One Click
	if (!m_zkCursor.ButtonPressedLeft()) {
		m_BlockCursorLeftPressed = false;
	}
	//For all screens...
	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++) {
		map<string, IViewGUIContainer*> tempGuicontainer;
		map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
		//Check if screen is on
		if (m_iterScreens->second->isOn()) {
			//Check for shortcuts
			m_iterScreens->second->checkShortcut(&m_zkKeyboard);
			m_iterScreens->second->checkSpecialEvent(&m_zkCursor);
			tempGuicontainer = m_iterScreens->second->getGuiContainerMap();

			map<string, IViewGUIObject*> tempList;
			map<string, IViewGUIObject*>::iterator tempIter;
			//For all containers in the screen
			for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++) {

				//Check if Container is on
				if (tempIterGuicontainer->second->isOn()) {
					tempList = tempIterGuicontainer->second->getGuiObjectList();
					//for all GUI-Objects in the container
					for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++) {

						if (tempIter->second->isOn()) {
							//check if cursor is over
							//	tempIter->second->checkHover(CurPosX, CurPosY);

							if (!m_BlockCursorLeftPressed) {
								//check for events
								tempIter->second->checkEvent(&m_zkCursor, &m_zkKeyboard);
							}
							//if screen was changed
							if (m_screenChanged) {
								m_screenChanged = false;
								m_BlockCursorLeftPressed = true;
								return;
							}

						}
						if (isQuit)return;

					}
					if (isQuit)return;
				}
				if (tempIterGuicontainer->second->getGuiContainerMap().size() > 0) {
					checkGUIContainer(tempIterGuicontainer->second);
				}
			}
			if (isQuit)return;


		}
	}
	if (m_zkCursor.ButtonPressedLeft()) {
		m_BlockCursorLeftPressed = true;
	}
}


NAMESPACE_VIEW_E
