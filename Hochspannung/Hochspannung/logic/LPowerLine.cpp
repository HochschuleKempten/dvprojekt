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
	//todo (L) what should happen here?
	if (!lField->getLPlayingField()->isLocalOperation())
	{
		std::pair<int, int> coordinates = lField->getCoordinates();
		lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::LSabotage::PowerLine, coordinates.first, coordinates.second);
	}
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
