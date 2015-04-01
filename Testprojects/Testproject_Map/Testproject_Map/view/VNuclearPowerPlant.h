# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B

class VNuclearPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;

public:
	VNuclearPowerPlant(VMaster *vMaster, LNuclearPowerPlant* lPlant);
	virtual ~VNuclearPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);



	
};


NAMESPACE_VIEW_E