#include "LPowerLine.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerLine.h"

NAMESPACE_LOGIC_B


LPowerLine::LPowerLine(LField* lField, const int x, const int y, const int orientation)
	: ILPowerLine(orientation, lField, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createPowerLine(this)),
	orientation(orientation)
{
	vPowerLine->initPowerLine(vPowerLine, x, y, orientation);
}

LPowerLine::~LPowerLine()
{
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
