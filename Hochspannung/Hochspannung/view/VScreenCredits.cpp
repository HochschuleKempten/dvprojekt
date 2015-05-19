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

		m_background->InitFull(&VMaterialLoader::materialDefaultBackground);

		m_viewport->AddBackground(m_background);

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "BackMainMenue");
		addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.33F, 0.0F, 0.33F, 1.0F), "Text");
		getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "GUIField");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.35F, 1.0F, 0.15F), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.5F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch");
		getContainer("Text")->addText(CFloatRect(0.0F, 0.6F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel");

		getContainer("Menue")->getGuiObject("BackMainMenue")->setLayer(0.1F);
	}

	VScreenCredits::~VScreenCredits()
	{
	}

	void VScreenCredits::onNotify(const Event& events)
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

	void VScreenCredits::tick(const float fTimeDelta)
	{
		updateCursorImagePos(&vUi->m_zkCursor);

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
	void VScreenCredits::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
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


	void VScreenCredits::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
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

	void VScreenCredits::resize(const int width, const int height)
	{
	}

	NAMESPACE_VIEW_E
