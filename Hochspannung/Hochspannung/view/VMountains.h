#pragma once

#include "VGeneral.h"
#include "IViewBuilding.h"
#include "VModelMountains.h"

NAMESPACE_VIEW_B


class VMountains : public IViewBuilding
{
private:
	VModelMountains viewModel;

public:
	explicit VMountains(VMaster* vMaster, const int x, const int y);
	~VMountains();
	
	virtual bool clicked(action action) override;
	virtual ILBuilding* getLBuilding() override;
};


NAMESPACE_VIEW_E
