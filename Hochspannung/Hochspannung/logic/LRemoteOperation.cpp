#include "LRemoteOperation.h"
#include "ILPowerPlant.h"
#include "LPowerLine.h"

NAMESPACE_LOGIC_B

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField): lPlayingField(lPlayingField)
{
	lPlayingField->beginRemoteOperation();
}

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField, ILPowerPlant* lPowerPlant): lPlayingField(lPlayingField), lPowerPlant(lPowerPlant)
{
	lPlayingField->beginRemoteOperation();
}

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField, LPowerLine* lPowerLine): lPlayingField(lPlayingField), lPowerLine(lPowerLine)
{
	lPlayingField->beginRemoteOperation();
}

LRemoteOperation::~LRemoteOperation()
{
	lPlayingField->endRemoteOperation();
}

bool LRemoteOperation::removeBuilding(const int x, const int y)
{
	return lPlayingField->removeBuilding(x, y);
}

void LRemoteOperation::upgradeBuilding(const int x, const int y)
{
	lPlayingField->upgradeBuilding(x, y);
}

void LRemoteOperation::switchOn()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);
	lPowerPlant->switchOn();
}

void LRemoteOperation::switchOff()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);
	lPowerPlant->switchOff();
}

bool LRemoteOperation::sabotagePowerPlant()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);
	return lPowerPlant->sabotagePowerPlant();
}

bool LRemoteOperation::sabotageResource()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);
	return lPowerPlant->sabotageResource();
}

bool LRemoteOperation::sabotagePowerLine()
{
	ASSERT(lPowerLine != nullptr, "lPowerLine is not initialized. Make sure you pass a valid pointer to LPowerLine in the constructor");
    return lPowerLine->sabotagePowerLine();
}

NAMESPACE_LOGIC_E
