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
			return ptrViewModelOn->getPlacementMain();
		}
		else
		{
			return ptrViewModelOff != nullptr ? ptrViewModelOff->getPlacementMain() : nullptr;
		}
	}

protected:
	bool isOn = false;
	CGeoQuad quadForAnimation;
	CPlacement placementForAnimation;
	CMaterial animationMaterial = VMaterialLoader::materialAnimSabotagePowerPlant;
	IViewModel* ptrViewModelOn = nullptr;
	IViewModel* ptrViewModelOff = nullptr;
	const float moveZOff = 1337.42f;

protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) = 0;

	void translateViewModel()
	{
		ASSERT(ptrViewModelOn != nullptr, "ptrViewModelOn is not initialized");
		ASSERT(ptrViewModelOff != nullptr, "ptrViewModelOff is not initialized");

		if (isOn)
		{
			ptrViewModelOff->getPlacementMain()->TranslateZDelta(-moveZOff);
		}
		else
		{
			ptrViewModelOn->getPlacementMain()->TranslateZDelta(-moveZOff);
		}
	}

public:
	inline IViewPowerPlant(ILPowerPlant* lPlant, VMaster* vMaster, CPlacement* m_zp, IViewModel* viewModelOn, IViewModel* viewModelOff)
		: IVPowerPlant(lPlant), IViewBuilding(vMaster, m_zp), ptrViewModelOn(viewModelOn), ptrViewModelOff(viewModelOff)
	{
		quadForAnimation.Init(2, 2, &animationMaterial);
		placementForAnimation.AddGeo(&quadForAnimation);
		placementForAnimation.TranslateY(2.0f);
		placementForAnimation.TranslateZDelta(2.0f);
		placementForAnimation.RotateXDelta(PI / 4.0f);
		animationMaterial.SwitchOff();
	}

	inline virtual ~IViewPowerPlant() override
	{}

	inline CPlacement* getPlacementSecond() const override
	{
		ASSERT(ptrViewModelOff != nullptr, "ptrViewModelOff is not initialized");
		return ptrViewModelOff->getPlacementMain();
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
			case sell:
			{
				return lPlant->checkSell();
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
		ASSERT(ptrViewModelOn != nullptr, "ptrViewModelOn is not initialized");
		ASSERT(ptrViewModelOff != nullptr, "ptrViewModelOff is not initialized");

		isOn = true;
		ptrViewModelOn->switchOn();
		ptrViewModelOff->switchOn();
		ptrViewModelOff->getPlacementMain()->TranslateZDelta(-moveZOff);
		ptrViewModelOn->getPlacementMain()->TranslateZDelta(moveZOff);

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone() && getLBuilding()->getPlayerId() == LPlayer::Local)
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_ON, getPlacementActive());
		}
	}

	virtual void switchedOff() override
	{
		ASSERT(ptrViewModelOn != nullptr, "ptrViewModelOn is not initialized");
		ASSERT(ptrViewModelOff != nullptr, "ptrViewModelOff is not initialized");

		isOn = false;
		ptrViewModelOn->switchOff();
		ptrViewModelOff->switchOff();
		ptrViewModelOff->getPlacementMain()->TranslateZDelta(moveZOff);
		ptrViewModelOn->getPlacementMain()->TranslateZDelta(-moveZOff);

		if (getLBuilding()->getLField()->getLPlayingField()->isInitDone() && getLBuilding()->getPlayerId() == LPlayer::Local)
		{
			VSoundLoader::playSoundeffect(VSoundLoader::POWERPLANT_SWITCH_OFF, getPlacementActive());
		}
	}

	virtual void sabotageResourcesReduced() override
	{
		if (getLBuilding()->getPlayerId() == LPlayer::Local)
		{
			VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacementActive());
		}
	}

	virtual void sabotagePowerPlantSwitchedOff(const int seconds) override
	{	
		animationMaterial.SwitchOn();
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 CASTS<float>(VMaterialLoader::materialAnimSabotagePowerPlant_x * VMaterialLoader::materialAnimSabotagePowerPlant_y) / CASTS<float>(seconds));

	    vMaster->getVPlayingField()->placeObject(&placementForAnimation, lPlant->getLField()->getX(), lPlant->getLField()->getY());

		if (getLBuilding()->getPlayerId() == LPlayer::Local)
		{
			VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
		}
	}

	virtual void sabotagePowerPlantSwitchedOn() override
	{
		animationMaterial.SwitchOff();
		vMaster->getVPlayingField()->subObject(&placementForAnimation, lPlant->getLField()->getX(), lPlant->getLField()->getY());
		animationMaterial.SetAni(VMaterialLoader::materialAnimSabotagePowerPlant_x,
								 VMaterialLoader::materialAnimSabotagePowerPlant_y,
								 0.0f);
	}

	virtual void updateValue(const int value) override
	{
		std::pair<int, int> position = std::make_pair(this->lPlant->getLField()->getX(), this->lPlant->getLField()->getY());
		vMaster->getVUi()->contextMenuUpdateValue(position, value);
	}

	virtual void updateResourceValue(const int value) override
	{
		std::pair<int, int> position = std::make_pair(this->lPlant->getLField()->getX(), this->lPlant->getLField()->getY());
		vMaster->getVUi()->contextMenuUpdateResourceValue(position, value);
	}
};


NAMESPACE_VIEW_E
