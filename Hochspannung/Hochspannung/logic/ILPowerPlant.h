#pragma once

#include "ILBuilding.h"
#include "LField.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVPowerPlant.h"
#include "LRemoteOperation.h"

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

		return 0;	
	}

	virtual void tick(const float fTimeDelta) override
	{
		if (isSabotaged && this->getPlayerId() == LPlayer::Local)
		{
			static float timeLastCheck = 0;
			
			if (timeLastCheck > 3) //TODO (V) set back to 5 mins
			{
				isSabotaged = false;
				LRemoteOperation remoteOperation(lField->getLPlayingField());
				this->switchOnOff();
				timeLastCheck = 0;
				DEBUG_OUTPUT("Your powerplant is reactivated after the sabotage act");
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
				DEBUG_OUTPUT("Powerplant OFF");
			}
			else
			{
				isActivated = true;
				vPowerPlant->switchedOn();
				DEBUG_OUTPUT("Powerplant ON");
			}

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendSetObject(300, coordinates.first, coordinates.second, std::to_string(-1));
			}

			lField->getLPlayingField()->recalculateCityConnections();
		}
	}

	void sabotage()
	{
		isSabotaged = true;
		isActivated = false;
		vPowerPlant->switchedOff();
		DEBUG_OUTPUT("Powerplant sabotated, it's deactivated for 5 mins");

		if (!lField->getLPlayingField()->isLocalOperation())
		{
			std::pair<int, int> coordinates = lField->getCoordinates();
			lField->getLPlayingField()->getLMaster()->sendSetObject(400, coordinates.first, coordinates.second, std::to_string(-1));
		}
	}

	void sabotageResource()
	{
		int newValue = this->getLField()->deductResources(2);
		DEBUG_OUTPUT("Resource sabotated, new Value:  " << newValue);

		if (!lField->getLPlayingField()->isLocalOperation())
		{
			std::pair<int, int> coordinates = lField->getCoordinates();
			lField->getLPlayingField()->getLMaster()->sendSetObject(500, coordinates.first, coordinates.second, std::to_string(-1));

		}
	}
};


NAMESPACE_LOGIC_E
