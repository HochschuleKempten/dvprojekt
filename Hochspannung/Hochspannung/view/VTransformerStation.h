#pragma once

#include "../logic/IVTransformerStation.h"
#include "IViewBuilding.h"
#include "VModelCity.h"   // Use City Model untill we have a TransformerStation Model

NAMESPACE_VIEW_B


class LTransformerStation;

class VTransformerStation : public IVTransformerStation, public IViewBuilding
{
private:
	VModelCity viewModel;

public:
	VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation);
	virtual ~VTransformerStation() override;

	virtual void initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y) override;

};


NAMESPACE_VIEW_E
