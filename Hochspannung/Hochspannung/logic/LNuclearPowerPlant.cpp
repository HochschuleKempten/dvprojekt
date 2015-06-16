#include "LNuclearPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LNuclearPowerPlant::LNuclearPowerPlant(LField* lField, const int x, const int y, const int playerId)
	:ILPowerPlant(lField, playerId, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createNuclearPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}

int LNuclearPowerPlant::getEnergyValue()
{
	return fossilResourceCheck();
}

LNuclearPowerPlant::~LNuclearPowerPlant()
{
}

NAMESPACE_LOGIC_E