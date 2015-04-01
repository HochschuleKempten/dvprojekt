#include "LCoalPowerPlant.h"

LCoalPowerPlant::LCoalPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
	: ILPowerPlant(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createCoalPowerPlant(this))
{
	vPowerPlant->initPowerPlant(x, y);
}

LCoalPowerPlant::~LCoalPowerPlant()
{
}
