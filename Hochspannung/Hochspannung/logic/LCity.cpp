#include "LCity.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVCity.h"
#include "LRemoteOperation.h"

NAMESPACE_LOGIC_B

LCity::LCity(LField* lField, const int x, const int y, const int playerId)
	: ILBuilding(lField, playerId), vCity(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createCity(this))
{
	vCity->initCity(vCity, x, y);
	lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
}

LCity::~LCity()
{
	lField->getLPlayingField()->getLMaster()->getVMaster()->unregisterObserver(this);
}

void LCity::tick(const float fTimeDelta)
{
	//if game is paused or not initialized or city from remote player, do nothing
	if (!lField->getLPlayingField()->getLMaster()->isGamePaused() &&
		lField->getLPlayingField()->isInitDone() &&
		playerId & LPlayer::Local)
	{
		//Handle the population increase (every second)
		if (timeLastCheck > 1)
		{
			int seconds = CASTS<int>(timeLastCheck);

			//Calculate energy value
			lField->getLPlayingField()->calculateEnergyValueCity();

			//Check energy storage
			int surplus = CASTS<int>(energy - (populationTotal * LBalanceLoader::getConsumptionPerCitizen()));
			setEnergySurplus(surplus);

			LRemoteOperation remoteOperation(getLField()->getLPlayingField(), this);

			//Avoid jumping around the borders
			if (surplus > LBalanceLoader::getConsumptionPerCitizen())
			{
				//Increase population
				remoteOperation.setPopulationTotal(populationTotal + seconds * LBalanceLoader::getPopulationGrowth());

			}
			else if (surplus < -LBalanceLoader::getConsumptionPerCitizen())
			{
				//Decrease population
				remoteOperation.setPopulationTotal(populationTotal - seconds * LBalanceLoader::getPopulationGrowth());
			}

			timeLastCheck = 0;
		}

		timeLastCheck += fTimeDelta;
	}
}

void LCity::setEnergy(const int energy)
{
	this->energy = energy;

	vCity->updateEnergy(energy);
}

int LCity::getEnergy() const
{
	return energy;
}

void LCity::setPopulationTotal(const int populationTotal)
{
	if (populationTotal > LBalanceLoader::getMaxPopulation())
	{
		this->populationTotal = LBalanceLoader::getMaxPopulation();
	} 
	else
	{
		this->populationTotal = populationTotal;
	}

	vCity->updatePopulation(populationTotal);

	if (!getLField()->getLPlayingField()->isLocalOperation())
	{
		getLField()->getLPlayingField()->getLMaster()->sendCityPopulation(this->populationTotal);
	}
}

int LCity::getPopulation() const
{
	return populationTotal;
}

int LCity::getEnergySurplus() const
{
	return energySurplus;
}

bool LCity::checkSell() const
{
	return false;
}

void LCity::setEnergySurplus(const int surplus)
{
	this->energySurplus = surplus;

	if (playerId & LPlayer::Local)
	{
		if (energySurplus < LBalanceLoader::getSurplusWarningThreshold())
		{
			vCity->energyLow(energySurplus);
			LMessageLoader::emitMessage(LMessageLoader::SURPLUS_LOW);
		}
	}

	vCity->updateEnergySurplus(energySurplus);
}

NAMESPACE_LOGIC_E
