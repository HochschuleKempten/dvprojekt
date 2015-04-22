#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "VPowerLine.h"
#include "IViewScreen.h"

#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenSpielmodusWahl.h"
#include "VScreenLobby.h"
#include "VScreenCredits.h"
#include "VScreenOptions.h"
#include "VIdentifier.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/ILPowerLine.h"
#include "../logic/LMaster.h"

NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster)
	: vMaster(vMaster), isQuit(false)
{
	vMaster->registerObserver(this);
}

VUI::~VUI()
{}

void VUI::initUI()
{
	vMaster->m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	vMaster->m_zf.AddDeviceCursor(&m_zkCursor);
	vMaster->m_zf.AddDeviceMouse(&m_zkMouse);

	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
	CColor(1.0f, 1.0f, 1.0f));

	addScreen("MainMenue", IViewScreen::MainMenue);
	addScreen("Spielmoduswahl", IViewScreen::Spielmoduswahl);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Ingame", IViewScreen::Ingame);
	
	//TODO (V) Sometimes no main screen appears
	switchScreen("MainMenue");
}

void VUI::handleInput(float fTimeDelta)
{
	//m_zkKeyboard.PlaceWASD(m_zpCamera, fTimeDelta);

	//TODO (JS) make power line clickable


	//Left + Right: 
	if (m_zkKeyboard.KeyPressed(DIK_A) == true)
	{
		m_zpCamera.TranslateXDelta(-0.5);

	}
	if (m_zkKeyboard.KeyPressed(DIK_D))
	{
		m_zpCamera.TranslateXDelta(0.5);
	}

	//Back + Forward
	if (m_zkKeyboard.KeyPressed(DIK_S) == true)
	{
		m_zpCamera.TranslateYDelta(-0.5);
	}
	if (m_zkKeyboard.KeyPressed(DIK_W))
	{
		m_zpCamera.TranslateYDelta(0.5);
	}

	//Zoom In + Out
	if (m_zkKeyboard.KeyPressed(DIK_UP) == true)
	{
		m_zpCamera.TranslateZDelta(-0.5);
	}
	if (m_zkKeyboard.KeyPressed(DIK_DOWN))
	{
		m_zpCamera.TranslateZDelta(0.5);
	}

	float zDelta = GET_WHEEL_DELTA_WPARAM(WHEEL_DELTA);

	if (zDelta != 0)
	{
	  // m_zpCamera.RotateZDelta(-0.05);
	}

	//if (m_zkMouse.ButtonPressed(DIMOUSE_WHEEL) == true)
	//{	
	//	//long delta = ?
	//	
	//}

	// Rotate around the field
	//if (m_zkKeyboard.KeyPressed(DIK_RIGHT) == true)
	//{
	//	m_zpCamera.RotateZDelta(-0.05);
	//}
	//if (m_zkKeyboard.KeyPressed(DIK_LEFT))
	//{
	//	m_zpCamera.RotateZDelta(0.05);
	//}



	/* Picking */
	static bool pickingActive = false;
	 
	if (m_zkCursor.ButtonPressedLeft()) {
		if (!pickingActive) {

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}
			
			DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());
			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() == 3) {

				if (std::stoi(koord[0]) == VIdentifier::VPlayingField) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					int x = std::stoi(koord[1]);
					int y = std::stoi(koord[2]);

					//TODO (V) will the power lines be connected automatically or must the user do the connection by itself
					vMaster->getPlayingField()->tryBuildOnField<LPowerLine>(x, y, ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);
				}

			}

			pickingActive = true;
		}
	}
	else if (m_zkCursor.ButtonPressedRight()) {
		if (!pickingActive) {

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}

			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() == 3) {
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (std::stoi(koord[0]) == VIdentifier::VPlayingField) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					vMaster->getPlayingField()->tryBuildOnField<LWindmillPowerPlant>(std::stoi(koord[1]), std::stoi(koord[2]));
				}
				else if (std::stoi(koord[0]) == VIdentifier::VPowerLine) {
					vMaster->getPlayingField()->tryRemoveObject(std::stoi(koord[1]), std::stoi(koord[2]));
				}
				else if (std::stoi(koord[0]) == VIdentifier::VHydroelectricPowerPlant) {
					vMaster->getPlayingField()->tryRemoveObject(std::stoi(koord[1]), std::stoi(koord[2]));
				}

			}

			pickingActive = true;
		}
	}
	else {
		pickingActive = false;
	}
}



