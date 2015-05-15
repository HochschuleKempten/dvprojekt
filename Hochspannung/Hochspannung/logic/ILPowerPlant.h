#pragma once

#include "ILBuilding.h"
#include "LField.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVPowerPlant.h"

NAMESPACE_LOGIC_B


class ILPowerPlant : public ILBuilding,  IVTickObserver
{
protected:
	std::shared_ptr<IVPowerPlant> vPowerPlant;
	bool isActivated = true;
	bool isSabotaged = false;

public:
	inline ILPowerPlant(LField* lField, const int playerId, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(lField, playerId),
		vPowerPlant(vPowerPlant)
	{
		lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
	}

	inline virtual ~ILPowerPlant()
	{}

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

	virtual void tick(const float fTimeDelta) override
	{
		if (isSabotaged)
		{
			static float timeLastCheck = 0;
			
			if (timeLastCheck > 3) //TODO (V) set back to 5 mins
			{
				isSabotaged = false;
				this->switchOnOff();
				timeLastCheck = 0;
				DEBUG_OUTPUT("Your Powerplant is reactivated after the sabotage Act");
			}

			timeLastCheck += fTimeDelta;
		}
 	};
		

	void switchOnOff()
	{
		if (!isSabotaged)
		{
			if (isActivated)
			{
				isActivated = false;
				vPowerPlant->switchedOff();
				DEBUG_OUTPUT("You Switched your Powerplant OFF");
				//TODO (L) inform enemy over network
			}
			else
			{
				isActivated = true;
				vPowerPlant->switchedOn();
				DEBUG_OUTPUT("You Switched your Powerplant ON");
				//TODO (L) inform enemy over network
			}

			lField->getLPlayingField()->recalculateCityConnections();
		}
	}

	void sabotage()
	{
		isSabotaged = true;
		isActivated = false;
		vPowerPlant->switchedOff();
		DEBUG_OUTPUT("You sabotated enemys Powerplant, its deactivated for 5 mins");
		//TODO (L) inform enemy over network
	}

	void sabotageResource()
	{
		int newValue = this->getLField()->deductResources(2);
		DEBUG_OUTPUT("You sabotated enemys Resources new Value:  " << newValue);
		//TODO (L) inform enemy over network
	}

};


NAMESPACE_LOGIC_E
