#include "LNuclearPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

LNuclearPowerPlant::LNuclearPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createNuclearPowerPlant(this))//TODO (V) fill with concrete View Object
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LNuclearPowerPlant::~LNuclearPowerPlant()
{
}
