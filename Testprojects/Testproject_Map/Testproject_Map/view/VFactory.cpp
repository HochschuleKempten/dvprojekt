#include "VFactory.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"

NAMESPACE_VIEW_B


IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(vMaster, field);
}

IVPowerPlant* VFactory::createCoalPowerPlant(LCoalPowerPlant* powerPlant)
{
	return new VCoalPowerPlant(vMaster, powerPlant);
}


NAMESPACE_VIEW_E
