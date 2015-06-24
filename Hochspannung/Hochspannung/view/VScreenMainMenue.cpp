#include "VScreenMainMenue.h"
#include <thread>
#include "VUI.h"
#include <future>
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B

VScreenMainMenue::VScreenMainMenue(VUI* vUi) : IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);


	m_flash = new COverlay();
	m_flash->InitFull(&VMaterialLoader::materialMainMenueBackground);
	m_flash->SetLayer(0.999F);

	m_background = new CBackground();
	m_headline = new COverlay();

	//scene = new CScene();
	//vUi->m_zr.AddScene(scene);
	//m_flash->Init(&VMaterialLoader::materialAnimLoadingCircle, CFloatRect(0.2F, 0.2, 0.2F, 0.2 * 1.77F));

	m_background->InitFull(&VMaterialLoader::materialMainMenueBackground);


	//m_viewport->AddBackground(m_background);
	
	m_viewport->AddOverlay(m_flash);
	
	
	

	addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue", 0.5F);

	getContainer("Menue")->addButton(CFloatRect(0.33F, 0.27F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, SWITCH_TO_LOBBY, "buttonSwitchToPlayMode", 0.3F);
	getContainer("Menue")->addButton(CFloatRect(0.33F, 0.42F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueHowTo, &VMaterialLoader::materialButtonMainMenueHowToHover, SWITCH_TO_OPTIONS, "buttonSwitchToOptions", 0.3F);
	getContainer("Menue")->addButton(CFloatRect(0.33F, 0.57F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, SWITCH_TO_CREDITS, "buttonSwitchToCredits", 0.3F);
	getContainer("Menue")->addButton(CFloatRect(0.33F, 0.72F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "buttonQuitGame", 0.3F);

	//VSoundLoader::initMainMenueSound(scene);
	
}


VScreenMainMenue::~VScreenMainMenue()
{
	delete m_background;
}

void VScreenMainMenue::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}

void VScreenMainMenue::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_F))
	{
		/*dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"))->getNormalOverlay()->SetTransparency(0.9);
			dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"))->getHoverOverlay()->SetTransparency(0.9);*/
		/*auto handle = std::launch (std::launch::async,&VScreenMainMenue::fadeOut, this);
			handle.get();*/
		/*auto thread=std::thread(&VScreenMainMenue::slideIn, this);
		thread.detach();*/
	}
}

void VScreenMainMenue::checkSpecialEvent()
{
}


void VScreenMainMenue::resize(const int width, const int height)
{
}

void VScreenMainMenue::tick(const float fTimeDelta)
{
	if (!vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = false;
	}

	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainer;


	checkShortcut(&vUi->m_zkKeyboard);
	checkSpecialEvent();
	tempGuiContainer = getGuiContainerMap();

	//For all containers in the screen
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainer)
	{
		checkGUIContainer(ContainerPair.second);
	}

	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = true;
	}
}

void VScreenMainMenue::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

	for (const std::pair<std::string, IViewGUIObject*>& ObjectPair : tempGUIObjects)
	{
		if (ObjectPair.second->isOn())
		{
			if (!vUi->m_BlockCursorLeftPressed)
			{
				//check for events
				ObjectPair.second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
			}
			//if screen was changed
			if (vUi->m_screenChanged)
			{
				vUi->m_screenChanged = false;

				vUi->m_BlockCursorLeftPressed = true;
				return;
			}
		}
	}
}


void VScreenMainMenue::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainerMap;

	tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();

	checkGUIObjects(tempGuicontainer);
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainerMap)
	{
		if (tempGuicontainer->getGuiContainerMap().size() > 0)
		{
			checkGUIContainer(ContainerPair.second);
		}
	}
}

void VScreenMainMenue::startAnimation()
{
	auto thread = std::thread(&VScreenMainMenue::slideIn, this);
	thread.detach();
}


void VScreenMainMenue::slideIn()
{
	if (startUp)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		startUp = false;
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	static bool is_running = false;
	if (!is_running)
	{
		is_running = true;
		VButton* button = CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"));
		CFloatRect rect = button->getRectangle();
		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			button->updateRectangle(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setRectangle(rect);

		button = CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToOptions"));
		rect = button->getRectangle();
		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			button->updateRectangle(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setRectangle(rect);

		button = CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"));
		rect = button->getRectangle();
		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			button->updateRectangle(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setRectangle(rect);

		button = CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonQuitGame"));
		rect = button->getRectangle();
		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			button->updateRectangle(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		getContainer("Menue")->getGuiObject("buttonQuitGame")->setRectangle(rect);
		is_running = false;
		return;
	}
}

void VScreenMainMenue::switchOn()
{
	if (isOn())
		return;
	m_viewport->SwitchOn();
	//scene->SwitchOn();
	//VSoundLoader::playMainMenueSound(scene);
	m_isOn = true;
}

void VScreenMainMenue::switchOff()
{
	if (!isOn()) return;
	m_viewport->SwitchOff();
	//VSoundLoader::stopMainMenueSound(scene);
	//scene->SwitchOff();
	m_isOn = false;
}

void VScreenMainMenue::StartEvent()
{
	//startAnimation();
}

void VScreenMainMenue::EndEvent()
{
	//CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"))->updateRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
	//CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToOptions"))->updateRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
	//CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->updateRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
	//CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonQuitGame"))->updateRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));

	//getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
	//getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
	//getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
	//getContainer("Menue")->getGuiObject("buttonQuitGame")->setRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));
}

NAMESPACE_VIEW_E
