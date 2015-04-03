#include "LSolarPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LSolarPowerPlant::LSolarPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
:ILPowerPlant(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createSolarPowerPlant(this))
{
}


LSolarPowerPlant::~LSolarPowerPlant()
{
}
