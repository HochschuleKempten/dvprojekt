#include "LWindmillPowerPlant.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B

LWindmillPowerPlant::LWindmillPowerPlant(LField* lField, const int x, const int y, const int playerId)
	: ILPowerPlant(lField, playerId, lField->getLPlayingField()->getLMaster()->getVMaster()->getFactory()->createWindmillPowerPlant(this))
{
	vPowerPlant->initPowerPlant(vPowerPlant, x, y);
}


LWindmillPowerPlant::~LWindmillPowerPlant()
{
}

NAMESPACE_LOGIC_E