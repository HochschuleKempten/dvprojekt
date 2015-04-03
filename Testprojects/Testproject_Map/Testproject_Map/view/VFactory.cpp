#include "VFactory.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VNuclearPowerPlant.h"
#include "VOilRefinery.h"
#include "VSolarPowerPlant.h"
#include "VWindmillPowerPlant.h"
#include "VUI.h"

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

IVPowerPlant* VFactory::createNuclearPowerPlant(LNuclearPowerPlant* powerPlant)
{
	return new VNuclearPowerPlant(vMaster, powerPlant);
}

IVPowerPlant* VFactory::createOilRefinery(LOilRefinery* powerPlant)
{
	return new VOilRefinery(vMaster, powerPlant);
}

IVPowerPlant* VFactory::createSolarPowerPlant(LSolarPowerPlant* powerPlant)
{
	return new VSolarPowerPlant(vMaster, powerPlant);
}

IVPowerPlant* VFactory::createWindmillPowerPlant(LWindmillPowerPlant* powerPlant)
{
	return new VWindmillPowerPlant(vMaster, powerPlant);
}

IVUI* VFactory::createUi(LUI* lUi)
{
	return new VUI(vMaster, lUi);
}


NAMESPACE_VIEW_E
