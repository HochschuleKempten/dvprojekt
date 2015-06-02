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


	m_background = new CBackground();

	m_background->InitFull(&VMaterialLoader::materialDefaultBackground);


	m_bigDialog = new COverlay();

	m_viewport->AddBackground(m_background);


	CWriting* iwas = new CWriting();
	iwas->Init(CFloatRect(0.1F, 0.8f, 0.2F, 0.1F), 10, &VMaterialLoader::standardFont);
	m_viewport->AddWriting(iwas);

	iwas->PrintF("Hallo");
	iwas->SetLayer(0.1F);

	iwas->SwitchOff();

	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.01F, 0.05F, 0.6F, 0.76F), &VMaterialLoader::materialLobbyRunningGamesBackground, "LobbyRunningGames", 0.5F);
	getContainer("LobbyRunningGames")->addTextfield(CFloatRect(0.1F, 0.10F, 0.80F, 0.1F), &VMaterialLoader::materialTextfieldBackground, &VMaterialLoader::materialTextfieldHoverBackground, &VMaterialLoader::materialTextfieldHoverBackground, 19, "Suche IP-Adresse...", "textfieldIP", 0.4F);


	//ListView
	getContainer("LobbyRunningGames")->addContainer(IViewGUIContainer::ContainerType::ListView, CFloatRect(0.1, 0.3, 0.8, 0.6), &VMaterialLoader::materialLobbyGamelistBackground, "HostList", 0.4F);
	getContainer("LobbyRunningGames")->getContainer("HostList")->addButton(CFloatRect(0.85F, 0.05F, 0.1F, 0.1F), &VMaterialLoader::materialButtonRefresh, &VMaterialLoader::materialButtonRefreshHover, REFRESH_GAME_LIST, "buttonRefresh", 0.3F);

	addContainer(m_viewport, IViewGUIContainer::ContainerType::Group, CFloatRect(0.0F, 0.7F, 1.0F, 0.3F), "Menue", 0.6F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.83F, 0.30F, 0.12F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "buttonBackToPlaymode", 0.2F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.05F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyHostGame, &VMaterialLoader::materialButtonLobbyHostGameHover, LOBBY_HOST_GAME, "buttonHostGame", 0.2F);
	getContainer("Menue")->addButton(CFloatRect(0.65F, 0.19F, 0.30F, 0.12F), &VMaterialLoader::materialButtonLobbyJoinGame, &VMaterialLoader::materialButtonLobbyJoinGameHover, LOBBY_JOIN_GAME, "buttonJoinGame", 0.2F);
	DEBUG_EXPRESSION(getContainer("Menue")->addButton(CFloatRect(0.65F, 0.33F, 0.30F, 0.12F), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME, "buttonStartGame", 0.2F));


	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.3F, 0.45F, 0.3F, 0.2F), &VMaterialLoader::materialGreen, "WaitingDialog", 0.19F);
	getContainer("WaitingDialog")->addText(CFloatRect(0.1F, 0.1F, 0.8F, 0.2F), &VMaterialLoader::standardFont, "Warte auf Mitspieler", "TextWaitingDialog", 0.15F);
	getContainer("WaitingDialog")->addButton(CFloatRect(0.2F, 0.65F, 0.6F, 0.2F), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover, NOTHING, "HostCancel", 0.14F);

	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.05F, 0.27F, 0.5F, 0.47F), &VMaterialLoader::materialGreen, "HostDialog", 0.1F);
	getContainer("HostDialog")->addTextfield(CFloatRect(0.1F, 0.1F, 0.8F, 0.2F), &VMaterialLoader::materialTextfieldBackground, &VMaterialLoader::materialTextfieldHoverBackground, &VMaterialLoader::materialTextfieldHoverBackground, 19, "Name des Spiels...", "textfieldGameName", 0.09F);
	getContainer("HostDialog")->addButton(CFloatRect(0.1, 0.5F, 0.3F, 0.2F), &VMaterialLoader::materialButtonLobbyHostGame, &VMaterialLoader::materialButtonLobbyHostGameHover, NOTHING, "buttonHostGame", 0.09F);
	getContainer("HostDialog")->addButton(CFloatRect(0.6, 0.5F, 0.3F, 0.2F), &VMaterialLoader::materialButtonLobbyJoinGame, &VMaterialLoader::materialButtonLobbyJoinGameHover, NOTHING, "buttonJoinGame", 0.09F);


	getContainer("HostDialog")->switchOff();
	getContainer("WaitingDialog")->switchOff();
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

		getContainer("LobbyRunningGames")->getGuiObject("textfieldIP")->disable();
		getContainer("Menue")->getGuiObject("buttonBackToPlaymode")->disable();
		getContainer("Menue")->getGuiObject("buttonHostGame")->disable();
		getContainer("Menue")->getGuiObject("buttonJoinGame")->disable();
		getContainer("Menue")->getGuiObject("buttonStartGame")->disable();
		//std::thread([this] { this->getContainer("WaitingDialog")->switchOn(); }).join();
		getContainer("HostDialog")->switchOn();
		getContainer("LobbyRunningGames")->getContainer("HostList")->switchOff();

		//std::thread([this] { this->vUi->vMaster->hostGame(); this->vUi->switchScreen("Ingame"); }).detach();

		//this->vUi->vMaster->hostGame(); this->vUi->switchScreen("Ingame");

		//notify(LOBBY_HOST_GAME);
		break;
	case LOBBY_JOIN_GAME:

		if (CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem() == nullptr)
		{
			vUi->vMaster->joinGame(CASTD<VTextfield*>(getContainer("LobbyRunningGames")->getGuiObject("textfieldIP"))->getValue());
		}
		else
		{
			vUi->vMaster->joinGame(CASTD<VListView*>(getContainer("LobbyRunningGames")->getContainer("HostList"))->getSelectedItem()->getName());
		}
		vUi->switchScreen("Ingame");
		break;
	case REFRESH_GAME_LIST:
		vUi->vMaster->getLMaster()->searchGames();
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
