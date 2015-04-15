#include "LPowerLine.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerLine.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B


LPowerLine::LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y, const int orientation)
	: ILPowerLine(costs, energyValue, orientation, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createPowerLine(this))
{
	vPowerLine->initPowerLine(vPowerLine, x, y);
}

LPowerLine::~LPowerLine()
{
}

int LPowerLine::getID()
{
	return id;
}

NAMESPACE_LOGIC_E