#include "LPlayer.h"
#include "LMaster.h"
#include "LPlayingField.h"
#include "ILPowerPlant.h"
#include "IVMaster.h"
#include "LRemoteOperation.h"
#include "LMessageLoader.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B


LPlayer::LPlayer(LMaster* lMaster, const PlayerId playerId)
	: lMaster(lMaster), playerId(playerId)
{
	lMaster->getVMaster()->registerObserver(this);

	setSabotageCostsRemove(LBalanceLoader::getSabotageCost(LSabotage::Remove));
	sabotageCostsResource(LBalanceLoader::getSabotageCost(LSabotage::Resource));
	sabotageCostsDeactivate(LBalanceLoader::getSabotageCost(LSabotage::Deactivate));
}

LPlayer::~LPlayer()
{
	lMaster->getVMaster()->unregisterObserver(this);
}

void LPlayer::tick(const float fTimeDelta)
{
	if (playerId == LPlayer::Local)
	{
		if (timeLastCheck > 1)
		{
			if (coolDownCounterRemove > 0) { coolDownCounterRemove--; }
			if (coolDownCounterDeactivate > 0) { coolDownCounterDeactivate--; }
			if (coolDownCounterResource > 0) { coolDownCounterResource--; }

			if (lMaster->getLPlayingField() != nullptr &&
				lMaster->getLPlayingField()->isInitDone() &&
				city->getPopulation() >= LBalanceLoader::getMaxPopulation() &&
				almost_equal(ratioRegenerative, 1.0F, 2))
			{
				lMaster->gameWon();
			}

			timeLastCheck = 0;
		}

		timeLastCheck += fTimeDelta;
	}
}

int LPlayer::getMoney() const
{
	return money;
}

void LPlayer::addMoney(const int amount)
{
	money += amount;
	lMaster->getVMaster()->updateMoney(money, playerId);
}

void LPlayer::subtractMoney(const int amount)
{
	money -= amount;
	lMaster->getVMaster()->updateMoney(money, playerId);
	ASSERT(money >= 0, "The player has not enough money");
}

bool LPlayer::isSabotagePossible(const LSabotage::LSabotage sabotageType) const
{
	// checks if player has to wait and if not, sets the new cooldown value
	auto checkCooldown = [this, sabotageType]()
	{
		switch (sabotageType)
		{
		case (LSabotage::Remove) :
			if (coolDownCounterRemove > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterRemove) });
				return false;
			}
			
			return true;

		case(LSabotage::Deactivate) :
			if (coolDownCounterDeactivate > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterDeactivate) });
				return false;
			}

			return true;

		case(LSabotage::Resource) :
			if (coolDownCounterResource > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterResource) });
				return false;
			}

			return true;

		default:
			return false;
		}
	};

	if (sabotageActs > 0)
	{
		int sabotageCost = LBalanceLoader::getSabotageCost(sabotageType);

		if (getMoney() < sabotageCost)
		{
			LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_NO_MONEY);
			return false;
		}

		if (!checkCooldown())
		{
			return false;
		}
		
		return true;
	}

	LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_NO_ACTS_LEFT);
	return false;
}

void LPlayer::addPowerPlant(ILPowerPlant* powerPlant)
{
	ASSERT(playerId == powerPlant->getPlayerId(), "Tried to add a power plant from player " << powerPlant->getPlayerId() << " to player " << playerId);

	powerPlants.emplace_back(powerPlant);

	if (playerId == LPlayer::Local)
	{
		LRemoteOperation remoteOperation(lMaster->getLPlayingField(), powerPlant);
		remoteOperation.switchOn();
	} 
	else if (playerId == LPlayer::Remote)
	{
		powerPlant->switchOn();
	}

	lMaster->getVMaster()->updateAddedPowerPlant(powerPlant->getIdentifier(), playerId);
}

void LPlayer::removePowerPlant(const ILPowerPlant* const powerPlant)
{
	ASSERT(playerId == powerPlant->getPlayerId(), "Tried to remove a power plant from player " << powerPlant->getPlayerId() << " to player " << playerId);

	powerPlants.erase(std::remove(powerPlants.begin(), powerPlants.end(), powerPlant), powerPlants.end());
	lMaster->getVMaster()->updateRemovedPowerPlant(powerPlant->getIdentifier(), playerId);
	
	if (playerId == LPlayer::Local && !lMaster->getLPlayingField()->isLocalOperation())
	{
		checkDisposalValue(powerPlant);
	}
}

