#include "LWindmillPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LWindmillPowerPlant::LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	: ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createWindmillPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LWindmillPowerPlant::~LWindmillPowerPlant()
{
}

NAMESPACE_LOGIC_E