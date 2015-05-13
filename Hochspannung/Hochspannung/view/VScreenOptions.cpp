#include "VScreenOptions.h"
#include "VUI.h"
#include "VGraph.h"

NAMESPACE_VIEW_B


	VScreenOptions::VScreenOptions(VUI* vUi) : IViewScreen(vUi)
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
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "buttonBackMainMenue");

		VGraph* graph = new VGraph(m_viewport, CFloatRect(0.2F, 0.3f, 0.2F, 0.2F));
		graph->addBar("EngergyBar", &VMaterialLoader::materialGreen);
		graph->addBar("SollEnergy", &VMaterialLoader::materialRed);
		graph->updateBar("SollEnergy", 20);
	}

	VScreenOptions::~VScreenOptions()
	{
		for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
		{
			delete m_IterGuicontainer->second;
		}
		m_Guicontainer.clear();

		delete m_viewport;
	}

	void VScreenOptions::onNotify(Event events)
	{
		switch (events)
		{
		default:
			notify(events);
			break;
		}
	}

	void VScreenOptions::checkShortcut(CDeviceKeyboard* keyboard)
	{
		if (keyboard->KeyPressed(DIK_ESCAPE))
		{
			notify(SWITCH_TO_MAINMENUE);
		}
	}

	void VScreenOptions::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}


	void VScreenOptions::tick()
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

	void VScreenOptions::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
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

	void VScreenOptions::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
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

	void VScreenOptions::startAnimation()
	{
	}

	void VScreenOptions::StartEvent()
	{
	}

	void VScreenOptions::EndEvent()
	{
	}

	void VScreenOptions::resize(int width, int height)
	{
	}

	NAMESPACE_VIEW_E
