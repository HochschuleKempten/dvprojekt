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
private:
	CPlacement* getPlacementActive() const
	{
		if (isOn)
		{
			return viewModelOn->getPlacementMain();
		}
		else
		{
			return viewModelOff != nullptr ? viewModelOff->getPlacementMain() : nullptr;
		}
	}

protected:
	bool isOn = false;
	CGeoQuad quadForAnimation;
	CPlacement placementForAnimation;
	CMaterial animationMaterial = VMaterialLoader::materialAnimSabotagePowerPlant;
	IViewModel* viewModelOn = nullptr;
	IViewModel* viewModelOff = nullptr;
	const float moveZOff = 1337.42f;

protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) = 0;

	void translateViewModel()
	{
		ASSERT(viewModelOn != nullptr, "viewModelOn is not initialized");
		ASSERT(viewModelOff != nullptr, "viewModelOff is not initialized");

		if (isOn)
		{
			viewModelOff->getPlacementMain()->TranslateZDelta(-moveZOff);
		}
		else
		{
			viewModelOn->getPlacementMain()->TranslateZDelta(-moveZOff);
		}
	}

public:
	inline IViewPowerPlant(ILPowerPlant* lPlant, VMaster* vMaster, CPlacement* m_zp, IViewModel* viewModelOn, IViewModel* viewModelOff)
		: IVPowerPlant(lPlant), IViewBuilding(vMaster, m_zp), viewModelOn(viewModelOn), viewModelOff(viewModelOff)
	{
		quadForAnimation.Init(5, 5, &animationMaterial);
		placementForAnimation.AddGeo(&quadForAnimation);
		placementForAnimation.TranslateY(5.0f);
		placementForAnimation.TranslateZDelta(5.0f);
		placementForAnimation.RotateXDelta(PI / -4.0f);
		animationMaterial.SwitchOff();
	}

	inline virtual ~IViewPowerPlant() override
	{}

	inline CPlacement* getPlacementSecond() const override
	{
		ASSERT(viewModelOff != nullptr, "viewModelOff is not initialized");
		return viewModelOff->getPlacementMain();
	}

	inline virtual ILBuilding* getLBuilding() override
	{
		return CASTD<ILBuilding*>(lPlant);
	}

	virtual bool clicked(action action) override
	{
		switch (action)
		{
			case switchOn:
			{
				if (isOn)
				{
					return false;
				}

				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				remoteOperation.switchOn();
				return true;
			}
			case switchOff:
			{
				if (!isOn)
				{
					return false;
				}

				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), lPlant);
				remoteOperation.switchOff();
				return true;
			}
			case sabotageDeactivate:
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), vMaster->getLMaster()->getPlayer(LPlayer::Local));
				return remoteOperation.sabotageDeactivate(lPlant);
			}
			case sabotageResource: 
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), vMaster->getLMaster()->getPlayer(LPlayer::Local));
				return remoteOperation.sabotageResource(lPlant);
			}
			case sabotageRemove:
			{
				LRemoteOperation remoteOperation(lPlant->getLField()->getLPlayingField(), vMaster->getLMaster()->getPlayer(LPlayer::Local));
				return remoteOperation.sabotageRemove(lPlant);
			}

			default:
				ASSERT("Invalid action"); return false;
		}
	}

	virtual void switchedOn() override
	{
		ASSERT(viewModelOn != nullptr, "viewModelOn is not initialized");
		ASSERT(viewModelOff != nullptr, "viewModelOff is not initialized");

		isOn = true;
		viewModelOn->switchOn();
		viewModelOff->switchOn();
		viewModelOff->getPlacementMain()->TranslateZDelta(-moveZOff);
		viewModelOn->getPlacementMain()->TranslateZDelta(moveZOff);

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone())
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_ON, getPlacementActive());
		}
	}

	virtual void switchedOff() override
	{
		ASSERT(viewModelOn != nullptr, "viewModelOn is not initialized");
		ASSERT(viewModelOff != nullptr, "viewModelOff is not initialized");

		isOn = false;
		viewModelOn->switchOff();
		viewModelOff->switchOff();
		viewModelOff->getPlacementMain()->TranslateZDelta(moveZOff);
		viewModelOn->getPlacementMain()->TranslateZDelta(-moveZOff);

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone())
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_OFF, getPlacementActive());
		}
	}

	virtual void sabotageResourcesReduced() override
	{
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacementActive());
	}

	virtual void sabotagePowerPlantSwitchedOff(const int seconds) override
	{	
		animationMaterial.SwitchOn();
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 CASTS<float>(VMaterialLoader::materialAnimSabotagePowerPlant_x * VMaterialLoader::materialAnimSabotagePowerPlant_y) / CASTS<float>(seconds));
		getPlacementActive()->AddPlacement(&placementForAnimation);
		VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
	}

	virtual void sabotagePowerPlantSwitchedOn() override
	{
		animationMaterial.SwitchOff();
		getPlacementActive()->SubPlacement(&placementForAnimation);
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 0.0f);
	}
};


NAMESPACE_VIEW_E
