# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "../logic/IVTickObserver.h"
#include "IViewPowerPlant.h"
#include "VModelOilRefinery.h"

NAMESPACE_VIEW_B


class VOilRefinery : public IViewPowerPlant, public IVTickObserver
{
private:
	VModelOilRefinery viewModelOn;
	VModelOilRefinery viewModelOff;

protected:
	virtual void configViewModel(IViewModel& model, const bool switchedOn) override;

public:
	VOilRefinery(VMaster *vMaster, LOilRefinery* lPlant);
	virtual ~VOilRefinery();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;

	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			viewModelOn.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VOilRefinery, fTimeDelta));
			viewModelOff.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VOilRefinery, fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
