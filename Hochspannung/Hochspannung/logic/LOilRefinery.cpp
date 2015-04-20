#include "LOilRefinery.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LOilRefinery::LOilRefinery(LField* lField, const int x, const int y)
	:ILPowerPlant(lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createOilRefinery(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LOilRefinery::~LOilRefinery()
{
}

NAMESPACE_LOGIC_E