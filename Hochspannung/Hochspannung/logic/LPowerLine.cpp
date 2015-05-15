#include "LPowerLine.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerLine.h"

NAMESPACE_LOGIC_B


LPowerLine::LPowerLine(LField* lField, const int x, const int y, const int orientation, const int playerId)
	: ILBuilding(lField, playerId, orientation), vPowerLine(lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createPowerLine(this))
{
	vPowerLine->initPowerLine(vPowerLine, x, y, orientation);
}

LPowerLine::~LPowerLine()
{
}

bool LPowerLine::sabotage()
{
	//TODO (L) inform enemy over network
	return true;
}

void LPowerLine::updatedOrientation(const int additionalOrientation)
{
	int newOrientation = this->orientation | additionalOrientation;

	if (this->orientation != newOrientation) {
		vPowerLine->orientationChanged(newOrientation);
		this->orientation = newOrientation;
	}
}


NAMESPACE_LOGIC_E
