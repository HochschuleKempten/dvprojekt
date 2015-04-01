#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class VHydroelectricPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;

public:
	VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant);
	virtual ~VHydroelectricPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);
};


NAMESPACE_VIEW_E
