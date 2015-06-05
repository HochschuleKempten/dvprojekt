#include "VScreenLobby.h"
#include "VUI.h"
#include "VMaster.h"
#include <thread>
#include "../logic/LMaster.h"

NAMESPACE_VIEW_B

VScreenLobby::VScreenLobby(VUI* vUi): IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);

	//Cursor




	m_bigDialog = new COverlay();
	m_bigDialog->InitFull("textures/background.jpg");
	//m_viewport->AddBackground(&VMaterialLoader::materialIngameBackground);
	m_bigDialog->SetLayer(0.999F);
	m_viewport->AddOverlay(m_bigDialog);
	CWriting* iwas = new CWriting();
	iwas->Init(CFloatRect(0.1F, 0.8f, 0.2F, 0.1F), 10, &VMaterialLoader::standardFont);
	m_viewport->AddWriting(iwas);

	iwas->PrintF("Hallo");
	iwas->SetLayer(0.1F);

	iwas->SwitchOff();

	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.01F, 0.05F, 0.6F, 0.76F), &VMaterialLoader::materialLobbyRunningGamesBackground, "LobbyRunningGames", 0.5F);
	getContainer("LobbyRunningGames")->addTextfield(CFloatRect(0.1F, 0.10F, 0.80F, 0.1F), &VMaterialLoader::materialTextfieldBackground, &VMaterialLoader::materialTextfieldHoverBackground, &VMaterialLoader::materialTextfieldHoverBackground, 20, "IP-Adresse...", "textfieldIP", 0.4F);


	//ListView
	getContainer("LobbyRunningGames")->addContainer(IViewGUIContainer::ContainerType::ListView, CFloatRect(0.1, 0.3, 0.8, 0.6), &VMaterialLoader::materialLobbyGamelistBackground, "HostList", 0.4F);
	getContainer("LobbyRunningGames")->getContainer("HostList")->addButton(CFloatRect(0.85F, 0.05F, 0.1F, 0.1F), &VMaterialLoader::materialButtonRefresh, &VMaterialLoader::materialButtonRefreshHover, REFRESH_GAME_LIST, "buttonRefresh", 0.3F);

	addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue", 0.6F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "buttonBackToPlaymode", 0.2F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.05F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyHostGame, &VMaterialLoader::materialButtonLobbyHostGameHover, OPEN_HOST_DIALOG, "buttonCreateGame", 0.2F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.19F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyJoinGame, &VMaterialLoader::materialButtonLobbyJoinGameHover, LOBBY_JOIN_GAME, "buttonJoinGame", 0.2F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.33F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME, "buttonStartGame", 0.2F);

	
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.3F, 0.45F, 0.3F, 0.2F), &VMaterialLoader::materialLobbyRunningGamesBackground, "WaitingDialog", 0.19F);
	getContainer("WaitingDialog")->addText(CFloatRect(0.1F, 0.1F, 0.8F, 0.2F), &VMaterialLoader::standardFont, "Warte auf Mitspieler", "TextWaitingDialog", 0.15F);
	getContainer("WaitingDialog")->addOverlay(CFloatRect(0.4F, 0.35, 0.2F, 0.354F), &VMaterialLoader::materialAnimLoadingCircle, "LoadingCircle", 0.07F);
	getContainer("WaitingDialog")->addButton(CFloatRect(0.2F, 0.71F, 0.6F, 0.2F), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover, ABORT_WAITING_DIALOG, "HostCancel", 0.14F);
	
	
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.05F, 0.27F, 0.5F, 0.47F), &VMaterialLoader::materialLobbyRunningGamesBackground, "HostDialog", 0.1F);
	getContainer("HostDialog")->addTextfield(CFloatRect(0.1F, 0.1F, 0.8F, 0.2F), &VMaterialLoader::materialTextfieldBackground, &VMaterialLoader::materialTextfieldHoverBackground, &VMaterialLoader::materialTextfieldHoverBackground, 19, "Name des Spiels...", "textfieldGameName", 0.09F);
	getContainer("HostDialog")->addButton(CFloatRect(0.1, 0.5F, 0.3F, 0.2F), &VMaterialLoader::materialButtonLobbyHostGame, &VMaterialLoader::materialButtonLobbyHostGameHover, LOBBY_HOST_GAME, "buttonHostGame", 0.09F);
	getContainer("HostDialog")->addButton(CFloatRect(0.6, 0.5F, 0.3F, 0.2F), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover, ABORT_HOST_DIALOG, "HostDialogAbort", 0.09F);


	getContainer("HostDialog")->switchOff();
	getContainer("WaitingDialog")->switchOff();
}

VScreenLobby::~VScreenLobby()
{
	//delete m_background;
	delete m_bigDialog;
}

