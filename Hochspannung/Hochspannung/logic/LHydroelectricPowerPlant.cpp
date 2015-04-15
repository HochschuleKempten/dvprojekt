#include "LHydroelectricPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LHydroelectricPowerPlant::LHydroelectricPowerPlant(LField* lField, const int x, const int y)
	:ILPowerPlant(lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createHydroelectricPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LHydroelectricPowerPlant::~LHydroelectricPowerPlant()
{
}

NAMESPACE_LOGIC_E