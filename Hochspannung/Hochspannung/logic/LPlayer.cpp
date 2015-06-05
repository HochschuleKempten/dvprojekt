#include "LPlayer.h"
#include "LMaster.h"
#include "LPlayingField.h"
#include "ILPowerPlant.h"
#include "IVMaster.h"
#include "LRemoteOperation.h"
#include "LMessageLoader.h"

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
	if (timeLastCheck > 1)
	{
		if (coolDownCounterPowerLine > 0) { coolDownCounterPowerLine--; }
		if (coolDownCounterPowerPlant > 0) { coolDownCounterPowerPlant--; }
		if (coolDownCounterResource > 0) { coolDownCounterResource--; }

		timeLastCheck = 0;
	}

	timeLastCheck += fTimeDelta;
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
	auto getSabotageCost = [sabotageType] ()
	{
		switch (sabotageType)
		{
		case (LSabotage::PowerLine) :
			return LBalanceLoader::getCostSabotagePowerLine();
		case(LSabotage::PowerPlant) :
			return LBalanceLoader::getCostSabotagePowerPlant();
		case(LSabotage::Resource) :
			return LBalanceLoader::getCostSabotageResource();
		default:
			return -1;
		}
	};

	// checks if player has to wait and if not, sets the new cooldown value
	auto checkCooldown = [this, sabotageType]()
	{
		switch (sabotageType)
		{
		case (LSabotage::PowerLine) :
			if (coolDownCounterPowerLine > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterPowerLine) });
				return false;
			}

			coolDownCounterPowerLine = LBalanceLoader::getCooldownTimeSabotagePowerLine();
			return true;

		case(LSabotage::PowerPlant) :
			if (coolDownCounterPowerPlant > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterPowerPlant) });
				return false;
			}

			coolDownCounterPowerPlant = LBalanceLoader::getCooldownTimeSabotagePowerPlant();
			return true;

		case(LSabotage::Resource) :
			if (coolDownCounterResource > 0)
			{
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_WAIT, { std::to_string(coolDownCounterResource) });
				return false;
			}

			coolDownCounterResource = LBalanceLoader::getCooldownTimeSabotageResource();
			return true;

		default:
			return false;
		}
	};

	if (sabotageActs > 0)
	{
		int sabotageCost = getSabotageCost();

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

	lMaster->getVMaster()->updateAddedPowerPlant(powerPlant->getIdentifier(), playerId);
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

	//calculate ratio regenerative
	int countRegenerativePowerPlants = std::count_if(powerPlants.begin(), powerPlants.end(), [](ILPowerPlant* pP) { return pP->isRegenerative() && pP->isActivated; });
	if (prevConnectedPowerPlants.size() != 0)
	{ 
		float ratioRegenerative = countRegenerativePowerPlants / prevConnectedPowerPlants.size();
		lMaster->getVMaster()->updateRegenerativeRatio(ratioRegenerative);
	}
	else
	{
		//TODO (L) GAME OVER as there are no connected powerplants ???
	}
}

NAMESPACE_LOGIC_E
