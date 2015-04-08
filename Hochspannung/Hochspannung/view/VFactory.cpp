#include "VFactory.h"
#include "VPlayingField.h"
#include "VCoalPowerPlant.h"
#include "VHydroelectricPowerPlant.h"
#include "VNuclearPowerPlant.h"
#include "VOilRefinery.h"
#include "VSolarPowerPlant.h"
#include "VWindmillPowerPlant.h"
#include "VPowerline.h"
#include "VUI.h"

NAMESPACE_VIEW_B


IVPlayingField* VFactory::createPlayingField(LPlayingField* field)
{
	return new VPlayingField(vMaster, field);
}

std::shared_ptr<IVPowerPlant> VFactory::createCoalPowerPlant(LCoalPowerPlant* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VCoalPowerPlant(vMaster, powerPlant));
}

std::shared_ptr<IVPowerPlant>VFactory::createHydroelectricPowerPlant(LHydroelectricPowerPlant* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VHydroelectricPowerPlant(vMaster, powerPlant));
}

std::shared_ptr<IVPowerPlant> VFactory::createNuclearPowerPlant(LNuclearPowerPlant* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VNuclearPowerPlant(vMaster, powerPlant));
}

std::shared_ptr<IVPowerPlant> VFactory::createOilRefinery(LOilRefinery* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VOilRefinery(vMaster, powerPlant));
}

std::shared_ptr<IVPowerPlant> VFactory::createSolarPowerPlant(LSolarPowerPlant* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VSolarPowerPlant(vMaster, powerPlant));
}

std::shared_ptr<IVPowerPlant> VFactory::createWindmillPowerPlant(LWindmillPowerPlant* powerPlant)
{
	return std::shared_ptr<IVPowerPlant>(new VWindmillPowerPlant(vMaster, powerPlant));
}

IVPowerLine* VFactory::createPowerLine(LPowerLine* powerLine)
{
	return new VPowerLine(vMaster, powerLine);
}

IVUI* VFactory::createUi(LUI* lUi)
{
	return new VUI(vMaster, lUi);
}


NAMESPACE_VIEW_E
