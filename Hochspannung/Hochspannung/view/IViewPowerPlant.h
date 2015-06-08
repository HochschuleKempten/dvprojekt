#pragma once

#include "VGeneral.h"
#include "IViewBuilding.h"
#include "IViewModel.h"
#include "../logic/IVPowerPlant.h"
#include "VSoundLoader.h"
#include "../logic/LRemoteOperation.h"

NAMESPACE_VIEW_B


class IViewPowerPlant : public IVPowerPlant, public IViewBuilding
{
protected:
	bool isOn = false;
	CGeoQuad quadForAnimation;
	CPlacement placementForAnimation;
	CMaterial animationMaterial = VMaterialLoader::materialAnimSabotagePowerPlant;
	IViewModel* ptrViewModel;

public:
	inline IViewPowerPlant(ILPowerPlant* lPlant, VMaster* vMaster, CPlacement* m_zp, IViewModel* ptrViewModel)
		: IVPowerPlant(lPlant), IViewBuilding(vMaster, m_zp), ptrViewModel(ptrViewModel)
	{
		quadForAnimation.Init(2, 2, &animationMaterial);
		placementForAnimation.AddGeo(&quadForAnimation);
		placementForAnimation.TranslateY(4.0);
		animationMaterial.SwitchOff();
	}

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
			case action::switchOn:
			{
				if (isOn)
				{
					return false;
				}

				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				remoteOperation.switchOn();
				return true;
			}
			case action::switchOff:
			{
				if (!isOn)
				{
					return false;
				}

				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				remoteOperation.switchOff();
				return true;
			}
			case action::sabotagePowerPlant:
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				return remoteOperation.sabotagePowerPlant();
			}

			case action::sabotageResourceField: 
			{
					LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
			     	return remoteOperation.sabotageResource();
			}			

			default:ASSERT("Invalid action"); return false;
		}
	}

	virtual void switchedOn() override
	{
		isOn = true;
		ptrViewModel->switchOn();

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone())
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_ON, getPlacement());
		}
	}

	virtual void switchedOff() override
	{
		isOn = false;
		ptrViewModel->switchOff();

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone())
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_OFF, getPlacement());
		}
	}

	virtual void sabotageRessourcesReduced() override
	{
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
	}

	virtual void sabotagePowerPlantSwitchedOff(const int seconds) override
	{	
		animationMaterial.SwitchOn();
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 CASTS<float>(VMaterialLoader::materialAnimSabotagePowerPlant_x * VMaterialLoader::materialAnimSabotagePowerPlant_y) / CASTS<float>(seconds));
		getPlacement()->AddPlacement(&placementForAnimation);
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
	}

	virtual void sabotagePowerPlantSwitchedOn() override
	{
		animationMaterial.SwitchOff();
		getPlacement()->SubPlacement(&placementForAnimation);
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 0.0f);
	}
};


NAMESPACE_VIEW_E
