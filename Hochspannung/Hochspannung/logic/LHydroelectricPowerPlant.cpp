#include "LHydroelectricPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LHydroelectricPowerPlant::LHydroelectricPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createHydroelectricPowerPlant(this))
{
	vPowerPlant->initPowerPlant(x, y);
}


LHydroelectricPowerPlant::~LHydroelectricPowerPlant()
{
}
