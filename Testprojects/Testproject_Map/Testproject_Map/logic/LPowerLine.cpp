#include "LPowerLine.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerLine.h"


LPowerLine::LPowerLine(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
:LPowerLine(costs, energyValue, lPlayingField, x, y, lPlayingField->getLMaster()->getVMaster()->getFactory()->createHydroelectricPowerPlant(this))
{
	vPowerLine->initPowerLine(x, y);
}

LPowerLine::~LPowerLine()
{
}
