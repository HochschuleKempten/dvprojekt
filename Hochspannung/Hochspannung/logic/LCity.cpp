#include "LCity.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVCity.h"

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

			//Increase population
			setPopulationTotal(populationTotal + seconds * LBalanceLoader::getPopulationGrowth());

			//Calculate energy value
			lField->getLPlayingField()->calculateEnergyValueCity();

			//Check energy storage
			setEnergySurplus(CASTS<int>(energy - (populationTotal * LBalanceLoader::getConsumptionPerCitizen())));

			timeLastCheck = 0;
		}

		timeLastCheck += fTimeDelta;
	}
}

void LCity::setEnergy(const int energy)
{
	this->energy = energy;

	if (playerId & LPlayer::Local)
	{
		vCity->updateEnergy(energy);
	}
}

int LCity::getEnergy() const
{
	return energy;
}

void LCity::setPopulationTotal(const int populationTotal)
{
	if (populationTotal > LBalanceLoader::getMaxPopulation())
	{
		return;
	}

	this->populationTotal = populationTotal;

	if (playerId & LPlayer::Local)
	{
		vCity->updatePopulation(populationTotal);
	}
}

int LCity::getEnergySurplus() const
{
	return energySurplus;
}

void LCity::setEnergySurplus(const int surplus)
{
	this->energySurplus = surplus;

	if (energySurplus >= 0 && energySurplus < 50)
	{
		vCity->energyLow(energySurplus);
	}
	else if (energySurplus < 0)
	{
		//Player has lost
		lField->getLPlayingField()->getLMaster()->gameOver();
		return;
	}

	vCity->updateEnergySurplus(energySurplus);
}

NAMESPACE_LOGIC_E
