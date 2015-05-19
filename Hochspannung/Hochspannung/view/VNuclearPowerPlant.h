# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "IViewPowerPlant.h"
#include "VModelNuclearPowerPlant.h"

NAMESPACE_VIEW_B


class VNuclearPowerPlant : public IViewPowerPlant
{
private:
	VModelNuclearPowerPlant viewModel;

public:
	VNuclearPowerPlant(VMaster *vMaster, LNuclearPowerPlant* lPlant);
	virtual ~VNuclearPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
};


NAMESPACE_VIEW_E
