#pragma once

#include "VGeneral.h"
#include "IViewBuilding.h"
#include "../logic/IVPowerPlant.h"
#include "VSoundLoader.h"

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
			case action::switchOnOff: lPlant->switchOnOff(); return true; //TODO inform enemy
				if (lPlant->getLField()->getLPlayingField()->getLMaster()->getPlayer(LPlayer::PlayerId::Local)->trySabotageAct())
				{
				case action::sabotagePowerPlant: lPlant->sabotage(); return true; //TODO inform enemy
				case action::sabotageResourceField: lPlant->sabotageResource(); return true;//TODO inform enemy
				}
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
