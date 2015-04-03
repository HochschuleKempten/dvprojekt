#pragma once

#include "../logic/LPowerLine.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class VPowerLine : public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VPowerLine(VMaster* vMaster);
	virtual ~VPowerLine()
	{}

	virtual void init(const int x, const int y);
};


NAMESPACE_VIEW_E 
