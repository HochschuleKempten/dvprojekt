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
	//todo (V) check which concrete object is passed in and create the corresponding counterpart
	return new VPowerPlant(vMaster, powerPlant);
}


NAMESPACE_VIEW_E
