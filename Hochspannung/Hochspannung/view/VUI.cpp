#include "VUI.h"
#include "VMaster.h"
#include "IViewScreen.h"
#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenLobby.h"
#include "VScreenCredits.h"
#include "VScreenOptions.h"
#include "VScreenGameOver.h"
#include "VScreenHelp.h"
#include "VScreenControls.h"

NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster)
	: vMaster(vMaster), isQuit(false)
{
	vMaster->registerObserver(this);
}

VUI::~VUI()
{
	vMaster->unregisterObserver(this);
}

void VUI::initUI(HWND hwnd, CSplash* psplash)
{
	m_hwnd = hwnd;

	m_Default_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\default_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));
	m_Hammer_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\hammer_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));
	m_Sabotage_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\bomb_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));
	m_PowerOn_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\poweron_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));
	m_PowerOff_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\poweroff_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));
	m_Sell_Cursor = static_cast<HCURSOR>(LoadImage(HINSTANCE(GetWindowLong(hwnd, GWLP_HINSTANCE)), "textures\\gui\\Cursor\\sell_zeiger.cur", IMAGE_CURSOR, 0, 0, LR_LOADTRANSPARENT | LR_LOADFROMFILE));


	m_zr.Init(psplash);
#ifdef _DEBUG
	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50_Basic, eApiInput_DirectInput, eApiSound_DirectSound, eShaderCreation_ForceCompile, eShaderAutoRecompilation_Disabled);
#else
	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput, eApiSound_DirectSound, eShaderCreation_ForceCompile, eShaderAutoRecompilation_Disabled);
#endif
	m_zr.AddFrameHere(&m_zf);

	m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);

	addScreen("MainMenue", IViewScreen::MainMenue);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Help", IViewScreen::Help);
	addScreen("Controls", IViewScreen::Controls);
	addScreen("Ingame", IViewScreen::Ingame);
	addScreen("GameOver", IViewScreen::GameOver);

	for (const std::pair<std::string, IViewScreen*>& screenPair : m_screens)
	{
		screenPair.second->switchOff();
	}

	activeScreen = getScreen("MainMenue");
	switchScreen("MainMenue");
}

void VUI::onNotify(const Event& evente)
{
	switch (evente)
	{
		case QUIT_GAME:
			isQuit = true;
			PostQuitMessage(0);
			break;
		case SEARCH_IP:
			break;

		case SWITCH_TO_LOBBY:
			switchScreen("Lobby");
			vMaster->lMaster->sendDefaultIPs();
			break;
		case SWITCH_TO_MAINMENUE:
			switchScreen("MainMenue");
			break;
		case SWITCH_TO_CREDITS:
			switchScreen("Credits");
			break;
		case SWITCH_TO_OPTIONS:
			switchScreen("Options");
			break;
		case SWITCH_TO_HELP:
			switchScreen("Help");
			break;
		case SWITCH_TO_CONTROLS:
			switchScreen("Controls");
			break;
		default:
			break;
	}
}

void VUI::resize(int width, int height)
{
	m_zf.ReSize(width, height);
	activeScreen->resize(width, height);

	for (std::pair<std::string, IViewScreen*> ScreenPair : m_screens)
	{
		ScreenPair.second->resize(width, height);
	}
}

void VUI::addScreen(const std::string& sName, const IViewScreen::ScreenType screenType)
{
	switch (screenType)
	{
		case IViewScreen::ScreenType::MainMenue:
			m_screens[sName] = new VScreenMainMenue(this);
			m_screens[sName]->addObserver(this);
			break;

		case IViewScreen::Lobby:
			m_screens[sName] = new VScreenLobby(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::ScreenType::Ingame:
			m_screens[sName] = new VScreenIngame(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Options:
			m_screens[sName] = new VScreenOptions(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Help:
			m_screens[sName] = new VScreenHelp(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Controls:
			m_screens[sName] = new VScreenControls(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::Credits:
			m_screens[sName] = new VScreenCredits(this);
			m_screens[sName]->addObserver(this);
			break;
		case IViewScreen::GameOver:
			m_screens[sName] = new VScreenGameOver(this);
			m_screens[sName]->addObserver(this);
			break;
		default: break;
	}
}

void VUI::switchScreen(const std::string& switchTo)
{
	ASSERT(activeScreen != nullptr, "No screen is initalized");
	ASSERT(m_screens.count(switchTo) > 0, "Screen" << switchTo << "not available");

	
	activeScreen->switchOff();
	activeScreen->EndEvent();
	activeScreen = m_screens[switchTo];
	activeScreen->switchOn();
	activeScreen->StartEvent();

	m_screenChanged = true;
}

IViewScreen* VUI::getScreen(const std::string& sName)
{
	ASSERT(m_screens.count(sName) > 0, "Screen" << sName << "not available");
	return m_screens[sName];
}

void VUI::updateMoney(const int wert, const LPlayer::PlayerId playerId)
{
	//Only update if UI is ready
	if (m_screens.count("Ingame") > 0)
	{
		CASTD<VScreenIngame*>(m_screens["Ingame"])->updateMoney(wert, playerId);
	}
}

void VUI::updatePopulation(const int wert)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updatePopulation(wert);
}

void VUI::updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateAddedPowerPlant(id, playerId);
}

void VUI::updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateRemovedPowerPlant(id, playerId);
}

void VUI::updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateNumberPowerLines(newNumberPowerLines, playerId);
}

void VUI::updateEnergySurplus(const int surplus)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateEnergyOverload(surplus);
}

