#include "VScreenGameOver.h"


NAMESPACE_VIEW_B


VScreenGameOver::VScreenGameOver(VUI* vUi) : IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);

	//Cursor


	m_background = new CBackground();

	m_background->InitFull(&VMaterialLoader::materialDefaultBackground);

	m_viewport->AddBackground(m_background);

	
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.2F, 0.2F, 0.6F, 0.3F), "MainContainer", 0.5F);
	getContainer("MainContainer")->addText(CFloatRect(0.0F, 0.0F, 1.0F, 1.0F), &VMaterialLoader::standardFont, "Sie haben gewonnen", "Header", 0.2F, VText::TextMode::CENTERED);
	
	
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.2F, 0.6F, 0.6F, 0.3F), "MainContent", 0.5F);
	getContainer("MainContent")->addButton(CFloatRect(0.2F, 0.2F, 0.6F, 0.2F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "QuitGame", 0.3F);


}


void VScreenGameOver::onNotify(const Event& events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}

void VScreenGameOver::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		//notify(SWITCH_TO_MAINMENUE);
	}
}

void VScreenGameOver::checkSpecialEvent()
{
}

void VScreenGameOver::tick(const float fTimeDelta)
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

void VScreenGameOver::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
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

void VScreenGameOver::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
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

void VScreenGameOver::resize(const int width, const int height)
{
}

void VScreenGameOver::startAnimation()
{
}

void VScreenGameOver::StartEvent()
{
}

void VScreenGameOver::EndEvent()
{
}

VScreenGameOver::~VScreenGameOver()
{
}

NAMESPACE_VIEW_E