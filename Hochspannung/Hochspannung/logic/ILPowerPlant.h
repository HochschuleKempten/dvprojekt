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
	bool isActivated = false;
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

	virtual int getEnergyValue()
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
			
			if (timeLastCheck > LBalanceLoader::getCooldownTimeReactivationPowerPlant())
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
		
	void switchOn()
	{
		if (isActivated)
		{
			return;
		}

		if (!isSabotaged)
		{
			isActivated = true;
			vPowerPlant->switchedOn();
			DEBUG_OUTPUT("Powerplant ON");

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendPowerPlantSwitchState(coordinates.first, coordinates.second, isActivated);
			}

			lField->getLPlayingField()->recalculateCityConnections();
		}
	}

	void switchOff()
	{
		if (!isActivated)
		{
			return;
		}

		if (!isSabotaged)
		{
			isActivated = false;
			vPowerPlant->switchedOff();
			DEBUG_OUTPUT("Powerplant OFF");

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendPowerPlantSwitchState(coordinates.first, coordinates.second, isActivated);
			}

			lField->getLPlayingField()->recalculateCityConnections();
		}
	}

	void switchOnOff()
	{
		//TODO (L) remove
		if (isActivated) {
			switchOff();
		}
		else {
			switchOn();
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
			lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::LSabotage::PowerPlant, coordinates.first, coordinates.second);
		}
	}

	void sabotageResource()
	{
		int newValue = this->getLField()->deductResources();
		DEBUG_OUTPUT("Resource sabotated, new Value:  " << newValue);

		if (!lField->getLPlayingField()->isLocalOperation())
		{
			std::pair<int, int> coordinates = lField->getCoordinates();
			lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::LSabotage::Resource, coordinates.first, coordinates.second);
		}
	}
};


NAMESPACE_LOGIC_E
