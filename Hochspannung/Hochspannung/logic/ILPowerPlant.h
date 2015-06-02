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
			DEBUG_OUTPUT("Powerplant ON");

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
			DEBUG_OUTPUT("Powerplant OFF");

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

	//TODO (V) make rest bools also

	bool sabotagePowerPlant()
	{
		if (this->getLField()->getLPlayingField()->getLMaster()->getPlayer(LPlayer::PlayerId::Local)->trySabotageAct(LSabotage::PowerPlant))
		{
			switchOff();
			isSabotaged = true;

			//if (playerId == LPlayer::Local)	//TODO (L) just for testing
			//{
				vPowerPlant->sabotagePowerPlantSwitchedOff(LBalanceLoader::getCooldownTimeReactivationPowerPlant());
			//}
			//TODO (L) inform UI

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::PowerPlant, coordinates.first, coordinates.second);
			}

			return true;
		}

		return false;
	}

	bool sabotageResource()
	{
		if (this->getLField()->getLPlayingField()->getLMaster()->getPlayer(LPlayer::PlayerId::Local)->trySabotageAct(LSabotage::PowerPlant))
		{
			DEBUG_OUTPUT("Try to sabotage ressource field. Old ressource value: " << getLField()->getResources());
			int newValue = this->getLField()->deductResources();
			DEBUG_OUTPUT("Resource sabotated, new Value:  " << newValue);

			if (!lField->getLPlayingField()->isLocalOperation())
			{
				std::pair<int, int> coordinates = lField->getCoordinates();
				lField->getLPlayingField()->getLMaster()->sendSabotage(LSabotage::Resource, coordinates.first, coordinates.second);
			}
			return true;
		}
		return false;
	}

protected:
	std::shared_ptr<IVPowerPlant> vPowerPlant;
	bool isActivated = false;
	bool isSabotaged = false;
	DEBUG_EXPRESSION(bool lastRessourcesUsed = false);

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
			if (timeLastCheck > LBalanceLoader::getCooldownTimeReactivationPowerPlant())
			{
				isSabotaged = false;
				vPowerPlant->sabotagePowerPlantSwitchedOn(); 

				LRemoteOperation remoteOperation(lField->getLPlayingField(), this);
				remoteOperation.switchOn();
				timeLastCheck = 0;

				//TODO (L) inform UI
				DEBUG_OUTPUT("Your powerplant is reactivated after the sabotage act");
			}

			timeLastCheck += fTimeDelta;
		}
	};

	int fossilRessourceCheck()
	{
		const int consumedRessources = LBalanceLoader::getConsumedResources(LField::NUCLEAR);
		const int amountReduced = lField->reduceResources(consumedRessources);

		if (amountReduced < consumedRessources)
		{
			ASSERT(!lastRessourcesUsed, "Last ressources of field are used twice");
			DEBUG_EXPRESSION(lastRessourcesUsed = true);

			//No more ressources are left, so switch the power plant off
			LRemoteOperation remoteOperation(lField->getLPlayingField(), this);
			remoteOperation.switchOff();

			//Last step returns proportionally ressources
			return LBalanceLoader::getProducedEnergy(this->getIdentifier()) * amountReduced / consumedRessources;
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
};


NAMESPACE_LOGIC_E
