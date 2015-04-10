#pragma once

#include "../logic/LPowerLine.h"
#include "../logic/IVPowerLine.h"
#include "IViewBuilding.h"
#include "Trasse.h"

NAMESPACE_VIEW_B


class VPowerLine : public IVPowerLine, public IViewBuilding
{
private:
	CTrasse m_zp;
	//CPlacement m_zp;
	//CMaterial m_zm;
	//CGeoEllipsoid m_zg;

public:
	VPowerLine(VMaster *vMaster, LPowerLine* lPlant);
	virtual ~VPowerLine()
	{}

	virtual void initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y);
};


NAMESPACE_VIEW_E 
