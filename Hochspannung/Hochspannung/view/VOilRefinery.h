# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "IViewPowerPlant.h"
#include "VModelOilRefinery.h"

NAMESPACE_VIEW_B


class VOilRefinery : public IViewPowerPlant
{
private:
	VModelOilRefinery viewModel;

public:
	VOilRefinery(VMaster *vMaster, LOilRefinery* lPlant);
	virtual ~VOilRefinery();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
};


NAMESPACE_VIEW_E
