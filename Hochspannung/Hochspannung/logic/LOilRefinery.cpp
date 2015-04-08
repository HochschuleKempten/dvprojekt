#include "LOilRefinery.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LOilRefinery::LOilRefinery(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
:ILPowerPlant(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createOilRefinery(this))//TODO (V) fill with concrete View Object
{
}


LOilRefinery::~LOilRefinery()
{
}
