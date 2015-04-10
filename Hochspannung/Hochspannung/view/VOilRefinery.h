# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "IViewBuilding.h"
#include "../logic/IDGenerator.h"

NAMESPACE_VIEW_B


class VOilRefinery : public IVPowerPlant, public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VOilRefinery(VMaster *vMaster, LOilRefinery* lPlant);
	virtual ~VOilRefinery()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);

	static int id;
	

};


NAMESPACE_VIEW_E
