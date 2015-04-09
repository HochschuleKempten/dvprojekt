#include "VFactory.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"

NAMESPACE_VIEW_B


IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(vMaster, field);
}

IVPowerPlant* VFactory::createCoalPowerPlant(LCoalPowerPlant* powerPlant)
{
	return new VCoalPowerPlant(vMaster, powerPlant);
}

IVPowerPlant* VFactory::createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant)
{
	return new VHydroelectricPowerPlant(vMaster, powerPlant);
}

NAMESPACE_VIEW_E
