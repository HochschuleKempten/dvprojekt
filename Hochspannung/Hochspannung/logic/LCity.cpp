#include "LCity.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVCity.h"

NAMESPACE_LOGIC_B


LCity::LCity(LField* lField, const int x, const int y)
	: ILBuilding(lField), vCity(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createCity(this))
{
	vCity->initCity(vCity, x, y);
	lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
}

LCity::~LCity()
{
}

void LCity::tick(const float fTimeDelta)
{
	static float timeLastCheck = 0;

	//Handle the population increase
	if (timeLastCheck > 1) {
		int seconds = CASTS<int>(timeLastCheck);
		ASSERT(seconds >= 1, "The number of seconds is invalid.");

		setPopulationTotal(populationTotal + seconds * populationIncrease);

		timeLastCheck = 0;
	}

	//Check energy storage
	int superplus = energy - (populationTotal * consumptionCitizen);
	if (superplus < 0) {
		//Player has lost
		lField->getLPlayingField()->getLMaster()->gameLost();
	}

	timeLastCheck += fTimeDelta;
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
	this->populationTotal = populationTotal;
	vCity->updatePopulation(populationTotal);
}

int LCity::getEnergySurplus()
{
	return energy - populationTotal;
}

NAMESPACE_LOGIC_E
