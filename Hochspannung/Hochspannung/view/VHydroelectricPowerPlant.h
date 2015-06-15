#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewPowerPlant.h"
#include "VModelHydroelectricPowerPlant.h"


NAMESPACE_VIEW_B

class VHydroelectricPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	
	VModelHydroelectricPowerPlant viewModelOn;
	VModelHydroelectricPowerPlant viewModelOff;

protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) override;

public:
	
	VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant);
	virtual ~VHydroelectricPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;

	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModelOn.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VHydroelectricPowerPlant, fTimeDelta));
			viewModelOff.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VHydroelectricPowerPlant, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
