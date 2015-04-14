#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "VPowerLine.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VMaterialLoader.h"
#include "IViewScreen.h"

#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenSpielmodusWahl.h"


#include "VIdentifier.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/ILPowerLine.h"
#include "../logic/LMaster.h"


NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster, LUI* lUi)
	: vMaster(vMaster), IVUI(lUi), isQuit(false)
{
	vMaster->setVUI(this);
	vMaster->registerObserver(this);
}

void VUI::initUI()
{
	vMaster->m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	vMaster->m_zf.AddDeviceCursor(&m_zkCursor);
	vMaster->m_zf.AddDeviceMouse(&m_zkMouse);

	vMaster->m_zr.AddFrameHere(&vMaster->m_zf);

	
	


	//Camera (WASD) settings
	m_zkKeyboard.SetWASDTranslationSensitivity(20.0);
	m_zkKeyboard.SetWASDRotationSensitivity(2.0);
	m_zkKeyboard.SetWASDLevelMin(100.0);
	m_zkKeyboard.SetWASDLevelMax(200.0);

	addScreen("MainMenue", IViewScreen::MainMenue);
	
	addScreen("Spielmoduswahl", IViewScreen::Spielmoduswahl);
	
	addScreen("Ingame", IViewScreen::Ingame);
	
	switchScreen("MainMenue");
}

void VUI::handleInput(float fTimeDelta)
{
	m_zkKeyboard.PlaceWASD(m_zpCamera, fTimeDelta);

	//TODO (JS) make power line clickable

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

					vMaster->getPlayingField()->tryBuildOnField<LPowerLine>(x, y, ILPowerLine::EAST);
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



void VUI::onNotify(IViewUIObserver::Event evente)
{
	DEBUG_OUTPUT("Nachricht bei GUI-Observer angekommen\n");
	switch (evente)
	{

	case IViewUIObserver::START_GAME:
		DEBUG_OUTPUT("STARTING GAME.........\n");
		vMaster->lMaster->startNewGame();
		switchScreen("Ingame"); //TODO Button Action erweitern um switchscreen event damit Screen nicht hardcoded Ingame sein muss
		break;
	case IViewUIObserver::MainOptions:
		DEBUG_OUTPUT("Open Options from MainMenue.........\n");
		break;
	case IViewUIObserver::QUIT_GAME:
		isQuit = true;
		PostQuitMessage(0);
		DEBUG_OUTPUT("Quit Game.........\n");
		break;
		
	case IViewUIObserver::SWITCH_TO_SPIELMODUS:
		
		switchScreen("Spielmoduswahl");
		break;
	case IViewUIObserver::SWITCH_TO_MAINMENUE:

		switchScreen("MainMenue");
		break;
	default:
		DEBUG_OUTPUT("Keine Lösung gefunden\n");
	}

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
	case IViewScreen::ScreenType::Ingame:
		m_screens[sName] = new VScreenIngame(&vMaster->m_zf,&vMaster->m_zr,&m_zs,&m_zpCamera);
		m_screens[sName]->addObserver(this);
		break;

	}
}

void VUI::switchScreen(string switchTo)
{
	map<string, IViewScreen*>::iterator it = m_screens.find(switchTo);
	ASSERT(it != m_screens.end(),"Screen not available");

	for (it = m_screens.begin(); it != m_screens.end(); it++)
	{
		it->second;
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

void VUI::aktualisiereGeld(const int& wert)
{

}
void VUI::aktualisiereBev(const int& wert)
{

}

void VUI::aktualisiereInfo(const int& wert)
{

}

void VUI::tick(const float fTimeDelta)
{
	handleInput(fTimeDelta);

	float CurPosX;
	float CurPosY;
	m_zkCursor.GetFractional(CurPosX, CurPosY, false);
	map<string, IViewGUIContainer*> tempGuicontainer;
	map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++)
	{
		if (m_iterScreens->second->isOn())
		{
			m_iterScreens->second->checkShortcut(&m_zkKeyboard);
			tempGuicontainer = m_iterScreens->second->getGuiContainerMap();
			list<IViewGUIObject*>tempList;
			list<IViewGUIObject*>::iterator tempIter;
			for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
			{
				if (tempIterGuicontainer->second->isOn())
				{
					tempList = tempIterGuicontainer->second->getGuiObjectList();

					for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++)
					{
						(*tempIter)->checkHover(CurPosX, CurPosY);
						(*tempIter)->checkPressed(CurPosX, CurPosY, m_zkCursor.ButtonPressedLeft());
						if (m_screenChanged)
						{
							m_screenChanged = false;
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