void VUI::updateGameList(const std::unordered_map<std::string, Network::CGameObject>& gameList)
{
	CASTD<VScreenLobby*>(m_screens["Lobby"])->updateHostList(gameList);
}

void VUI::updateRegenerativeRatioLocal(float ratio)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateOwnGraphRatio(ratio);
}

void VUI::updateRegenerativeRatioRemote(float ratio)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateEnemyGraphRatio(ratio);
}

void VUI::switchCursor(const CursorType& cursorType)
{
	switch (cursorType)
	{
		default:
			break;
		case Default:

			SetCursor(m_Default_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_Default_Cursor));
			break;
		case Hammer:
			SetCursor(m_Hammer_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_Hammer_Cursor));
			break;
		case Sabotage:
			SetCursor(m_Sabotage_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_Sabotage_Cursor));
			break;

		case PowerOn:
			SetCursor(m_PowerOn_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_PowerOn_Cursor));
			break;

		case PowerOff:
			SetCursor(m_PowerOff_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_PowerOff_Cursor));
			break;

		case Sell:
			SetCursor(m_Sell_Cursor);
			SetClassLong(m_hwnd, GCLP_HCURSOR, DWORD(m_Sell_Cursor));
			break;
	}
}

void VUI::showMessage(const std::string& message)
{
	auto splitMessage = [] (const std::string& text)
	{
		const int numberOfCharactersPerLine = 80;

		if (numberOfCharactersPerLine - 1 > text.size())
		{
			//Single line
			return std::vector<std::string>();
		}

		std::string splitName = text.substr(numberOfCharactersPerLine);

		//Split on word boundaries
		std::regex txt_regex("^(\\w+\\b\\s?|\\s+\\b)");
		std::smatch base_match;

		if (!std::regex_search(splitName, base_match, txt_regex))
		{
			//Something went wrong --> single line
			return std::vector<std::string>();
		}

		std::string row1 = text.substr(0, numberOfCharactersPerLine + base_match.length());
		std::string row2 = text.substr(numberOfCharactersPerLine + base_match.length());

		return std::vector<std::string>{ row1, row2 };
	};

	const double secondsPerCharacter = 0.125;
	const std::vector<std::string> rows = splitMessage(message);

	if (rows.size() == 2)
	{
		CASTD<VScreenIngame*>(m_screens["Ingame"])->showMessage(rows[0], rows[1], message.length() * secondsPerCharacter);
	}
	else
	{
		CASTD<VScreenIngame*>(m_screens["Ingame"])->showMessage(message, "", message.length() * secondsPerCharacter);
	}
}

void VUI::removeMaterialFromRoot(CMaterial* material)
{
	m_zr.SubMaterial(material);
}


void VUI::setSabotageNumber(const int value)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->setSabotageNumber(value);
}

void VUI::contextMenuUpdateValue(const std::pair<int, int> & pos, const int value)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->updateFieldStorageValue(pos, "SellPrice", std::to_string(value));
}

void VUI::contextMenuUpdateResourceValue(const std::pair<int, int> & pos, const int resourceValue)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->updateFieldStorageValue(pos, "Resource", std::to_string(resourceValue));
}

void VUI::contextMenuUpdatePopulation(const std::pair<int, int> & pos, const int population)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->updateFieldStorageValue(pos, "Population", std::to_string(population));
}

void VUI::contextMenuUpdateEnergy(const std::pair<int, int> & pos, const int energy)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->updateFieldStorageValue(pos, "Energy", std::to_string(energy));
}

void VUI::contextMenuUpdateEnergySurplus(const std::pair<int, int> & pos, const int surplus)
{
}

void VUI::sabotageCostChanged(const int cost, const LSabotage::LSabotage sabotage)
{
	CASTD<VScreenIngame*>(getScreen("Ingame"))->updateSabotageCost(sabotage, cost);
}

void VUI::gameOver(bool win)
{
	if (win)
		CASTD<VText*>(getScreen("GameOver")->getContainer("MainContainer")->getGuiObject("Header"))->updateText("Sie haben gewonnen");
	else
		CASTD<VText*>(getScreen("GameOver")->getContainer("MainContainer")->getGuiObject("Header"))->updateText("Sie haben verloren");

	switchScreen("GameOver");
}

void VUI::tick(const float fTimeDelta)
{
	float fTimeDeltaCopy = fTimeDelta; //Copy needed because Vektoria means to change the time variable for some reasons (prevent undefined behaviour: http://en.cppreference.com/w/cpp/language/const_cast)
	m_zr.Tick(fTimeDeltaCopy);
	activeScreen->tick(fTimeDelta);
}


NAMESPACE_VIEW_E
