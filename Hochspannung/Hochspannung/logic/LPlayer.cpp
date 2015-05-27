#include "LPlayer.h"
#include "LMaster.h"
#include "LPlayingField.h"
#include "ILPowerPlant.h"
#include "IVMaster.h"
#include "LBalanceLoader.h"
#include "LRemoteOperation.h"

NAMESPACE_LOGIC_B


LPlayer::LPlayer(LMaster* lMaster)
	: lMaster(lMaster)
{
	lMaster->getVMaster()->registerObserver(this);
}

LPlayer::~LPlayer()
{
	lMaster->getVMaster()->unregisterObserver(this);
}

void LPlayer::tick(const float fTimeDelta)
{
	static float timeLastCheck = 0;

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
	lMaster->getVMaster()->updateMoney(money);
}

void LPlayer::subtractMoney(const int amount)
{
	money -= amount;
	lMaster->getVMaster()->updateMoney(money);
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
				lMaster->getVMaster()->messageSabotageFailed(std::string("Powerline sabotage not possible, you have to wait ") + std::to_string(coolDownCounterPowerLine) + std::string(" seconds."));
				return false;
			}

			coolDownCounterPowerLine = LBalanceLoader::getCooldownTimeSabotagePowerLine();
			return true;

		case(LSabotage::PowerPlant) :
			if (coolDownCounterPowerPlant > 0)
			{
				lMaster->getVMaster()->messageSabotageFailed(std::string("Powerline sabotage not possible, you have to wait ") + std::to_string(coolDownCounterPowerLine) + std::string(" seconds."));
				return false;
			}

			coolDownCounterPowerPlant = LBalanceLoader::getCooldownTimeSabotagePowerPlant();
			return true;

		case(LSabotage::Resource) :
			if (coolDownCounterResource > 0)
			{
				lMaster->getVMaster()->messageSabotageFailed(std::string("Powerline sabotage not possible, you have to wait ") + std::to_string(coolDownCounterPowerLine) + std::string(" seconds."));
				return false;
			}

			coolDownCounterResource = LBalanceLoader::getCooldownTimeSabotageResource();
			return true;

		default:
			return false;
		}
	};

	if (sabotageActs == -1)
	{
		sabotageActs = LBalanceLoader::getSabotageActs();
	}

	if (sabotageActs > 0)
	{
		int sabotageCost = getSabotageCost();

		if (getMoney() >= sabotageCost && checkCooldown())
		{
			sabotageActs--;
			subtractMoney(sabotageCost);
			lMaster->getVMaster()->updateRemainingSabotageActs(sabotageActs);

			return true;
		}

		lMaster->getVMaster()->messageSabotageFailed("You do not have enough money or have to wait!");
		return false;
	}

	lMaster->getVMaster()->messageSabotageFailed("No sabotage acts left!");
	return false;
}

void LPlayer::addPowerPlant(ILPowerPlant* powerPlant)
{
	//TODO (L) inform ui
	powerPlants.emplace_back(powerPlant);

	LRemoteOperation remoteOperation(lMaster->getLPlayingField(), powerPlant);
	remoteOperation.switchOn();
}

void LPlayer::removePowerPlant(const ILPowerPlant* const powerPlant)
{
	//TODO (L) inform ui
	powerPlants.erase(std::remove(powerPlants.begin(), powerPlants.end(), powerPlant), powerPlants.end());
}

void LPlayer::checkPowerPlants()
{
	std::vector<int> cityConnections = lMaster->getLPlayingField()->getCityConnections();
	std::vector<ILPowerPlant*> connectedPowerPlants;

	for (const int pPos : cityConnections)
	{
		ILPowerPlant* p = dynamic_cast<ILPowerPlant*>(lMaster->getLPlayingField()->getField(lMaster->getLPlayingField()->convertIndex(pPos))->getBuilding());
		if (p != nullptr)
		{
			connectedPowerPlants.emplace_back(p);
		}
	}

	std::vector<ILPowerPlant*> differences;
	std::sort(powerPlants.begin(), powerPlants.end());
	std::sort(connectedPowerPlants.begin(), connectedPowerPlants.end());

	std::set_symmetric_difference(
		powerPlants.begin(),
		powerPlants.end(),
		connectedPowerPlants.begin(),
		connectedPowerPlants.end(),
		std::back_inserter(differences));

	for (ILPowerPlant* p : differences)
	{
		//The check is only done by the player itself, so this is always a remote operation
		LRemoteOperation remoteOperation(lMaster->getLPlayingField(), p);
		remoteOperation.switchOff();
	}
}

NAMESPACE_LOGIC_E
