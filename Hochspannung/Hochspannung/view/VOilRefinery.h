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
	VModelOilRefinery viewModel;

public:
	VOilRefinery(VMaster *vMaster, LOilRefinery* lPlant);
	virtual ~VOilRefinery();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;

	inline virtual void tick(const float fTimeDelta) override
	{
		if (isOn)
		{
			const double sec = 8.0;	//Number of seconds per rotation
			viewModel.rotate(CASTS<float>((2.0 * M_PI / sec) * fTimeDelta));
		}
	}
};


NAMESPACE_VIEW_E
