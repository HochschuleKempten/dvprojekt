#include "VFactory.h"
#include "VPlayingField.h"
#include "VPowerPlant.h"

NAMESPACE_VIEW_B


IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(vMaster, field);
}

IVPowerPlant* VFactory::createPowerPlant(ILPowerPlant* powerPlant)
{
	return new VPowerPlant(vMaster, powerPlant);
}


NAMESPACE_VIEW_E
