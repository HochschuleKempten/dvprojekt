#pragma once

#include "ILBuilding.h"
#include "LField.h"
#include "LPlayingField.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVPowerPlant.h"
#include "LRemoteOperation.h"

NAMESPACE_LOGIC_B


class LRemoteOperation;
class LPlayer;

class ILPowerPlant : public ILBuilding, public IVTickObserver
{
	friend class LRemoteOperation;
	friend class LMaster;
	friend class LPlayer;

private:
	float timeLastCheck = 0;

private:
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

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendPowerPlantSwitchState(coordinates.first, coordinates.second, isActivated);
			}

			if (playerId == LPlayer::Local)
			{
				lField->getLPlayingField()->recalculateCityConnections();
			}
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

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendPowerPlantSwitchState(coordinates.first, coordinates.second, isActivated);
			}

			if (playerId == LPlayer::Local)
			{
				lField->getLPlayingField()->recalculateCityConnections();
			}
		}
	}

	bool sabotageDeactivate()
	{
		if (!isSabotagePossible() && !lField->getLPlayingField()->isLocalOperation())
		{
			return false;
		}

		switchOff();
		vPowerPlant->sabotagePowerPlantSwitchedOff(LBalanceLoader::getSabotageCooldown(LSabotage::Deactivate));
		isSabotaged = true;

		if (!lField->getLPlayingField()->isLocalOperation())
		{
			std::pair<int, int> coordinates = lField->getCoordinates();
			lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::Deactivate, coordinates.first, coordinates.second);
		}
		else
		{
			LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_DEACTIVATE);
		}

		return true;
	}

	void sabotageDeactivateEnd()
	{
		if (isSabotaged)
		{
			isSabotaged = false;
			vPowerPlant->sabotagePowerPlantSwitchedOn();

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendPowerPlantSabotageEnd(coordinates.first, coordinates.second);
				LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_DEACTIVATE_OVER);
			}
		}
	}

	bool sabotageResource()
	{
		if (!isSabotagePossible() && !lField->getLPlayingField()->isLocalOperation())
		{
			return false;
		}

		DEBUG_OUTPUT("Try to sabotage resource field. Old resource value: " << getLField()->getResources());
		int newValue = this->getLField()->deductResources();
		vPowerPlant->updateResourceValue(newValue);
		DEBUG_OUTPUT("Resource sabotated, new Value:  " << newValue);

		if (!lField->getLPlayingField()->isLocalOperation())
		{
			std::pair<int, int> coordinates = lField->getCoordinates();
			lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::Resource, coordinates.first, coordinates.second);
		} 
		else
		{
			LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_RESOURCE);
		}

		return true;
	}

	bool isSabotagePossible()
	{
		if (isSabotaged)
		{
			LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_ALREADY_SABOTAGED);
			return false;
		}

		if (!isActivated)
		{
			LMessageLoader::emitMessage(LMessageLoader::SABOTAGE_NOT_ACTIVATED);
			return false;
		}

		return true;
	}

protected:
	std::shared_ptr<IVPowerPlant> vPowerPlant;
	bool isActivated = false;
	bool isSabotaged = false;
	DEBUG_EXPRESSION(bool lastResourcesUsed = false);

public:
	inline ILPowerPlant(LField* lField, const int playerId, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(lField, playerId),
		vPowerPlant(vPowerPlant)
	{
		lField->getLPlayingField()->getLMaster()->getVMaster()->registerObserver(this);
	}

	inline virtual ~ILPowerPlant()
	{
		lField->getLPlayingField()->getLMaster()->getVMaster()->unregisterObserver(this);
	}

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
			if (timeLastCheck > LBalanceLoader::getSabotageCooldown(LSabotage::Deactivate))
			{
				LRemoteOperation remoteOperation(lField->getLPlayingField(), this);
				remoteOperation.sabotagePowerPlantEnd();
				remoteOperation.switchOn();
				timeLastCheck = 0;
			}

			timeLastCheck += fTimeDelta;
		}
	};

	int fossilResourceCheck()
	{
		const int consumedResources = LBalanceLoader::getConsumedResources(getLField()->getFieldType());
		const int amountReduced = lField->reduceResources(consumedResources);
		vPowerPlant->updateResourceValue(lField->getResources());

		if (amountReduced < 0)
		{
			return 0;
		}

		if (amountReduced < consumedResources)
		{
			ASSERT(!lastResourcesUsed, "Last resources of field are used twice");
			DEBUG_EXPRESSION(lastResourcesUsed = true);

			//No more resources are left, so switch the power plant off
			LRemoteOperation remoteOperation(lField->getLPlayingField(), this);
			remoteOperation.switchOff();

			//Last step returns proportionally resources
			return LBalanceLoader::getProducedEnergy(this->getIdentifier()) * amountReduced / consumedResources;
		}

		//Normal energy value was reduced
		return LBalanceLoader::getProducedEnergy(this->getIdentifier());
	}

	bool isRegenerative()
	{
		LIdentifier::LIdentifier identifier = this->getIdentifier();

		switch (identifier)
		{
			case(LIdentifier::LCoalPowerPlant) :
			case(LIdentifier::LNuclearPowerPlant) :
			case(LIdentifier::LOilRefinery) :
				return false;
			default:
				return true;
		}
	}

	virtual void setConnected(bool connected) override
	{
		ILBuilding::setConnected(connected);
		vPowerPlant->updateValue(getValue());
	}

	virtual bool checkSell() const override
	{
		if (isSabotaged)
		{
			LMessageLoader::emitMessage(LMessageLoader::SELL_CHECK_IS_SABOTAGED);
			return false;
		}

		return true;
	}

	virtual bool sabotageRemove() override
	{
		if (!isSabotagePossible())
		{
			return false;
		}

		return ILBuilding::sabotageRemove();
	}
};


NAMESPACE_LOGIC_E
