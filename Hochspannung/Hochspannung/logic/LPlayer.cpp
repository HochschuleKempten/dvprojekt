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

			if (lMaster->getLPlayingField() != nullptr && lMaster->getLPlayingField()->isInitDone() && city->getPopulation() >= LBalanceLoader::getMaxPopulation() && almost_equal(ratioRegenerative, 1.0F, 2))
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

bool LPlayer::trySabotageAct(const LSabotage::LSabotage sabotageType)
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

			coolDownCounterRemove = LBalanceLoader::getSabotageCooldown(sabotageType);
			return true;

		case(LSabotage::Deactivate) :
			if (coolDownCounterDeactivate > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterDeactivate) });
				return false;
			}

			coolDownCounterDeactivate = LBalanceLoader::getSabotageCooldown(sabotageType);
			return true;

		case(LSabotage::Resource) :
			if (coolDownCounterResource > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterResource) });
				return false;
			}

			coolDownCounterResource = LBalanceLoader::getSabotageCooldown(sabotageType);
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

		//Everything fine at this point
		sabotageActs--;
		subtractMoney(sabotageCost);
		lMaster->getVMaster()->updateRemainingSabotageActs(sabotageActs);
		LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_EMITTED, { std::to_string(sabotageActs) });
		
		return true;
	}

	LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_NO_ACTS_LEFT);
	return false;
}

void LPlayer::addPowerPlant(ILPowerPlant* powerPlant)
{
	ASSERT(playerId == powerPlant->getPlayerId(), "Tried to add a power plant from player " << powerPlant->getPlayerId() << " to player " << playerId);

	powerPlants.emplace_back(powerPlant);

	LRemoteOperation remoteOperation(lMaster->getLPlayingField(), powerPlant);
	remoteOperation.switchOn();

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
		//The check is only done by the player itself, so this is always a remote operation
		LRemoteOperation remoteOperation(lMaster->getLPlayingField(), p);
		remoteOperation.switchOff();
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
	for (ILPowerPlant* p : powerPlants)
	{	
		p->setConnected(connected);

	}
	for (LPowerLine* l : powerLines)
	{
		l->setConnected(connected);
	}

	checkRegenerativeRatio();
}

bool LPlayer::sabotageRemove(ILBuilding* lBuilding)
{
	if (trySabotageAct(LSabotage::Remove))
	{
		lBuilding->sabotageRemove();
		return true;
	}

	return false;
}

bool LPlayer::sabotageDeactivate(ILPowerPlant* lPowerPlant)
{
	if (trySabotageAct(LSabotage::Deactivate))
	{
		lPowerPlant->sabotagePowerPlant();

		return true;
	}

	return false;
}

bool LPlayer::sabotageResource(ILPowerPlant* lPowerPlant)
{
	if (trySabotageAct(LSabotage::Resource))
	{
		lPowerPlant->sabotageResource();

		return true;
	}

	return false;
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
