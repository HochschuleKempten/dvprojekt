# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "IViewBuilding.h"
#include "VModelNuclearPowerPlant.h"

NAMESPACE_VIEW_B


class VNuclearPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	VModelNuclearPowerPlant viewModel;

public:
	VNuclearPowerPlant(VMaster *vMaster, LNuclearPowerPlant* lPlant);
	virtual ~VNuclearPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
	virtual ILBuilding* getLBuilding() override;
};


NAMESPACE_VIEW_E
