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
	bool isOn = false;
	CGeoQuad quadForAnimation;
	CPlacement placementForAnimation;
	CMaterial animationMaterial = VMaterialLoader::materialAnimSabotagePowerPlant;

public:
	inline IViewPowerPlant(ILPowerPlant* lPlant, VMaster* vMaster, CPlacement* m_zp)
		: IVPowerPlant(lPlant), IViewBuilding(vMaster, m_zp)
	{
		this->quadForAnimation.Init(2, 2, &animationMaterial);
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
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				return remoteOperation.sabotagePowerPlant();
				//TODO (V)Change other cases according to this one	
			}

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
