# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LWindmillPowerPlant.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B

class VWindmillPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;
	//TODO (V) Windkraftwerk einbauen

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
    virtual ~VWindmillPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);
     

		

};


NAMESPACE_VIEW_E