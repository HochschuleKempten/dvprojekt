#include "VUI.h"
#include "VMaster.h"
#include "../logic/LUtility.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VMaterialLoader.h"


NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster, LUI* lUi)
	: vMaster(vMaster), IVUI(lUi)
{
	vMaster->setVUI(this);
	vMaster->registerObserver(this);
}

void VUI::initUI()
{
	vMaster->m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	vMaster->m_zf.AddDeviceCursor(&m_zkCursor);
	vMaster->m_zf.AddDeviceMouse(&m_zkMouse);

	addScreen("MainMenue", VScreen::MainMenue);
	getScreen("MainMenue")->addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Bottom");
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33, 0.27, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::START_GAME);
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33, 0.42, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::MainOptions);
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33, 0.57, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::QUIT_GAME);

	addScreen("Ingame", VScreen::Ingame);
	getScreen("Ingame")->addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "craft");
	getScreen("Ingame")->getContainer("craft")->addButton(CFloatRect(0.0, 0.75, 0.20, 0.25), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenue, IViewObserver::NOTHING);
	getScreen("Ingame")->getContainer("craft")->addButton(CFloatRect(0.2, 0.75, 0.60, 0.25), &VMaterialLoader::materialIngameCraft, &VMaterialLoader::materialIngameCraft, IViewObserver::NOTHING);

}

void VUI::handleInput(float fTimeDelta)
{
	m_zkKeyboard.PlaceWASD(vMaster->m_zpCamera, fTimeDelta);
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


void VUI::onNotify(IViewObserver::Event evente)
{
	OutputDebugString("Nachricht bei GUI-Observer angekommen\n");
	switch (evente)
	{
	case IViewObserver::START_GAME:
		OutputDebugString("STARTING GAME.........\n");
		switchScreen("Ingame"); //TODO Button Action erweitern um switchscreen event damit Screen nicht hardcoded Ingame sein muss
		break;
	case IViewObserver::MainOptions:
		OutputDebugString("Open Options from MainMenue.........\n");
		//m_writing.PrintF("Change Screen to Options");
		break;
	case IViewObserver::QUIT_GAME:
		isQuit = true;
		PostQuitMessage(0);
		OutputDebugString("Quit Game.........\n");
		break;
		// Handle other events, and update heroIsOnBridge_...
	default:
		OutputDebugString("Keine Lösung gefunden\n");
	}

}


void VUI::addScreen(string sName, VScreen::ScreenType screenType)
{
	m_screens[sName] = new VScreen(screenType, &vMaster->m_zf);
	m_screens[sName]->addObserver(this);
}

void VUI::switchScreen(string switchTo)
{
	map<string, VScreen*>::iterator it = m_screens.find(switchTo);
	ASSERT(it != m_screens.end(),"Screen not available");

	for (it = m_screens.begin(); it != m_screens.end(); it++)
	{
		it->second->switchOff();
	}
	m_screens[switchTo]->switchOn();

}


VScreen* VUI::getScreen(string sName)
{
	ASSERT(m_screens.find(sName) != m_screens.end(), "Screen not available");
	return	m_screens[sName];
}
NAMESPACE_VIEW_E
