# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LSolarPowerPlant.h"
#include "IViewBuilding.h"


NAMESPACE_VIEW_B


class VSolarPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VSolarPowerPlant(VMaster *vMaster, LSolarPowerPlant* lPlant);
	virtual ~VSolarPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);


	static const int id = __COUNTER__;
};


NAMESPACE_VIEW_E
