#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


void VCoalPowerPlant::initPowerPlant(const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(this, x, y);
}


NAMESPACE_VIEW_E
