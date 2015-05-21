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

		//Cursor
		//switchCursor(CursorType::Default);
		

		m_flash = new COverlay();
		m_background = new CBackground();
		m_headline = new COverlay();

		COverlay* testAnim=new COverlay();

		testAnim->Init(&VMaterialLoader::materialAnimationsVersuch, CFloatRect(0.1F, 0.1F, 0.1F, 0.1F));
		m_viewport->AddOverlay(testAnim);

		m_background->InitFull(&VMaterialLoader::materialMainMenueBackground);
		//m_flash->Init("textures\\Blitz.png", CFloatRect(0.75F, 0.2F, 0.20F, 0.7F));
		//m_headline->Init("textures\\Hochvolt.png", CFloatRect(0.20F, 0.05F, 0.6F, 0.15F));


		m_viewport->AddBackground(m_background);
		m_viewport->AddOverlay(m_flash);
		//m_viewport->AddOverlay(m_headline);

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");

		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, SWITCH_TO_LOBBY, "buttonSwitchToPlayMode");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, SWITCH_TO_OPTIONS, "buttonSwitchToOptions");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, SWITCH_TO_CREDITS, "buttonSwitchToCredits");
		getContainer("Menue")->addButton(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "buttonQuitGame");


		m_flash->SetLayer(0.3F);
		m_headline->SetLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonQuitGame")->setLayer(0.3F);
	}


	VScreenMainMenue::~VScreenMainMenue()
	{
		delete m_flash;
		delete m_background;
		delete m_headline;
	}

	void VScreenMainMenue::onNotify(const Event& events)
	{
		switch (events)
		{
		default:
			notify(events);//TODO (UI) endless loop?
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
		checkSpecialEvent(&vUi->m_zkCursor);
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
			checkGUIObjects(ContainerPair.second);

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
		CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode"))->updateRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
		CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToOptions"))->updateRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
		CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonSwitchToCredits"))->updateRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
		CASTD<VButton*>(getContainer("Menue")->getGuiObject("buttonQuitGame"))->updateRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));

		getContainer("Menue")->getGuiObject("buttonSwitchToPlayMode")->setRectangle(CFloatRect(-0.30F, 0.27F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonSwitchToOptions")->setRectangle(CFloatRect(-0.30F, 0.42F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonSwitchToCredits")->setRectangle(CFloatRect(-0.30F, 0.57F, 0.30F, 0.12F));
		getContainer("Menue")->getGuiObject("buttonQuitGame")->setRectangle(CFloatRect(-0.30F, 0.72F, 0.30F, 0.12F));
	}

	NAMESPACE_VIEW_E
