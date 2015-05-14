#pragma once

#include "VGeneral.h"
#include "IViewBuilding.h"
#include "../logic/IVPowerPlant.h"

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
			case action::sabotagePowerPlant: lPlant->sabotage(); return true; //TODO inform enemy
			case action::sabotageResourceField: lPlant->sabotageResource(); return true;//TODO inform enemy
				
			default:ASSERT("Invalid action"); return false;
		}
	}

	virtual void switchedOn() override
	{
		isOn = true;
	}

	virtual void switchedOff() override
	{
		isOn = false;
	}
};


NAMESPACE_VIEW_E
