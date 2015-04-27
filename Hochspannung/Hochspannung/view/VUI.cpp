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
#include <Vektoria/Placements.h>

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
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zr.AddFrameHere(&m_zf);

	m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);

	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
	          CColor(1.0f, 1.0f, 1.0f));

	addScreen("MainMenue", IViewScreen::MainMenue);
	//addScreen("Spielmoduswahl", IViewScreen::Spielmoduswahl);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Ingame", IViewScreen::Ingame);

	//TODO (V) Sometimes no main screen appears
	switchScreen("MainMenue");
}

void VUI::handleInput(float fTimeDelta)
{
	//Left + Right: 
	if (m_zkKeyboard.KeyPressed(DIK_A) == true) {
		m_zpCamera.TranslateXDelta(-0.5);

	}
	if (m_zkKeyboard.KeyPressed(DIK_D)) {
		m_zpCamera.TranslateXDelta(0.5);
	}

	//Back + Forward
	if (m_zkKeyboard.KeyPressed(DIK_S) == true) {
		m_zpCamera.TranslateYDelta(-0.5);
	}
	if (m_zkKeyboard.KeyPressed(DIK_W)) {
		m_zpCamera.TranslateYDelta(0.5);
	}

	//Zoom In + Out
	if (m_zkKeyboard.KeyPressed(DIK_UP) == true) {
		m_zpCamera.TranslateZDelta(-0.5);
	}
	if (m_zkKeyboard.KeyPressed(DIK_DOWN)) {
		m_zpCamera.TranslateZDelta(0.5);
	}

	float zDelta = GET_WHEEL_DELTA_WPARAM(WHEEL_DELTA);

	if (zDelta != 0) {
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

	std::map<int, std::vector<int>> pickedElements = pickElements();
	if (pickedElements.count(VIdentifier::VPlayingField) > 0) {
		vMaster->getPlayingField()->hoverField(pickedElements[VIdentifier::VPlayingField][0], pickedElements[VIdentifier::VPlayingField][1]);
	}

	static bool clickActive = false;
	if (m_zkCursor.ButtonPressedLeft()) {
		if (!clickActive) {

			if (pickedElements.count(VIdentifier::VPlayingField) > 0) {
				vMaster->getPlayingField()->tryBuildOnField<LPowerLine>(pickedElements[VIdentifier::VPlayingField][0],
				                                                        pickedElements[VIdentifier::VPlayingField][1],
				                                                        ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);
			}

			clickActive = true;
		}
	}
	else if (m_zkCursor.ButtonPressedRight()) {
		if (!clickActive) {

			if (pickedElements.count(VIdentifier::VPlayingField) > 0) {
				vMaster->getPlayingField()->tryBuildOnField<LWindmillPowerPlant>(pickedElements[VIdentifier::VPlayingField][0],
				                                                                 pickedElements[VIdentifier::VPlayingField][1]);
			}
			else if (pickedElements.count(VIdentifier::VPowerLine) > 0) {
				vMaster->getPlayingField()->tryRemoveObject(pickedElements[VIdentifier::VPowerLine][0],
				                                            pickedElements[VIdentifier::VPowerLine][1]);
			}
			else if (pickedElements.count(VIdentifier::VWindmillPowerPlant) > 0) {
				vMaster->getPlayingField()->tryRemoveObject(pickedElements[VIdentifier::VWindmillPowerPlant][0],
				                                            pickedElements[VIdentifier::VWindmillPowerPlant][1]);
			}

			clickActive = true;
		}
	}
	else {
		clickActive = false;
	}
}

std::map<int, std::vector<int>> VUI::pickElements()
{
	std::map<int, std::vector<int>> pickedElements;

	CPlacements placements;
	CPlacement* singlePlacement = m_zkCursor.PickPlacement();
	m_zkCursor.PickPlacements(&placements);

	//The two placements pick different things, so they have to be merged together
	if (singlePlacement != nullptr) {
		placements.Add(singlePlacement);
	}

	//Now iterate over every found placement
	for (int i = 0; i < placements.m_iPlacements; i++) {
		std::vector<std::string> nameParts = split(placements.m_applacement[i]->GetName(), ';');

		if (nameParts.size() > 0 && nameParts[0].at(0) != '#') {
			//At this point only valid names remain
			ASSERT(nameParts.size() == 3, "Not enough arguments in the placement name");

			//Convert the arguments to integer (skip the first one, because its the key for the map
			std::vector<int> namePartsInt;
			for (size_t j = 1; j < nameParts.size(); j++) {
				namePartsInt.emplace_back(std::stoi(nameParts[j]));
			}

			pickedElements[std::stoi(nameParts[0])] = namePartsInt;
		}
	}

	return pickedElements;
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
		//TODO BuildMenue Button Windmill 
		break;
	case	SELECT_BUILDING_COALPOWERPLANT:
		//TODO BuildMenue Button CoalPowerplant 
		break;
	case	SELECT_BUILDING_OILPOWERPLANT:
		//TODO BuildMenue Button Oilpowerplant
		break;
	case	SELECT_BUILDING_NUCLEARPOWERPLANT:
		//TODO BuildMenue Button Nuclearpowerplant
		break;
	case	SELECT_BUILDING_HYDROPOWERPLANT:
		//TODO BuildMenue Button Hydropowerplant
		break;
	case	SELECT_BUILDING_SOLARPOWERPLANT:
		//TODO BuildMenue Button Solarpowerplant
		break;
	case	SELECT_BUILDING_POWERLINE:
		//TODO BuildMenue Button Powerline
		break;
	default:
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
	/*case IViewScreen::ScreenType::Spielmoduswahl:
		m_screens[sName] = new VScreenSpielmodusWahl(&vMaster->m_zf);
		m_screens[sName]->addObserver(this);
		break;*/
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

void VUI::updateInfofield(const int wert)
{}

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