void LPlayer::addPowerLine(LPowerLine* powerLine)
{
	ASSERT(playerId == powerLine->getPlayerId(), "Tried to add a powerline from player " << powerLine->getPlayerId() << " to player " << playerId);

	powerLines.emplace_back(powerLine);
	lMaster->getVMaster()->updateNumberPowerLines(CASTS<int>(powerLines.size()), playerId);
}

void LPlayer::removePowerLine(const LPowerLine* const powerLine)
{
	ASSERT(playerId == powerLine->getPlayerId(), "Tried to remove a powerline from player " << powerLine->getPlayerId() << " to player " << playerId);

	powerLines.erase(std::remove(powerLines.begin(), powerLines.end(), powerLine), powerLines.end());
	lMaster->getVMaster()->updateNumberPowerLines(CASTS<int>(powerLines.size()), playerId);

	if (playerId == LPlayer::Local && !lMaster->getLPlayingField()->isLocalOperation())
	{
		checkDisposalValue(powerLine);
	}
}

void LPlayer::checkPowerPlants()
{
	std::vector<int> cityConnections = lMaster->getLPlayingField()->getCityConnections();
	std::vector<ILPowerPlant*> currentConnectedPowerPlants;

	for (const int pPos : cityConnections)
	{
		ILPowerPlant* p = dynamic_cast<ILPowerPlant*>(lMaster->getLPlayingField()->getField(lMaster->getLPlayingField()->convertIndex(pPos))->getBuilding());
		if (p != nullptr)
		{
			currentConnectedPowerPlants.emplace_back(p);
		}
	}

	std::vector<ILPowerPlant*> differencesPrevCurrent;
	std::vector<ILPowerPlant*> differencesCurrentPrev;

	//The ranges need to be sorted before difference is calculated
	std::sort(prevConnectedPowerPlants.begin(), prevConnectedPowerPlants.end());
	std::sort(currentConnectedPowerPlants.begin(), currentConnectedPowerPlants.end());

	//Prev - Current --> turn off
	std::set_difference(
		prevConnectedPowerPlants.begin(),
		prevConnectedPowerPlants.end(),
		currentConnectedPowerPlants.begin(),
		currentConnectedPowerPlants.end(),
		std::back_inserter(differencesPrevCurrent));

	//Current - Prev --> turn on
	std::set_difference(
		currentConnectedPowerPlants.begin(),
		currentConnectedPowerPlants.end(),
		prevConnectedPowerPlants.begin(),
		prevConnectedPowerPlants.end(),
		std::back_inserter(differencesCurrentPrev));

	for (ILPowerPlant* p : differencesPrevCurrent)
	{
		if (std::find(powerPlants.begin(), powerPlants.end(), p) != powerPlants.end())
		{
			//The check is only done by the player itself, so this is always a remote operation
			LRemoteOperation remoteOperation(lMaster->getLPlayingField(), p);
			remoteOperation.switchOff();
		}
	}

	for (ILPowerPlant* p : differencesCurrentPrev)
	{
		//The check is only done by the player itself, so this is always a remote operation
		LRemoteOperation remoteOperation(lMaster->getLPlayingField(), p);
		remoteOperation.switchOn();
	}

	prevConnectedPowerPlants = currentConnectedPowerPlants;

	//update sell values
	bool connected = lMaster->getLPlayingField()->isTransformstationConnected();

	if (!this->lMaster->getLPlayingField()->isFirstConnected())
	{
		this->lMaster->getLPlayingField()->setFirstConnected(); // player reached the transformer station
	}

	for (ILPowerPlant* p : powerPlants)
	{	
		p->setConnected(connected);

	}
	for (LPowerLine* l : powerLines)
	{
		l->setConnected(connected);
	}

	checkRegenerativeRatio();

	//Update sabotage costs
	if (!lMaster->getLPlayingField()->isFirstConnected())
	{
		double disconnectedFactor = LBalanceLoader::getSabotageDiscountDisconnected();
		setSabotageCostsRemove(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Remove) * 1.0 / disconnectedFactor));
		setSabotageCostsResource(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Resource) * 1.0 / disconnectedFactor));
		setSabotageCostsDeactivate(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Deactivate) * 1.0 / disconnectedFactor));
	}
	else if (!lMaster->getLPlayingField()->isTransformstationConnected())
	{
		setSabotageCostsRemove(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Remove) * LBalanceLoader::getSabotageDiscountDisconnected()));
		setSabotageCostsResource(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Resource) * LBalanceLoader::getSabotageDiscountDisconnected()));
		setSabotageCostsDeactivate(CASTS<int>(LBalanceLoader::getSabotageCost(LSabotage::Deactivate) * LBalanceLoader::getSabotageDiscountDisconnected()));
	}
	else
	{
		setSabotageCostsRemove(LBalanceLoader::getSabotageCost(LSabotage::Remove));
		setSabotageCostsResource(LBalanceLoader::getSabotageCost(LSabotage::Resource));
		setSabotageCostsDeactivate(LBalanceLoader::getSabotageCost(LSabotage::Deactivate));
	}
}

