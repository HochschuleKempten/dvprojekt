#include "VMaster.h"
#include "../logic/LMaster.h"
#include "VFactory.h"
#include "VPlayingField.h"
#include "VUI.h"
#include "IViewObject.h"
#include "VMaterialLoader.h"
#include "VScreenIngame.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VMaster::VMaster()
	: factory(this), vUi(this)
{
	VMaterialLoader::init();
}

VMaster::~VMaster()
{}

void VMaster::setLMaster(LMaster* lMaster)
{
	this->lMaster = lMaster;
}

LMaster* VMaster::getLMaster() const
{
	return lMaster;
}

void VMaster::initScene(HWND hwnd, CSplash* psplash)
{	
	vUi.initUI(hwnd, psplash);
}

void VMaster::tick(float /*fTime*/, float fTimeDelta)
{
	if (lMaster->isGamePaused())
	{
		//The logic side must be informed even in pause mode
		lMaster->tick(fTimeDelta);
	}
	else
	{
		updateTick(fTimeDelta);
	}
}

IVFactory* VMaster::getFactory()
{
	return &factory;
}

void VMaster::updateRegenerativeRatio(const float ratio)
{
	//todo (V) show new ratio
	DEBUG_OUTPUT("New regenerative ratio: " << ratio);
}

void VMaster::gameOver()
{
	static bool informed = false;
	if (!informed) {
		VSoundLoader::playSoundeffect(VSoundLoader::GAME_OVER, nullptr);
		informed = true;
	}
	//TODO (V) do something useful here when UI is ready
}

void VMaster::updateGameList(const std::vector<Network::CGameObject>& gameList)
{
	vUi.updateGameList(gameList);

	DEBUG_OUTPUT("Updated List");
	for (auto go : gameList)
	{
		DEBUG_OUTPUT("ip = " << go.getServerIP());
		DEBUG_OUTPUT("name = " << go.getName());
	}
}

void VMaster::showMessage(const std::string& message, const LMessageLoader::MessageID id)
{
	vUi.showMessage(message);
	VSoundLoader::playRadioMessage(id);
}

VUI* VMaster::getVUi()
{
	return &vUi;
}

void VMaster::setVPlayingField(const std::shared_ptr<VPlayingField>& vPlayingField)
{
	this->vPlayingField = vPlayingField;
	CASTD<VScreenIngame*>(vUi.getScreen("Ingame"))->addToScene(vPlayingField->getPlacement());
}

void VMaster::resize(int width, int height)
{
	//On some systems the width is very small (0, 2, ...) and a resize with that values result in assertion failures
	if (width <= 20 || height <= 20)
	{
		return;
	}

	vUi.resize(width, height);
}

void VMaster::hostGame()
{
	lMaster->startNewGame();
}

void VMaster::startSinglePlayerGame()
{
	lMaster->startNewGame("SINGLE_PLAYER");
}

void VMaster::joinGame(const std::string& ipAddress)
{
	lMaster->startNewGame(ipAddress);
}

void VMaster::startBuildingPlayingField()
{
	//TODO (V) inform UI
}

void VMaster::updateMoney(const int money, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	{
		vUi.updateMoney(money);
	}
}

void VMaster::updateRemainingSabotageActs(const int remainingSabotageActs)
{
	//TODO (V) Show remaining sabotage acts
}

void VMaster::updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	{
		vUi.updateAddedPowerPlant(id);
	}
}

void VMaster::updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	{
		vUi.updateRemovedPowerPlant(id);
	}
}

void VMaster::updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	{
		vUi.updateNumberPowerLines(newNumberPowerLines);
	}
}

void VMaster::pauseGame()
{
	//todo (V) implement
}

void VMaster::continueGame()
{
	//todo (V) implement
}

void VMaster::gameWon()
{
	VSoundLoader::playSoundeffect(VSoundLoader::GAME_WON, nullptr);
	//todo (V) exit the game
}

NAMESPACE_VIEW_E
