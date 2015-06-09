#pragma once

#include "../logic/IVTransformerStation.h"
#include "IViewBuilding.h"
#include "VModelTransformerStation.h"

NAMESPACE_VIEW_B

class LTransformerStation;

class VTransformerStation : public IVTransformerStation, public IViewBuilding
{
private:
	VModelTransformerStation viewModel;

public:
	VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation);
	virtual ~VTransformerStation() override;

	virtual void initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y) override;
	virtual ILBuilding* getLBuilding() override;
	virtual bool clicked(action action) override;
};


NAMESPACE_VIEW_E
