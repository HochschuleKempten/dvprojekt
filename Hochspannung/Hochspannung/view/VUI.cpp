#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VMaterialLoader.h"
#include "VScreenMainMenue.h"
#include "VScreenIngame.h"


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

	
	addScreen("MainMenue", IViewScreen::MainMenue);
	
	addScreen("Ingame", IViewScreen::Ingame);
	
	switchScreen("MainMenue");
}

void VUI::handleInput(float fTimeDelta)
{
	m_zkKeyboard.PlaceWASD(m_zpCamera, fTimeDelta);
	m_zkKeyboard.SetWASDTranslationSensitivity(100.0);
	m_zkKeyboard.SetWASDRotationSensitivity(2.0);
    m_zkKeyboard.SetWASDLevelMin(100.0);
	m_zkKeyboard.SetWASDLevelMax(200.0);




	/* Picking */
	static bool pickingActive = false;

	if (m_zkCursor.ButtonPressedLeft()) {
		if (!pickingActive) {
			float f;

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}

			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() > 0) {
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (koord[0] == getClassName(VPlayingField)) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					int x = std::stoi(koord[1]);
					int y = std::stoi(koord[2]);

					dynamic_cast<VPlayingField*>(vMaster->views[getClassName(VPlayingField)])->tryBuildOnField<LCoalPowerPlant>(x, y);
				}

			}

			pickingActive = true;
		}
	}
	else if (m_zkCursor.ButtonPressedRight()) {
		if (!pickingActive) {
			float f;

			CPlacement *pickedPlacement = m_zkCursor.PickPlacement();
			if (pickedPlacement == nullptr) {
				return;
			}

			std::vector<std::string> koord = split(pickedPlacement->GetName(), ';');

			if (koord.size() > 0) {
				DEBUG_OUTPUT("picked object = " << pickedPlacement->GetName());

				if (koord[0] == getClassName(VPlayingField)) {
					ASSERT(koord.size() == 3, "Not enough arguments in the placement name");

					dynamic_cast<VPlayingField*>(vMaster->views[getClassName(VPlayingField)])->tryBuildOnField<LHydroelectricPowerPlant>(std::stoi(koord[1]), std::stoi(koord[2]));
				}
				else if (koord[0] == getClassName(VCoalPowerPlant)) {
					vMaster->getPlayingField()->tryRemoveObject(std::stoi(koord[1]), std::stoi(koord[2]));
				}
				else if (koord[0] == getClassName(VHydroelectricPowerPlant)) {
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
	OutputDebugString("Nachricht bei GUI-Observer angekommen\n");
	switch (evente)
	{
	case IViewUIObserver::START_GAME:
		OutputDebugString("STARTING GAME.........\n");
		switchScreen("Ingame"); //TODO Button Action erweitern um switchscreen event damit Screen nicht hardcoded Ingame sein muss	
		break;
	case IViewUIObserver::MainOptions:
		OutputDebugString("Open Options from MainMenue.........\n");
		//m_writing.PrintF("Change Screen to Options");
		break;
	case IViewUIObserver::QUIT_GAME:
		isQuit = true;
		PostQuitMessage(0);
		OutputDebugString("Quit Game.........\n");
		break;
		// Handle other events...
	default:
		OutputDebugString("Keine Lösung gefunden\n");
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
		it->second->switchOff();

	}

	m_screens[switchTo]->switchOn();

}


IViewScreen* VUI::getScreen(string sName)
{
	ASSERT(m_screens.find(sName) != m_screens.end(), "Screen"<< sName<< "not available");
	return	m_screens[sName];
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
			tempGuicontainer = m_iterScreens->second->getGuiContainerMap();
			list<IViewGUIObject*>tempList;
			list<IViewGUIObject*>::iterator tempIter;
			for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
			{
				tempList = tempIterGuicontainer->second->getGuiObjectList();

				for (tempIter = tempList.begin(); tempIter != tempList.end(); tempIter++)
				{
					(*tempIter)->checkHover(CurPosX, CurPosY);
					(*tempIter)->checkPressed(CurPosX, CurPosY, m_zkCursor.ButtonPressedLeft());
					if (isQuit)break;
				}
				if (isQuit)break;
			}
			if (isQuit)break;
		}
	}
}

NAMESPACE_VIEW_E
