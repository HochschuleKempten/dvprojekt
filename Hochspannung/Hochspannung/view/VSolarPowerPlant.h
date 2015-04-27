# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LSolarPowerPlant.h"
#include "IViewBuilding.h"
#include "VModelSolarPowerPlant.h"

NAMESPACE_VIEW_B


class VSolarPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	VModelSolarPowerPlant viewModel;

public:
	VSolarPowerPlant(VMaster *vMaster, LSolarPowerPlant* lPlant);
	virtual ~VSolarPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
};


NAMESPACE_VIEW_E
