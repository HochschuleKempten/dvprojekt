#include "VUI.h"
#include "VMaster.h"
#include "VPlayingField.h"
#include "VPowerLine.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VMaterialLoader.h"
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

	//Camera (WASD) settings
	m_zkKeyboard.SetWASDTranslationSensitivity(20.0);
	m_zkKeyboard.SetWASDRotationSensitivity(2.0);
	m_zkKeyboard.SetWASDLevelMin(100.0);
	m_zkKeyboard.SetWASDLevelMax(200.0);

	m_zc.Init();
	m_zv.InitFull(&m_zc);
	vMaster->m_zr.AddFrameHere(&vMaster->m_zf);
	vMaster->m_zf.AddViewport(&m_zv);
	vMaster->m_zr.AddScene(&m_zs);
	m_zs.SwitchOff();
	m_zb.InitFull("textures/black_image.jpg");
	m_zv.AddBackground(&m_zb);
	
	m_zs.AddPlacement(&m_zpCamera);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.SetName("Placement Camera");

	m_zpCamera.TranslateZ(50.0);
	m_zpCamera.RotateXDelta(0.3 * PI);

	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
	CColor(1.0f, 1.0f, 1.0f));

	addScreen("MainMenue", VScreen::MainMenue);
	getScreen("MainMenue")->addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Bottom");
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33f, 0.27f, 0.33f, 0.14f), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::START_GAME);
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33f, 0.42f, 0.33f, 0.14f), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::MainOptions);
	getScreen("MainMenue")->getContainer("Bottom")->addButton(CFloatRect(0.33f, 0.57f, 0.33f, 0.14f), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::QUIT_GAME);

	addScreen("Ingame", VScreen::Ingame);
	getScreen("Ingame")->addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "craft");
	getScreen("Ingame")->getContainer("craft")->addButton(CFloatRect(0.0f, 0.75f, 0.20f, 0.25f), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenue, IViewObserver::NOTHING);
	getScreen("Ingame")->getContainer("craft")->addButton(CFloatRect(0.2f, 0.75f, 0.60f, 0.25f), &VMaterialLoader::materialIngameCraft, &VMaterialLoader::materialIngameCraft, IViewObserver::NOTHING);

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

void VUI::onNotify(IViewObserver::Event evente)
{
	DEBUG_OUTPUT("Nachricht bei GUI-Observer angekommen\n");
	switch (evente)
	{
	case IViewObserver::START_GAME:
		DEBUG_OUTPUT("STARTING GAME.........\n");
		vMaster->lMaster->startNewGame();
		switchScreen("Ingame"); //TODO Button Action erweitern um switchscreen event damit Screen nicht hardcoded Ingame sein muss
		break;
	case IViewObserver::MainOptions:
		DEBUG_OUTPUT("Open Options from MainMenue.........\n");
		//m_writing.PrintF("Change Screen to Options");
		break;
	case IViewObserver::QUIT_GAME:
		isQuit = true;
		PostQuitMessage(0);
		DEBUG_OUTPUT("Quit Game.........\n");
		break;
		// Handle other events, and update heroIsOnBridge_...
	default:
		DEBUG_OUTPUT("Keine Lösung gefunden\n");
	}

}

void VUI::addScreen(string sName, VScreen::ScreenType screenType)
{
	if (screenType==VScreen::ScreenType::Ingame)
	{
		m_screens[sName] = new VScreen(&m_zv,screenType, &vMaster->m_zf);
		m_screens[sName]->addObserver(this);
	}
	else
	{
		m_screens[sName] = new VScreen(screenType, &vMaster->m_zf);
		m_screens[sName]->addObserver(this);
	}
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

	if (getScreen(switchTo)->m_screenType == VScreen::ScreenType::Ingame)
	{
		m_zs.SwitchOn();
		m_zv.SwitchOn();

	}
	else
	{
		m_zs.SwitchOff();
		m_zv.SwitchOff();
	}

}

VScreen* VUI::getScreen(string sName)
{
	ASSERT(m_screens.find(sName) != m_screens.end(), "Screen not available");
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
