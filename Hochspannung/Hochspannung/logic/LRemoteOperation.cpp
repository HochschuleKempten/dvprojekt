#include "LRemoteOperation.h"
#include "ILPowerPlant.h"

NAMESPACE_LOGIC_B

std::deque<std::function<void()>> LRemoteOperation::storedNetworkCalls;

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField): lPlayingField(lPlayingField)
{
	lPlayingField->beginRemoteOperation();
}

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField, ILPowerPlant* lPowerPlant)
	: lPlayingField(lPlayingField), lPowerPlant(lPowerPlant)
{
	lPlayingField->beginRemoteOperation();
}

LRemoteOperation::LRemoteOperation(LPlayingField* lPlayingField, LPlayer* lPlayer)
	: lPlayingField(lPlayingField), lPlayer(lPlayer)
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

	if (!lPlayingField->isInitDone())
	{
		storedNetworkCalls.push_back(std::bind(&ILPowerPlant::switchOn, lPowerPlant));
	}
	else
	{
		lPowerPlant->switchOn();
	}
}

void LRemoteOperation::switchOff()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);

	if (!lPlayingField->isInitDone())
	{
		storedNetworkCalls.push_back(std::bind(&ILPowerPlant::switchOff, lPowerPlant));
	}
	else
	{
		lPowerPlant->switchOff();
	}
}

void LRemoteOperation::sabotagePowerPlantEnd()
{
	ASSERT(lPowerPlant != nullptr, msglPowerPlantNotInitialized);
	lPowerPlant->sabotagePowerPlantEnd();
}

bool LRemoteOperation::sabotageRemove(ILBuilding* lBuilding)
{
	ASSERT(lPlayer != nullptr, "lPlayer is not initialized");
	return lPlayer->sabotageRemove(lBuilding);
}

bool LRemoteOperation::sabotageDeactivate(ILPowerPlant* lPowerPlant)
{
	ASSERT(lPlayer != nullptr, "lPlayer is not initialized");
	return lPlayer->sabotageDeactivate(lPowerPlant);
}

bool LRemoteOperation::sabotageRessource(ILPowerPlant* lPowerPlant)
{
	ASSERT(lPlayer != nullptr, "lPlayer is not initialized");
	return lPlayer->sabotageRessource(lPowerPlant);
}

void LRemoteOperation::sendStoredNetworkCalls()
{
	for (auto call : storedNetworkCalls)
	{
		call();
	}

	storedNetworkCalls.clear();
}

NAMESPACE_LOGIC_E