bool LPlayer::sabotageRemove(ILBuilding* lBuilding)
{
	if (isSabotagePossible(LSabotage::Remove) && lBuilding->sabotageRemove())
	{
		performSabotage(LSabotage::Remove);
		
		return true;
	}

	return false;
}

bool LPlayer::sabotageDeactivate(ILPowerPlant* lPowerPlant)
{
	if (isSabotagePossible(LSabotage::Deactivate) && lPowerPlant->sabotageDeactivate())
	{
		performSabotage(LSabotage::Deactivate);
		
		return true;
	}

	return false;
}

bool LPlayer::sabotageResource(ILPowerPlant* lPowerPlant)
{
	if (isSabotagePossible(LSabotage::Resource) && lPowerPlant->sabotageResource())
	{
		performSabotage(LSabotage::Resource);
		
		return true;
	}

	return false;
}

void LPlayer::performSabotage(const LSabotage::LSabotage sabotageType)
{
	switch (sabotageType)
	{
		case LSabotage::Deactivate:
			coolDownCounterDeactivate = LBalanceLoader::getSabotageCooldown(sabotageType);
			break;

		case LSabotage::Resource:
			coolDownCounterResource = LBalanceLoader::getSabotageCooldown(sabotageType);
			break;

		case LSabotage::Remove:
			coolDownCounterRemove = LBalanceLoader::getSabotageCooldown(sabotageType);
			break;

		default: break;
	}
	
	sabotageActs--;

	subtractMoney(LBalanceLoader::getSabotageCost(sabotageType));

	lMaster->getVMaster()->updateRemainingSabotageActs(sabotageActs);
	LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_EMITTED, { std::to_string(sabotageActs) });
}

void LPlayer::setSabotageCostsRemove(int sabotageCostsRemove1)
{
	if (sabotageCostsRemove != sabotageCostsRemove1)
	{
		sabotageCostsRemove = sabotageCostsRemove1;
		lMaster->getVMaster()->sabotageCostChanged(sabotageCostsRemove, LSabotage::Remove);
	}
}

void LPlayer::setSabotageCostsResource(int sabotageCostsResource1)
{
	if (sabotageCostsResource != sabotageCostsResource1)
	{
		sabotageCostsResource = sabotageCostsResource1;
		lMaster->getVMaster()->sabotageCostChanged(sabotageCostsResource, LSabotage::Resource);
	}
}

void LPlayer::setSabotageCostsDeactivate(int sabotageCostsDeactivate1)
{
	if (sabotageCostsDeactivate != sabotageCostsDeactivate1)
	{
		sabotageCostsDeactivate = sabotageCostsDeactivate1;
		lMaster->getVMaster()->sabotageCostChanged(sabotageCostsDeactivate, LSabotage::Deactivate);
	}
}

void LPlayer::checkRegenerativeRatio()
{
	auto countTotalPowerPlant = std::count_if(prevConnectedPowerPlants.begin(), prevConnectedPowerPlants.end(), [] (ILPowerPlant* pP)
	{
		return pP->isActivated;
	});

	//calculate ratio regenerative
	auto countRegenerativePowerPlants = std::count_if(prevConnectedPowerPlants.begin(), prevConnectedPowerPlants.end(), [] (ILPowerPlant* pP)
	{
		return pP->isRegenerative() && pP->isActivated;
	});


	if (countTotalPowerPlant != 0)
	{
		ratioRegenerative = CASTS<float>(countRegenerativePowerPlants) / CASTS<float>(countTotalPowerPlant);
	} 
	else
	{
		ratioRegenerative = 0;
	}

	lMaster->getVMaster()->updateRegenerativeRatio(ratioRegenerative, playerId);

	lMaster->sendRegenerativeRatio(ratioRegenerative);
}

void LPlayer::checkDisposalValue(const ILBuilding* const building)
{
	//Player gets money back (connection check is done in getValue())
	addMoney(building->getValue());
}

NAMESPACE_LOGIC_E
