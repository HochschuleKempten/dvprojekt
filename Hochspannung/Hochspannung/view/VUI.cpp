#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "IViewScreen.h"

#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenLobby.h"
#include "VScreenCredits.h"
#include "VScreenOptions.h"
#include "VIdentifier.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/LPowerLine.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "../logic/LSolarPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "../logic/LMaster.h"


NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster)
: vMaster(vMaster), isQuit(false), m_selectedBuilding(VIdentifier::Undefined)
{
	vMaster->registerObserver(this);
}

VUI::~VUI()
{}

void VUI::initUI(HWND hwnd, CSplash* psplash) 
{
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zr.AddFrameHere(&m_zf);

	m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);

	addScreen("MainMenue", IViewScreen::MainMenue);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Ingame", IViewScreen::Ingame);

	switchScreen("MainMenue");
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


	case SELECT_BUILDING_WINDMILL:
		updateInfofield("Windmill");
		m_selectedBuilding = VIdentifier::VWindmillPowerPlant;
		//TODO BuildMenue Button Windmill 
		break;
	case	SELECT_BUILDING_COALPOWERPLANT:
		updateInfofield("CoalPowerplant");
		m_selectedBuilding = VIdentifier::VCoalPowerPlant;
		//TODO BuildMenue Button CoalPowerplant 
		break;
	case	SELECT_BUILDING_OILPOWERPLANT:
		updateInfofield("OilPowerplant");
		m_selectedBuilding = VIdentifier::VOilRefinery;
		//TODO BuildMenue Button Oilpowerplant
		break;
	case	SELECT_BUILDING_NUCLEARPOWERPLANT:
		updateInfofield("NuclearPowerplant");
		m_selectedBuilding = VIdentifier::VNuclearPowerPlant;
		//TODO BuildMenue Button Nuclearpowerplant
		break;
	case	SELECT_BUILDING_HYDROPOWERPLANT:
		updateInfofield("HydroPowerplant");
		m_selectedBuilding = VIdentifier::VHydroelectricPowerPlant;
		//TODO BuildMenue Button Hydropowerplant
		break;
	case	SELECT_BUILDING_SOLARPOWERPLANT:
		updateInfofield("SolarPowerplant");
		m_selectedBuilding = VIdentifier::VSolarPowerPlant;
		//TODO BuildMenue Button Solarpowerplant
		break;
	case	SELECT_BUILDING_POWERLINE:
		updateInfofield("Powerline");
		m_selectedBuilding = VIdentifier::VPowerLine;
		//TODO BuildMenue Button Powerline
		break;
	default:
		m_selectedBuilding = VIdentifier::Undefined;
		break;
	}
	
}

void VUI::resize(int width, int height)
{

	
	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++)
	{
		m_iterScreens->second->resize(width, height);
	}

	m_zf.ReSize(width, height);

}

void VUI::addScreen(string sName, IViewScreen::ScreenType screenType)
{

	switch (screenType)
	{
	case IViewScreen::ScreenType::MainMenue:
		m_screens[sName] = new VScreenMainMenue(&m_zf);
		m_screens[sName]->addObserver(this);
		break;

	case IViewScreen::Lobby:
		m_screens[sName] = new VScreenLobby(&m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::ScreenType::Ingame:
		m_screens[sName] = new VScreenIngame(&m_zf,&m_zr,&m_zs,&m_zpCamera);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::Options: 
		m_screens[sName] = new VScreenOptions(&m_zf);
		m_screens[sName]->addObserver(this);
		break;
	case IViewScreen::Credits: 
		m_screens[sName] = new VScreenCredits(&m_zf);
		m_screens[sName]->addObserver(this);
		break;
	default: break;

	}
}

void VUI::switchScreen(string switchTo)
{
	map<string, IViewScreen*>::iterator it = m_screens.find(switchTo);
	ASSERT(it != m_screens.end(),"Screen not available");

	for (it = m_screens.begin(); it != m_screens.end(); it++) {
		it->second->switchOff();
	}

	m_screens[switchTo]->switchOn();
	m_screenChanged = true;
}


IViewScreen* VUI::getScreen(string sName)
{
	ASSERT(m_screens.find(sName) != m_screens.end(), "Screen"<< sName<< "not available");
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

void VUI::updateInfofield(string neuerText)
{
	dynamic_cast<VScreenIngame*>(m_screens["Ingame"])->updateInfofeld(neuerText);
}

void VUI::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
{
	float CurPosX;
	float CurPosY;
	m_zkCursor.GetFractional(CurPosX, CurPosY, false);
	map<string, IViewGUIContainer*> tempmapGuicontainer;
	map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
	map<string, IViewGUIObject*>tempList;
	map<string, IViewGUIObject*>::iterator tempIter;

	tempmapGuicontainer = tempGuicontainer->getGuiContainerMap();

	for (tempIterGuicontainer = tempmapGuicontainer.begin(); tempIterGuicontainer != tempmapGuicontainer.end(); tempIterGuicontainer++)
	{
		//Check if Container is on
		if (tempIterGuicontainer->second->isOn())
		{
			
			tempList = tempIterGuicontainer->second->getGuiObjectList();
			//for all GUI-Objects in the container
			for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++)
			{
				if (tempIter->second->isOn())
				{//check if cursor is over
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
					
				}
			}
			if (tempIterGuicontainer->second->getGuiContainerMap().size()>0)
		{
			checkGUIContainer(tempIterGuicontainer->second);
		}
		}

		
	}
	if (m_zkCursor.ButtonPressedLeft())
	{
		m_BlockCursorLeftPressed = true;
	}
}


void VUI::tick(const float fTimeDelta)
{
	m_zr.Tick(const_cast<float&>(fTimeDelta));


	handleInput(fTimeDelta);

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

			map<string, IViewGUIObject*>tempList;
			map<string, IViewGUIObject*>::iterator tempIter;
			//For all containers in the screen
			for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
			{
				
					//Check if Container is on
					if (tempIterGuicontainer->second->isOn())
					{
						tempList = tempIterGuicontainer->second->getGuiObjectList();
						//for all GUI-Objects in the container
						for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++)
						{

							if (tempIter->second->isOn())
							{
								//check if cursor is over
							//	tempIter->second->checkHover(CurPosX, CurPosY);

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
								
							}
							if (isQuit)return;

						}
						if (isQuit)return;
					}	
					if (tempIterGuicontainer->second->getGuiContainerMap().size() > 0)
				{
					checkGUIContainer(tempIterGuicontainer->second);
				}
				}
				if (isQuit)return;

			
			}
		}
	if (m_zkCursor.ButtonPressedLeft())
	{
		m_BlockCursorLeftPressed = true;
	}
	}




NAMESPACE_VIEW_E
