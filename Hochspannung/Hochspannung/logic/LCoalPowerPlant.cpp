#include "LCoalPowerPlant.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"
#include "LPlayingField.h"

LCoalPowerPlant::LCoalPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	: ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createCoalPowerPlant(this))
{
	vPowerPlant->initPowerPlant(x, y);
}

LCoalPowerPlant::~LCoalPowerPlant()
{
}
