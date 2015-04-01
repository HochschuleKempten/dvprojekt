#include "LHydroelectricPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LHydroelectricPowerPlant::LHydroelectricPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createHydroelectricPowerPlant(this))//TODO (V) fill with concrete View Object
{
	vPowerPlant->initPowerPlant(x, y);
}


LHydroelectricPowerPlant::~LHydroelectricPowerPlant()
{
}
