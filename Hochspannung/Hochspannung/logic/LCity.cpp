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
{}

void LCity::tick(const float fTimeDelta)
{
	//if game is paused or not initialized or city from remote player, do nothing
	if (!lField->getLPlayingField()->getLMaster()->isGamePaused() &&
		lField->getLPlayingField()->isInitDone() &&
		playerId & LPlayer::Local)
	{
		static float timeLastCheck = 0;

		//Handle the population increase (every second)
		if (timeLastCheck > 1)
		{
			int seconds = CASTS<int>(timeLastCheck);

			//Increase population
			setPopulationTotal(populationTotal + seconds * LBalanceLoader::getPopulationGrowth());

			//Calculate energy value
			lField->getLPlayingField()->calculateEnergyValueCity();

			//Check energy storage
			int surplus = CASTS<int>(energy - (populationTotal * LBalanceLoader::getConsumptionPerCitizen()));
			DEBUG_OUTPUT("surplus = " << surplus);

			if (surplus >= 0 && surplus < 50)
			{
				vCity->energyLow(surplus);
			}
			else if (surplus < 0)
			{
				//Player has lost
				lField->getLPlayingField()->getLMaster()->gameOver();
			}

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

int LCity::getEnergySurplus()
{
	return energy - populationTotal;
}

NAMESPACE_LOGIC_E
