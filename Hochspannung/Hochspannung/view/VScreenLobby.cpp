#include "VScreenLobby.h"
#include "VUI.h"
#include "VMaster.h"

NAMESPACE_VIEW_B

	VScreenLobby::VScreenLobby(VUI* vUi): IViewScreen(vUi)
	{
		m_viewport = new CViewport();
		m_camera.Init();
		m_viewport->InitFull(&m_camera);
		vUi->m_zf.AddViewport(m_viewport);

		//Cursor
		switchCursor("textures/gui/default_zeiger.png", true);

		m_background = new CBackground();
		
		m_background->InitFull(&VMaterialLoader::materialDefaultBackground);
		

		m_bigDialog = new COverlay();
		m_bigDialog->Init(&VMaterialLoader::materialWhiteGreyBackground, CFloatRect(0.01F, 0.05F, 0.6F, 0.76F));
		m_bigDialog->SetLayer(0.9F);
		m_viewport->AddBackground(m_background);
		m_viewport->AddOverlay(m_bigDialog);

		CWriting* iwas=new CWriting();
		iwas->Init(CFloatRect(0.1F, 0.8f, 0.2F, 0.1F), 10, &VMaterialLoader::standardFont);
		m_viewport->AddWriting(iwas);

		iwas->PrintF("Hallo");
		iwas->SetLayer(0.1F);
		//VMaterialLoader::standardFont.SwitchOff();
		iwas->SwitchOff();

		addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.01F, 0.05F, 0.6F, 0.76F), "LobbyRunningGames");
		getContainer("LobbyRunningGames")->addTextfield(CFloatRect(0.1F, 0.10F, 0.80F, 0.1F), &VMaterialLoader::materialIngameBorder, &VMaterialLoader::materialRed, &VMaterialLoader::materialGreen, 30, "Suche IP-Adresse...", "textfieldIP");
		
		
		//ListView
		getContainer("LobbyRunningGames")->addContainer(IViewGUIContainer::ContainerType::ListView, CFloatRect(0.1, 0.3, 0.8, 0.6), "HostList");
		
		

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "buttonBackToPlaymode");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.05F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyHostGame, &VMaterialLoader::materialButtonLobbyHostGameHover, LOBBY_HOST_GAME, "buttonHostGame");
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.19F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyJoinGame, &VMaterialLoader::materialButtonLobbyJoinGameHover, LOBBY_JOIN_GAME, "buttonJoinGame");
		DEBUG_EXPRESSION(getContainer("Menue")->addButton(CFloatRect(0.65F, 0.33F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME, "buttonStartGame"));
		getContainer("Menue")->addButton(CFloatRect(0.65F, 0.33F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME, "buttonStartGame");

		addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.3F, 0.45F, 0.3F, 0.2F), &VMaterialLoader::materialGreen, "WaitingDialog");
		getContainer("WaitingDialog")->addText(CFloatRect(0.1F, 0.1F, 0.8F, 0.2F), &VMaterialLoader::standardFont, "Warte auf Mitspieler", "TextWaitingDialog");
		getContainer("WaitingDialog")->addButton(CFloatRect(0.2F, 0.35F, 0.6F, 0.2), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover,NOTHING,"HostCancel");


		getContainer("WaitingDialog")->setLayer(0.5);
		getContainer("WaitingDialog")->switchOff();
	
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->setLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonHostGame")->setLayer(0.3F);
		getContainer("Menue")->getGuiObject("buttonJoinGame")->setLayer(0.3F);
		DEBUG_EXPRESSION(getContainer("Menue")->getGuiObject("buttonStartGame")->setLayer(0.3F));
	}

	VScreenLobby::~VScreenLobby()
	{
		delete m_background;
		delete m_bigDialog;
	}

	void VScreenLobby::onNotify(const Event& events)
	{
		switch (events)
		{
			case START_GAME:
				vUi->vMaster->startSinglePlayerGame();
				vUi->switchScreen("Ingame");
				break;
			case LOBBY_HOST_GAME:
				getContainer("WaitingDialog")->switchOn();
				//vUi->vMaster->hostGame();
				//vUi->switchScreen("Ingame");
				//notify(LOBBY_HOST_GAME);
				break;
			case LOBBY_JOIN_GAME:
				
				if (CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem()->getName().empty())
				{
					vUi->vMaster->joinGame(CASTD<VTextfield*>(getContainer("LobbyRunningGames")->getGuiObject("textfieldIP"))->getValue());
				}
				else
				{
					vUi->vMaster->joinGame(CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem()->getName());
				}
				vUi->switchScreen("Ingame");
				//notify(LOBBY_JOIN_GAME);
				break;
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

	void VScreenLobby::tick(const float fTimeDelta)
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

	void VScreenLobby::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
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


	void VScreenLobby::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
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

	void VScreenLobby::startAnimation()
	{
	}

	void VScreenLobby::StartEvent()
	{
	}

	void VScreenLobby::EndEvent()
	{
	}

	void VScreenLobby::updateHostList(const std::vector<Network::CGameObject>& hostList)
	{
		CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->updateList(hostList);
	}

	void VScreenLobby::resize(const int width, const int height)
	{
	}

	NAMESPACE_VIEW_E
