#include "LSolarPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LSolarPowerPlant::LSolarPowerPlant(LField* lField, const int x, const int y)
	:ILPowerPlant(lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createSolarPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LSolarPowerPlant::~LSolarPowerPlant()
{
}

NAMESPACE_LOGIC_E