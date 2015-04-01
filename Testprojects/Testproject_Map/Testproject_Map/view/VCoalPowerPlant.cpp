#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


void VCoalPowerPlant::initPowerPlant(const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(x, y);

	//Todo (V) create PP visual

}


NAMESPACE_VIEW_E
