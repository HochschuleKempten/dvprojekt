#include "VScreenCredits.h"
#include "VUI.h"

NAMESPACE_VIEW_B

	void VScreenCredits::startAnimation()
	{
	}

	void VScreenCredits::StartEvent()
	{
	}

	void VScreenCredits::EndEvent()
	{
	}

	VScreenCredits::VScreenCredits(VUI* vUi) : IViewScreen(vUi)
	{
		m_viewport = new CViewport();
		m_camera.Init();
		m_viewport->InitFull(&m_camera);
		vUi->m_zf.AddViewport(m_viewport);

		//Cursor
		switchCursor("textures/gui/default_zeiger.png", true);

		m_background = new CBackground();

		m_background->InitFull("textures\\MainMenueBackground.png");

		m_viewport->AddBackground(m_background);

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "BackMainMenue");
		addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.33F, 0.0F, 0.33F, 1.0F), "Text");
		getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "GUIField");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.35F, 1.0, 0.15), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.5F, 1.0, 0.1), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.6F, 1.0, 0.1), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel");
	}

	VScreenCredits::~VScreenCredits()
	{
		for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
		{
			delete m_IterGuicontainer->second;
		}
		m_Guicontainer.clear();

		delete m_viewport;
	}

	void VScreenCredits::onNotify(Event events)
	{
		switch (events)
		{
		default:
			notify(events);
			break;
		}
	}

	void VScreenCredits::checkShortcut(CDeviceKeyboard* keyboard)
	{
		if (keyboard->KeyPressed(DIK_ESCAPE))
		{
			notify(SWITCH_TO_MAINMENUE);
		}
	}

	void VScreenCredits::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}

	void VScreenCredits::tick()
	{
		updateCursorImagePos(&vUi->m_zkCursor);

		if (!vUi->m_zkCursor.ButtonPressedLeft())
		{
			vUi->m_BlockCursorLeftPressed = false;
		}

		std::map<std::string, IViewGUIContainer*> tempGuicontainer;
		std::map<std::string, IViewGUIContainer*>::iterator tempIterGuicontainer;

		checkShortcut(&vUi->m_zkKeyboard);
		checkSpecialEvent(&vUi->m_zkCursor);
		tempGuicontainer = getGuiContainerMap();

		//For all containers in the screen
		for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
		{
			checkGUIContainer(tempIterGuicontainer->second);
		}

		if (vUi->m_zkCursor.ButtonPressedLeft())
		{
			vUi->m_BlockCursorLeftPressed = true;
		}
	}

	void VScreenCredits::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
	{
		std::map<std::string, IViewGUIObject*>::iterator tempIterGUIObjects;
		std::map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

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

	void VScreenCredits::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
	{
		std::map<std::string, IViewGUIContainer*> tempGuiContainerMap;
		std::map<std::string, IViewGUIContainer*>::iterator ItertempGuiContainerMap;

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

	void VScreenCredits::resize(int width, int height)
	{
	}

	NAMESPACE_VIEW_E