void VUI::onNotify(Event evente)
{
	switch (evente)
	{

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
		
	case SWITCH_TO_SPIELMODUS:
		
		switchScreen("Spielmoduswahl");
		break;
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
}

void VUI::addScreen(string sName, IViewScreen::ScreenType screenType)
{
	switch (screenType)
	{
	case IViewScreen::ScreenType::MainMenue:
		m_screens[sName] = new VScreenMainMenue(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::ScreenType::Spielmoduswahl:
		m_screens[sName] = new VScreenSpielmodusWahl(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::Lobby:
		m_screens[sName] = new VScreenLobby(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::ScreenType::Ingame:
		m_screens[sName] = new VScreenIngame(&vMaster->m_zf,&vMaster->m_zr,&m_zs,&m_zpCamera);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::Options: 
		m_screens[sName] = new VScreenOptions(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::Credits: 
		m_screens[sName] = new VScreenCredits(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;
	default: break;
	}
}

void VUI::switchScreen(string switchTo)
{
	map<string, IViewScreen*>::iterator it = m_screens.find(switchTo);
	ASSERT(it != m_screens.end(),"Screen not available");
	
	for (it = m_screens.begin(); it != m_screens.end(); it++)
	{
		it->second->switchOff();
	}

	m_screens[switchTo]->switchOn();
	m_screenChanged = true;

}


IViewScreen* VUI::getScreen(string sName)
{
	ASSERT(m_screens.find(sName) != m_screens.end(), "Screen"<< sName<< "not available");
	return	m_screens[sName];
}

void VUI::updateMoney(const int wert)
{
	dynamic_cast<VScreenIngame*>(m_screens["Ingame"])->updateMoney(wert);
}
void VUI::updatePopulation(const int wert)
{
	dynamic_cast<VScreenIngame*>(m_screens["Ingame"])->updatePopulation(wert);
}

void VUI::updateInfofield(const int wert)
{

}

void VUI::tick(const float fTimeDelta)
{
	/*static unsigned int money = 0;
	static unsigned int pop = 0;
	updateMoney(money++);
	updatePopulation(pop++);*/
	handleInput(fTimeDelta);

	float CurPosX;
	float CurPosY;
	m_zkCursor.GetFractional(CurPosX, CurPosY, false);
	
	//One Click
	if (!m_zkCursor.ButtonPressedLeft())
	{
		m_BlockCursorLeftPressed = false;
	}
	//For all screens...
	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++)
	{
		map<string, IViewGUIContainer*> tempGuicontainer;
		map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
		//Check if screen is on
		if (m_iterScreens->second->isOn())
		{
			//Check for shortcuts
			m_iterScreens->second->checkShortcut(&m_zkKeyboard);
			
			tempGuicontainer = m_iterScreens->second->getGuiContainerMap();
			map<string,IViewGUIObject*>tempList;
			map<string,IViewGUIObject*>::iterator tempIter;
			//For all containers in the screen
			for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
			{
				//Check if screen is on
				if (tempIterGuicontainer->second->isOn())
				{
					tempList = tempIterGuicontainer->second->getGuiObjectList();
					//for all GUI-Objects in the container
					for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++)
					{
					
						//check if cursor is over
						tempIter->second->checkHover(CurPosX, CurPosY);
						
						if (!m_BlockCursorLeftPressed)
						{
							//check for events
							tempIter->second->checkEvent(&m_zkCursor, &m_zkKeyboard);
						}
						//if screen was changed
						if (m_screenChanged)
						{
							m_screenChanged = false;
							m_BlockCursorLeftPressed = true;
							return;
						}
						if (isQuit)return;
					}
					if (isQuit)return;
				}
			}
			if (isQuit)return;
		}
	}
	
}


NAMESPACE_VIEW_E
