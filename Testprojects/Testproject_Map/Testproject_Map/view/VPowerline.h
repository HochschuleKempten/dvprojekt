#pragma once


#include "../logic/LPowerLine.h"
#include "../logic/IVPowerLine.h"
#include "IViewBuilding.h"


NAMESPACE_VIEW_B


class VPowerLine : public IVPowerLine, public IViewBuilding
{
private:
	CGeoEllipsoid m_zg;

public:
	VPowerLine(VMaster *vMaster, LPowerLine* lPlant);
	virtual ~VPowerLine()
	{}

	virtual void initPowerLine(const int x, const int y);
};


NAMESPACE_VIEW_E 