#include "LOilRefinery.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LOilRefinery::LOilRefinery(LField* lField, const int x, const int y, const int playerId)
	:ILPowerPlant(lField, playerId, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createOilRefinery(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}

int LOilRefinery::getEnergyValue() {
	// TODO (BP) what if there are less resources than reduced by tick? 
	if (lField->getResources() > 0 && !lField->reduceRecources(LBalanceLoader::getConsumedResources(LField::NUCLEAR))) {
		switchOnOff();
	}

	return ILPowerPlant::getEnergyValue();
}

LOilRefinery::~LOilRefinery()
{
}

NAMESPACE_LOGIC_E