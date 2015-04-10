#include "LPowerLine.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerLine.h"


LPowerLine::LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y, PowerLineOrientation orientation)
	:ILPowerLine(costs, energyValue, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createPowerLine(this)),
	orientation(orientation)
{
	vPowerLine->initPowerLine(vPowerLine, x, y);
}

LPowerLine::~LPowerLine()
{
}
