#pragma once

#include "VMaster.h"
#include "../logic/IVPowerPlant.h"
#include "../logic/ILPowerPlant.h"
#include "../logic/Array2D.h"
#include "IViewObject.h"

NAMESPACE_VIEW_B


class VPowerPlant : public IVPowerPlant, public IViewObject
{
private:
	

public:
	VPowerPlant(VMaster* vMaster, ILPowerPlant* plant)
		: IVPowerPlant(plant), IViewObject(vMaster)
	{}

	//TODO (V) use geo, placement and material functions

	virtual ~VPowerPlant()
	{}

	virtual void initPowerPlant(const int i, const int j);

};


NAMESPACE_VIEW_E