#include "LWindmillPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LWindmillPowerPlant::LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	: ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createWindmillPowerPlant(this))
{
	vPowerPlant->initPowerPlant(x, y);
}


LWindmillPowerPlant::~LWindmillPowerPlant()
{
}
