#include "VScreenCredits.h"
#include "VUI.h"
#include <thread>

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


	m_background = new CBackground();

	m_background->InitFull(&VMaterialLoader::materialDefaultBackground);

	overlay = new COverlay();
	overlay->Init(&VMaterialLoader::materialButtonGameContinue, CFloatRect(0.3F, 0.7F, 0.3F, 0.2F));

	topBorder = new COverlay();
	topBorder->Init(&VMaterialLoader::materialErrorBackground, CFloatRect(0.0F, 0.0F, 1.0F, 0.05F));

	/*overlay = new CWriting();
	overlay->Init(CFloatRect(0.3F, 0.7F, 0.3F, 0.2F), 19, &VMaterialLoader::standardFont);
	overlay->PrintF("Patrick Benkowitsch");
*/
	overlay->SetLayer(0.1F);
	m_viewport->AddOverlay(overlay);
	m_viewport->AddOverlay(topBorder);

	m_viewport->AddBackground(m_background);

	/*addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue", 0.5F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "BackMainMenue", 0.1F);
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.33F, 0.0F, 0.33F, 1.0F), "Text", 0.4F);
	
	getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "1", 0.1F);
	getContainer("Text")->getContainer("1")->addText(CFloatRect(0.0F, 1.0F, 1.0F, 0.15F), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI", 0.1F);
	getContainer("Text")->getContainer("1")->addText(CFloatRect(0.0F, 1.15F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch", 0.1F);
	getContainer("Text")->getContainer("1")->addText(CFloatRect(0.0F, 1.25F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel", 0.1F);

	getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "2", 0.1F);
	getContainer("Text")->getContainer("2")->addText(CFloatRect(0.0F, 1.0F, 1.0F, 0.15F), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI", 0.1F);
	getContainer("Text")->getContainer("2")->addText(CFloatRect(0.0F, 1.15F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch", 0.1F);
	getContainer("Text")->getContainer("2")->addText(CFloatRect(0.0F, 1.25F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel", 0.1F);

	getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "3", 0.1F);
	getContainer("Text")->getContainer("3")->addText(CFloatRect(0.0F, 1.0F, 1.0F, 0.15F), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI", 0.1F);
	getContainer("Text")->getContainer("3")->addText(CFloatRect(0.0F, 1.15F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch", 0.1F);
	getContainer("Text")->getContainer("3")->addText(CFloatRect(0.0F, 1.25F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel", 0.1F);

	getContainer("Text")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 1.0F, 1.0F, 0.35F), "4", 0.1F);
	getContainer("Text")->getContainer("4")->addText(CFloatRect(0.0F, 1.0F, 1.0F, 0.15F), &VMaterialLoader::GoldFont, "2D-GUI und Interaktion", "GUI", 0.1F);
	getContainer("Text")->getContainer("4")->addText(CFloatRect(0.0F, 1.15F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Patrick Benkowitsch", "Benkowitsch", 0.1F);
	getContainer("Text")->getContainer("4")->addText(CFloatRect(0.0F, 1.25F, 1.0F, 0.1F), &VMaterialLoader::standardFont, "Manfred Wippel", "Wippel", 0.1F);*/
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
	static bool running = false;

	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(SWITCH_TO_MAINMENUE);
	}
	if (keyboard->KeyPressed(DIK_M)&&!running)
	{
		running = true;
		MoveText();
	}
}

void VScreenCredits::checkSpecialEvent(CDeviceCursor* cursor)
{
}

void VScreenCredits::tick(const float fTimeDelta)
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

void VScreenCredits::MoveText()
{
	//std::thread([this] {
		/*while (getContainer("Text")->getContainer("1")->getRectangle().GetYPos() > -1.25F)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			getContainer("Text")->getContainer("1")->slideUp(0.05F);
		}*/
	//}).detach();

	

	std::thread([this] {
		for (float i = overlay->GetRect().GetYPos(); i > -0.2F; i = i - 0.001F)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			CFloatRect tempRect = overlay->GetRect();
			tempRect.SetYPos(i);
			overlay->SetRect(tempRect);

		}
	}).detach();
	/*CFloatRect tempRect;
	while (getContainer("Text")->getContainer("1")->getRectangle().GetYPos() > -1.25F)
	{
		tempRect = getContainer("Text")->getContainer("1")->getRectangle();
		tempRect.SetYPos(tempRect.GetYPos() - 0.03F);
		CASTD<VText*>(getContainer("Text")->getContainer("1")->getGuiObject("GUI"))->updateRectangle(tempRect);
		
	}*/
	
}

NAMESPACE_VIEW_E