void VScreenLobby::onNotify(const Event& events)
{
	

	switch (events)
	{
	case START_GAME:
		
		///*std::thread([this]{
		//	while (!m_startReady)
		//	{*/
		//		vUi->tick(0.01F);
		//		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		//	}
		//	m_startReady = false;
		//}).detach();

			vUi->vMaster->startSinglePlayerGame();
			
			vUi->switchScreen("Ingame");
			m_startReady = true;
		
		break;
	case LOBBY_HOST_GAME:

		//getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->disable();
		//getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->disable();
		//getContainer("Menue")->getGuiObject("buttonCreateGame")->disable();
		//getContainer("Menue")->getGuiObject("buttonJoinGame")->disable();
		//getContainer("Menue")->getGuiObject("buttonStartGame")->disable();

		//getContainer("HostDialog")->switchOff();
		//getContainer("WaitingDialog")->switchOn();
		//getContainer("LobbyRunningGames")->getContainer("HostList")->switchOn();

		//std::thread([this] { this->getContainer("WaitingDialog")->switchOn(); }).join();
		

		//std::thread([this] { this->vUi->vMaster->hostGame(); this->vUi->switchScreen("Ingame"); }).detach();

		this->vUi->vMaster->hostGame(); this->vUi->switchScreen("Ingame");

		//notify(LOBBY_HOST_GAME);
		break;
	case LOBBY_JOIN_GAME:
		
		getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->disable();
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->disable();
		getContainer("Menue")->getGuiObject("buttonCreateGame")->disable();
		getContainer("Menue")->getGuiObject("buttonJoinGame")->disable();
		getContainer("Menue")->getGuiObject("buttonStartGame")->disable();
		
			CASTD<VText*>(getContainer("WaitingDialog")->getGuiObject("TextWaitingDialog"))->updateText("Trete Spiel bei...");
			getContainer("WaitingDialog")->switchOn();
			
			std::thread([this]{
				while (!m_JoinReady)
				{
					vUi->tick(0.01F);
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
				m_JoinReady = false;
			}).detach();
			
		


		if (CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem() == nullptr)
		{
			vUi->vMaster->joinGame(CASTD<VTextfield*>(getContainer("LobbyRunningGames")->getGuiObject("textfieldIP"))->getValue());
			m_JoinReady = true;
		}
		else
		{
			vUi->vMaster->joinGame(CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem()->getName());
			m_JoinReady = true;
		}
		vUi->switchScreen("Ingame");
		break;
	case REFRESH_GAME_LIST:
		vUi->vMaster->getLMaster()->searchGames();
		break;

	case ABORT_HOST_DIALOG:
		getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->enable();
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->enable();
		getContainer("Menue")->getGuiObject("buttonCreateGame")->enable();
		getContainer("Menue")->getGuiObject("buttonJoinGame")->enable();
		getContainer("Menue")->getGuiObject("buttonStartGame")->enable();
		getContainer("HostDialog")->switchOff();
		getContainer("LobbyRunningGames")->getContainer("HostList")->switchOn();
		break;
	case OPEN_HOST_DIALOG:
		getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->disable();
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->disable();
		getContainer("Menue")->getGuiObject("buttonCreateGame")->disable();
		getContainer("Menue")->getGuiObject("buttonJoinGame")->disable();
		getContainer("Menue")->getGuiObject("buttonStartGame")->disable();
		getContainer("HostDialog")->switchOn();
		getContainer("LobbyRunningGames")->getContainer("HostList")->switchOff();
		break;
	
	case ABORT_WAITING_DIALOG:
		getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->enable();
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->enable();
		getContainer("Menue")->getGuiObject("buttonCreateGame")->enable();
		getContainer("Menue")->getGuiObject("buttonJoinGame")->enable();
		getContainer("Menue")->getGuiObject("buttonStartGame")->enable();
		getContainer("WaitingDialog")->switchOff();
		getContainer("LobbyRunningGames")->getContainer("HostList")->switchOn();

		if (!m_startReady)
		m_startReady = true;
		if (!m_JoinReady)
		m_JoinReady = true;

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

void VScreenLobby::foundPlayer()
{
	static bool JoinReady = false;

	CASTD<VText*>(getContainer("WaitingDialog")->getGuiObject("TextWaitingDialog"))->updateText("Erstelle Spiel...");
	
	std::thread([this]{
		while (!JoinReady)
		{
			vUi->tick(0.01F);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
		JoinReady = false;
	}).detach();

	vUi->vMaster->startSinglePlayerGame();
	vUi->switchScreen("Ingame");
	JoinReady = true;

	
}

void VScreenLobby::resize(const int width, const int height)
{
}

NAMESPACE_VIEW_E
