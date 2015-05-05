#include "VScreenMainMenue.h"
#include <thread>
#include "VUI.h"
#include <future>

NAMESPACE_VIEW_B

	VScreenMainMenue::VScreenMainMenue(VUI* vUi) : IViewScreen(vUi)
	{
		m_viewport = new CViewport();
		m_camera.Init();
		m_viewport->InitFull(&m_camera);
		vUi->m_zf.AddViewport(m_viewport);

		m_flash = new COverlay();
		m_background = new CBackground();
		m_headline = new COverlay();

		m_background->InitFull("textures\\MainMenueBackground.png");
		m_flash->Init("textures\\Blitz.png", CFloatRect(0.75F, 0.2F, 0.20F, 0.7F));
		m_headline->Init("textures\\Hochvolt.png", CFloatRect(0.20F, 0.05F, 0.6F, 0.15F));

		m_viewport->AddBackground(m_background);
		m_viewport->AddOverlay(m_flash);
		m_viewport->AddOverlay(m_headline);

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
		/*getContainer("Menue")->addButton(CFloatRect(0.33F, 0.27F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, SWITCH_TO_LOBBY, "buttonSwitchToPlayMode");
		getContainer("Menue")->addButton(CFloatRect(0.33F, 0.42F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, SWITCH_TO_OPTIONS, "buttonSwitchToOptions");
		getContainer("Menue")->addButton(CFloatRect(0.33F, 0.57F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, SWITCH_TO_CREDITS, "buttonSwitchToCredits");
		getContainer("Menue")->addButton(CFloatRect(0.33F, 0.72F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "buttonQuitGame");
	*/
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, SWITCH_TO_LOBBY, "buttonSwitchToPlayMode");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, SWITCH_TO_OPTIONS, "buttonSwitchToOptions");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, SWITCH_TO_CREDITS, "buttonSwitchToCredits");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "buttonQuitGame");

		
}


	VScreenMainMenue::~VScreenMainMenue()
	{
		for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
		{
			delete m_IterGuicontainer->second;
		}
		m_Guicontainer.clear();

		delete m_flash;
		delete m_background;
		delete m_headline;
		delete m_viewport;
	}

	void VScreenMainMenue::onNotify(Event events)
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

	void VScreenMainMenue::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}


	void VScreenMainMenue::resize(int width, int height)
	{
	}

	void VScreenMainMenue::tick()
	{

		if (!vUi->m_zkCursor.ButtonPressedLeft())
		{
			vUi->m_BlockCursorLeftPressed = false;
		}

		map<string, IViewGUIContainer*> tempGuicontainer;
		map<string, IViewGUIContainer*>::iterator tempIterGuicontainer;
		
		checkShortcut(&vUi->m_zkKeyboard);
		checkSpecialEvent(&vUi->m_zkCursor);
		tempGuicontainer = getGuiContainerMap();

			//For all containers in the screen
		for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
		{
			checkGUIContainer(tempIterGuicontainer->second);
		}
	}

	void VScreenMainMenue::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
	{
		map<string, IViewGUIObject*>::iterator tempIterGUIObjects;
		map<string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

		for (tempIterGUIObjects = tempGUIObjects.begin(); tempIterGUIObjects != tempGUIObjects.end(); tempIterGUIObjects++)
		{
			if (tempIterGUIObjects->second->isOn())
			{
				if (!vUi->m_BlockCursorLeftPressed)
				{
					//check for events
					tempIterGUIObjects->second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
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
			VButton* button = static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"));
			CFloatRect rect = button->getRectangle();
			for (float i = 0; i < 0.33F; i = i + 0.001F)
			{

				rect.SetXPos(i);
				button->updateRectangle(rect);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setRectangle(rect);
			
			button = static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToOptions"));
			 rect = button->getRectangle();
			for (float i = 0; i < 0.33F; i = i + 0.001F)
			{

				rect.SetXPos(i);
				button->updateRectangle(rect);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setRectangle(rect);
			
			button = static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"));
			 rect = button->getRectangle();
			for (float i = 0; i < 0.33F; i = i + 0.001F)
			{

				rect.SetXPos(i);
				button->updateRectangle(rect);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setRectangle(rect);
			
			button = static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonQuitGame"));
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
		/*
		rect = dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->getNormalOverlay()->GetRect();

		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->getNormalOverlay()->SetRect(rect);
			dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->getHoverOverlay()->SetRect(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		rect = dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToQuitGame"))->getNormalOverlay()->GetRect();

		for (float i = 0; i < 0.33F; i = i + 0.001F)
		{
			rect.SetXPos(i);
			dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToQuitGame"))->getNormalOverlay()->SetRect(rect);
			dynamic_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToQuitGame"))->getHoverOverlay()->SetRect(rect);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}*/
	}

	void VScreenMainMenue::StartEvent()
	{
		startAnimation();
	}

	void VScreenMainMenue::EndEvent()
	{
		static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"))->updateRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
		static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToOptions"))->updateRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
		static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->updateRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
		static_cast<VButton*>(getContainer("Menue")->getGuiObject("buttonQuitGame"))->updateRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));

		getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonQuitGame")->setRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));
	}

	void VScreenMainMenue::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
	{
		map<string, IViewGUIContainer*> tempGuiContainerMap;
		map<string, IViewGUIContainer*>::iterator ItertempGuiContainerMap;
		
		tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();
		
		checkGUIObjects(tempGuicontainer);

		for (ItertempGuiContainerMap = tempGuiContainerMap.begin(); ItertempGuiContainerMap != tempGuiContainerMap.end(); ItertempGuiContainerMap++)
		{
			checkGUIObjects(ItertempGuiContainerMap->second);

			if (tempGuicontainer->getGuiContainerMap().size() > 0)
			{
				checkGUIContainer(ItertempGuiContainerMap->second);
			}
		}
	}

	NAMESPACE_VIEW_E
