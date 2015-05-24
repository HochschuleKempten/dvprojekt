#pragma once

#include "VGeneral.h"
#include "IViewBuilding.h"
#include "../logic/IVPowerPlant.h"
#include "VSoundLoader.h"
#include "../logic/LRemoteOperation.h"
#include "../logic/LSabotage.h"

NAMESPACE_VIEW_B


class IViewPowerPlant : public IVPowerPlant, public IViewBuilding
{
protected:
	bool isOn = true;

public:
	inline IViewPowerPlant(ILPowerPlant* lPlant, VMaster* vMaster, CPlacement* m_zp)
		: IVPowerPlant(lPlant), IViewBuilding(vMaster, m_zp)
	{}
	inline virtual ~IViewPowerPlant() override
	{}

	inline virtual ILBuilding* getLBuilding() override
	{
		return CASTD<ILBuilding*>(lPlant);
	}

	virtual bool clicked(action action) override
	{			
		switch (action)
		{
			case action::switchOnOff:
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				if (isOn)
				{
					remoteOperation.switchOff();
				}
				else
				{
					remoteOperation.switchOn();
				}

				return true;
			}
			case action::sabotagePowerPlant: 
				if (lPlant->getLField()->getLPlayingField()->getLMaster()->getPlayer(LPlayer::PlayerId::Local)->trySabotageAct(LSabotage::PowerPlant))
				{
					LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
					remoteOperation.sabotage();
					return true; 
				} 

				return false;

			case action::sabotageResourceField: 
				if (lPlant->getLField()->getLPlayingField()->getLMaster()->getPlayer(LPlayer::PlayerId::Local)->trySabotageAct(LSabotage::Resource))
				{
					LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
					remoteOperation.sabotageResource();

					return true;
				}

				return false;

			default:ASSERT("Invalid action"); return false;
		}				
	}

	virtual void switchedOn() override
	{
		isOn = true;
		VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_ON, getPlacement());
	}

	virtual void switchedOff() override
	{
		isOn = false;
		VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_OFF, getPlacement());
	}

	virtual void sabotageRessourcesReduced() override
	{
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
	}

	virtual void sabotagePowerPlantSwitchedOff() override
	{
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
	}
};


NAMESPACE_VIEW_E
