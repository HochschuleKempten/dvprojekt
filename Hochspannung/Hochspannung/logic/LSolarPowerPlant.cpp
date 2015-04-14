#include "LSolarPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LSolarPowerPlant::LSolarPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createSolarPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LSolarPowerPlant::~LSolarPowerPlant()
{
}

int LSolarPowerPlant::getID()
{
	return id;
}