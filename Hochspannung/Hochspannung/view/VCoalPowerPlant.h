#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "VMaster.h"
#include "IViewPowerPlant.h"
#include "VModelCoalPowerPlant.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelCoalPowerPlant viewModelOn;
	VModelCoalPowerPlant viewModelOff;
	float timeLastCheck = 0;
	
protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) override;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant);
	virtual ~VCoalPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModelOn.moveLore(VMaterialLoader::getRotationPerTick(VIdentifier::VCoalPowerPlant, fTimeDelta));
			viewModelOff.moveLore(VMaterialLoader::getRotationPerTick(VIdentifier::VCoalPowerPlant, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
