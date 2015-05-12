#pragma once

#include "ILBuilding.h"
#include "LField.h"
#include "LPlayingField.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B


class ILPowerPlant : public ILBuilding
{
protected:
	std::shared_ptr<IVPowerPlant> vPowerPlant;
	bool isActivated = true;

public:
	inline ILPowerPlant(LField* lField, const int playerId, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(lField, playerId),
		vPowerPlant(vPowerPlant)
	{};

	inline virtual ~ILPowerPlant()
	{
	};

	int virtual getEnergyValue()
	{
		if (isActivated)
		{
			return LBalanceLoader::getProducedEnergy(this->getIdentifier());
		}
		else
		{
			return 0;
		}
	}

	void switchOnOff()
	{
		if (isActivated)
		{
			isActivated = false;
			vPowerPlant->switchedOff();
		}
		else
		{
			isActivated = true;
			vPowerPlant->switchedOn();
		}

		lField->getLPlayingField()->calculateEnergyValueCity();
	};

};


NAMESPACE_LOGIC_E
