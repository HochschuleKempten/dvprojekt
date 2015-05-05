#include "VScreenLobby.h"
#include "VUI.h"

NAMESPACE_VIEW_B

VScreenLobby::VScreenLobby(VUI* vUi): IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);


	m_background = new CBackground();

	m_background->InitFull("textures\\MainMenueBackground.png");

	m_bigDialog = new COverlay();
	m_bigDialog->Init("textures\\LobbyBigDialog.png", CFloatRect(0.01F, 0.05F, 0.6F, 0.76F), false);
	m_bigDialog->SetLayer(0.9F);
	m_viewport->AddBackground(m_background);
	m_viewport->AddOverlay(m_bigDialog);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE,"buttonBackToPlaymode");
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.05F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME,"buttonStartGame");
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.19F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING,"iwas");
	getContainer("Menue")->addTextfield(CFloatRect(0.02F, 0.06F, 0.30F, 0.08F), &VMaterialLoader::materialIngameBorder, &VMaterialLoader::materialRed, &VMaterialLoader::materialGreen,30,"Suche IP-Adresse...","textfieldIP");
	
}

VScreenLobby::~VScreenLobby()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;
	delete m_background;
	delete m_bigDialog;

	}
void VScreenLobby::onNotify(Event events)
{
	switch (events)
	{

	default:
		notify(events);
		break;
	}
}
void VScreenLobby::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(SWITCH_TO_SPIELMODUS);
	}
	if (keyboard->KeyPressed(DIK_K))
	{
		
	}

}

	void VScreenLobby::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}

	void VScreenLobby::tick()
	{
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

	void VScreenLobby::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
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

	void VScreenLobby::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
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

	void VScreenLobby::startAnimation()
	{
	}

	void VScreenLobby::StartEvent()
	{
	}

	void VScreenLobby::EndEvent()
	{
	}

	void VScreenLobby::resize(int width, int height)
	{
	}

	NAMESPACE_VIEW_E