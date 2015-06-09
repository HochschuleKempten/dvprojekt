# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LSolarPowerPlant.h"
#include "IViewPowerPlant.h"
#include "VModelSolarPowerplant.h"

NAMESPACE_VIEW_B



class VSolarPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelSolarPowerPlant viewModel;

public:
	VSolarPowerPlant(VMaster *vMaster, LSolarPowerPlant* lPlant);
	virtual ~VSolarPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;

	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModel.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VSolarPowerPlant, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
