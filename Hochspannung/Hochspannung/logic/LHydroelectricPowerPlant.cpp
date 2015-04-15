#include "LHydroelectricPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LHydroelectricPowerPlant::LHydroelectricPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createHydroelectricPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LHydroelectricPowerPlant::~LHydroelectricPowerPlant()
{
}

int LHydroelectricPowerPlant::getID()
{
	return id;
}

NAMESPACE_LOGIC_E