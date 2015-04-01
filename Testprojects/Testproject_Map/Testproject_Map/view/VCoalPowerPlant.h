#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoCone m_zg;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant);

	virtual ~VCoalPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);

};


NAMESPACE_VIEW_E
