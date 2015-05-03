# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewBuilding.h"
#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


class VWindmillPowerPlant : public IVPowerPlant, public IViewBuilding, public IVTickObserver
{
private:
	VModelWindmillPowerPlant viewModel;

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
	virtual ~VWindmillPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
     
	inline virtual void tick(const float fTimeDelta) override
	{
		const double sec = 2.0;	//Number of seconds per rotation
		viewModel.rotate(CASTS<float>((2.0 * M_PI / sec) * fTimeDelta));
	}
	virtual ILBuilding* getLBuilding() override;
};


NAMESPACE_VIEW_E
