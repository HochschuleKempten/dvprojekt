#include "LCoalPowerPlant.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"
#include "LPlayingField.h"

NAMESPACE_LOGIC_B

LCoalPowerPlant::LCoalPowerPlant(LField* lField, const int x, const int y, const int playerId)
	: ILPowerPlant(lField, playerId, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createCoalPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}

int LCoalPowerPlant::getEnergyValue()
{
	return fossilRessourceCheck();
}

LCoalPowerPlant::~LCoalPowerPlant()
{
}

NAMESPACE_LOGIC_E