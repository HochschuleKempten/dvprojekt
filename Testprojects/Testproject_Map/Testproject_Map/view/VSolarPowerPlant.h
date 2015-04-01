# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LSolarPowerPlant.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B

class VSolarPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;

public:
	VSolarPowerPlant(VMaster *vMaster, LSolarPowerPlant* lPlant);
	virtual ~VSolarPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);


	

};


NAMESPACE_VIEW_E