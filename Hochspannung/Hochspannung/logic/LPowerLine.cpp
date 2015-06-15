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

void LPowerLine::addDirection(const int direction)
{
	int newOrientation = this->orientation | direction;

	if (this->orientation != newOrientation) {
		vPowerLine->orientationChanged(newOrientation);
		this->orientation = newOrientation;
	}
}

void LPowerLine::removeDirection(const int direction)
{
	if ((this->orientation & direction) > 0)	//Remove only an orientation which exists
	{
		int newOrientation = this->orientation ^ direction;

		if (this->orientation != newOrientation)
		{
			vPowerLine->orientationChanged(newOrientation);
			this->orientation = newOrientation;
		}
	}
}

NAMESPACE_LOGIC_E
