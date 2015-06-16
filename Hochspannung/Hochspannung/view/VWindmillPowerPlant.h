# pragma once

#include "../logic/LWindmillPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewPowerPlant.h"
#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B

class VWindmillPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelWindmillPowerPlant viewModelOn;
	VModelWindmillPowerPlant viewModelOff;

protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) override;

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
	virtual ~VWindmillPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
     
	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModelOn.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VWindmillPowerPlant, fTimeDelta));
			viewModelOff.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VWindmillPowerPlant, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
