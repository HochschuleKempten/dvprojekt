#pragma once

#include "../logic/LPowerLine.h"
#include "../logic/IVPowerLine.h"
#include "IViewBuilding.h"
#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


class VPowerLine : public IVPowerLine, public IViewBuilding
{
private:
	VModelPowerLine viewModel;

public:
	VPowerLine(VMaster *vMaster, LPowerLine* lPlant);
	virtual ~VPowerLine();

	virtual void initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation) override;
	virtual void orientationChanged(const int orientation) override;
	virtual ILBuilding* getLBuilding() override;
	virtual bool clicked(action action) override;
	virtual void sabotagePowerLineRemoved() override;
	virtual void updateValue(const int value) override;
};


NAMESPACE_VIEW_E 
