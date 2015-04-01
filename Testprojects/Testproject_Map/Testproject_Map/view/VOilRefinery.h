# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B

class VOilRefinery : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;

public:
	VOilRefinery(VMaster *vMaster, LOilRefinery* lPlant);
	virtual ~VOilRefinery()
	{}

	virtual void initPowerPlant(const int x, const int y);


	

};


NAMESPACE_VIEW_E