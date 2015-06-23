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

void VMaster::updateRegenerativeRatio(const float ratio, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	{
		vUi.updateRegenerativeRatioLocal(ratio);
	}
	else if (playerId == LPlayer::Remote)
	{
		vUi.updateRegenerativeRatioRemote(ratio);
	}
}

void VMaster::gameOver()
{
	static bool informed = false;
	if (!informed) {
		VSoundLoader::playSoundeffect(VSoundLoader::GAME_OVER, nullptr);
		informed = true;
		vUi.gameOver(false);
	}
}

void VMaster::updateGameList(const std::unordered_map<std::string, Network::CGameObject>& gameList)
{
	vUi.updateGameList(gameList);
}

void VMaster::showMessage(const std::string& message, const LMessageLoader::MessageID id)
{
	vUi.showMessage(message);
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

void VMaster::hostGame(const std::string & gameName)
{
	lMaster->hostGame(gameName);
}

void VMaster::startSinglePlayerGame()
{
	lMaster->startSinglePlayerGame();
}

void VMaster::joinGame(const std::string& ipAddress)
{
	lMaster->joinGame(ipAddress);
}

void VMaster::startBuildingPlayingField()
{
	//TODO (V) inform UI
}

void VMaster::updateMoney(const int money, const LPlayer::PlayerId playerId)
{
	vUi.updateMoney(money, playerId);
}

void VMaster::updateRemainingSabotageActs(const int remainingSabotageActs)
{
	vUi.setSabotageNumber(remainingSabotageActs);
}

void VMaster::updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	vUi.updateAddedPowerPlant(id, playerId);
}

void VMaster::updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	vUi.updateRemovedPowerPlant(id, playerId);
}

void VMaster::updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId)
{
	vUi.updateNumberPowerLines(newNumberPowerLines, playerId);
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
	vUi.gameOver(true);
}


NAMESPACE_VIEW_E
