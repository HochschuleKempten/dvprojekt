#include "LNuclearPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LNuclearPowerPlant::LNuclearPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
:ILPowerPlant(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createNuclearPowerPlant(this))//TODO (V) fill with concrete View Object
{
}


LNuclearPowerPlant::~LNuclearPowerPlant()
{
}
