#pragma once

#include "IVTickObserver.h"
#include "LGeneral.h"
#include "LPlayer.h"
#include "../network/GameObject.h"
#include "LMessageLoader.h"

NAMESPACE_LOGIC_B

class IVFactory;

class IVMaster
{
protected:
	std::list<IVTickObserver*> observer;

	inline void updateTick(const float fTimeDelta)
	{
		for (IVTickObserver* o : observer) {
			o->tick(fTimeDelta);
		}
	}

public:
	inline virtual ~IVMaster()
	{
		ASSERT(observer.empty(), "Not every observer unregistered himself");
	}

	inline void registerObserver(IVTickObserver* observer)
	{
		this->observer.push_back(observer);
	}

	inline void unregisterObserver(IVTickObserver* observer)
	{
		this->observer.remove(observer);
	}

	virtual IVFactory* getFactory() = 0;
	virtual void gameWon() = 0;
	virtual void gameOver() = 0;
	virtual void startBuildingPlayingField() = 0;
	virtual void updateMoney(const int money, const LPlayer::PlayerId playerId) = 0;
	virtual void updateRemainingSabotageActs(const int remainingSabotageActs) = 0;
	virtual void updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId) = 0;
	virtual void updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId) = 0;
	virtual void updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId) = 0;
	virtual void updateGameList(const std::unordered_map<std::string, Network::CGameObject>& gameList) = 0;
	virtual void updateRegenerativeRatio(const float ratio, const LPlayer::PlayerId playerId) = 0;
	virtual void pauseGame() = 0;
	virtual void continueGame() = 0;
	virtual void showMessage(const std::string& message, const LMessageLoader::MessageID id) = 0;
	virtual void switchIngame() = 0;
	virtual void sabotageCostChanged(const int cost, const LSabotage::LSabotage sabotage) = 0;
};

NAMESPACE_LOGIC_E
