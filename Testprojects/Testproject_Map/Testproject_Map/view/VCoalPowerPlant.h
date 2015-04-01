#pragma once

#include "VMaster.h"
#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/Array2D.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IVPowerPlant, public IViewObject
{
private:

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* plant)
		: IViewObject(vMaster), IVPowerPlant(plant)
	{}

	//TODO (V) use geo, placement and material functions

	virtual ~VCoalPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);

};


NAMESPACE_VIEW_E
