# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/IVTickObserver.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class VWindmillPowerPlant : public IVPowerPlant, public IViewBuilding, public IVTickObserver
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;
	//TODO (V) Windkraftwerk einbauen

public:
	VWindmillPowerPlant(VMaster *vMaster, LWindmillPowerPlant* lPlant);
    virtual ~VWindmillPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);
     
	inline virtual void tick(const float fTimeDelta)
	{
		//TODO (V) rotate windmill
	}

};


NAMESPACE_VIEW_E
