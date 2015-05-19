# pragma once

#include "../logic/LWindmillPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewPowerPlant.h"
#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


class VWindmillPowerPlant : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelWindmillPowerPlant viewModel;

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
	virtual ~VWindmillPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
     
	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModel.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VWindmillPowerPlant, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
