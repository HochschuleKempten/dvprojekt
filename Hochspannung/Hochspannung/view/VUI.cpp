#include "VUI.h"
#include "VMaster.h"
#include "IViewScreen.h"
#include "VScreenMainMenue.h"
#include "VScreenIngame.h"
#include "VScreenLobby.h"
#include "VScreenCredits.h"
#include "VScreenOptions.h"
#include "../logic/LMaster.h"

NAMESPACE_VIEW_B


VUI::VUI(VMaster* vMaster)
	: vMaster(vMaster), isQuit(false)
{
	vMaster->registerObserver(this);
}

VUI::~VUI()
{}

void VUI::initUI(HWND hwnd, CSplash* psplash)
{
	m_zr.Init(psplash);

	//get computer name
	std::vector<const char*> computerNameBlacklist{ "TITANIC-TABLET" };	//Opt-in when you want to compile the shaders at every start
	unsigned long bufCharCount = 32767;
	char buf[32767];

	//check if the computername is in the blacklist --> recompile Shader
	if (GetComputerName(buf, &bufCharCount) && std::find_if(computerNameBlacklist.begin(), computerNameBlacklist.end(), [&buf](const char* name) { return strcmp(name, buf) == 0; }) != computerNameBlacklist.end())
	{
		m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput, eApiSound_DirectSound, eShaderCreation_ForceCompile, eShaderAutoRecompilation_Disabled);
	}
	else
	{
		m_zf.Init(hwnd);
	}
	m_zr.AddFrameHere(&m_zf);

	m_zf.AddDeviceKeyboard(&m_zkKeyboard);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);

	addScreen("MainMenue", IViewScreen::MainMenue);
	addScreen("Lobby", IViewScreen::Lobby);
	addScreen("Credits", IViewScreen::Credits);
	addScreen("Options", IViewScreen::Options);
	addScreen("Ingame", IViewScreen::Ingame);

	for (const std::pair<std::string, IViewScreen*>& screenPair : m_screens) {
		screenPair.second->switchOff();
	}

	activeScreen = getScreen("MainMenue");
	switchScreen("MainMenue");
}

void VUI::onNotify(Event evente)
{
	switch (evente) {
		case QUIT_GAME:
			isQuit = true;
			PostQuitMessage(0);
			vMaster->lMaster->gameOver();
			break;
		case SEARCH_IP:
			break;

		case SWITCH_TO_LOBBY:
			switchScreen("Lobby");
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
		default:
			break;
	}
}

void VUI::resize(int width, int height)
{
	m_zf.ReSize(width, height);
	activeScreen->resize(width, height);

	for (m_iterScreens = m_screens.begin(); m_iterScreens != m_screens.end(); m_iterScreens++) {
		m_iterScreens->second->resize(width, height);
	}
}

void VUI::addScreen(const std::string& sName, const IViewScreen::ScreenType screenType)
{
	switch (screenType) {
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
		case IViewScreen::Credits:
			m_screens[sName] = new VScreenCredits(this);
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
}

IViewScreen* VUI::getScreen(const std::string& sName)
{
	ASSERT(m_screens.count(sName) > 0, "Screen" << sName << "not available");
	return m_screens[sName];
}

void VUI::updateMoney(const int wert)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updateMoney(wert);
}

void VUI::updatePopulation(const int wert)
{
	CASTD<VScreenIngame*>(m_screens["Ingame"])->updatePopulation(wert);
}

void VUI::updateGameList(const std::vector<Network::CGameObject>& gameList)
{
	CASTD<VScreenLobby*>(m_screens["Lobby"])->updateHostList(gameList);
}

void VUI::tick(const float fTimeDelta)
{
	m_zr.Tick(const_cast<float&>(fTimeDelta));
	activeScreen->tick();

}


NAMESPACE_VIEW_E
