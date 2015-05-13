#pragma once

#include "../logic/IVCity.h"
#include "IViewBuilding.h"
#include "VModelCity.h"

NAMESPACE_VIEW_B


class LCity;

class VCity : public IVCity, public IViewBuilding
{
private:
	VModelCity viewModel;

public:
	VCity(VMaster *vMaster, LCity* lCity);
	virtual ~VCity() override;

	virtual void initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y) override;
	virtual void updatePopulation(const int population) override;
	virtual void updateEnergy(const int energy) override;
	virtual ILBuilding* getLBuilding() override;
	virtual bool clicked(action action) override;
};


NAMESPACE_VIEW_E
