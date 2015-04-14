#include "LOilRefinery.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LOilRefinery::LOilRefinery(const int costs, const int energyValue, LField* lField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createOilRefinery(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LOilRefinery::~LOilRefinery()
{
}

int LOilRefinery::getID()
{
	return id;
}