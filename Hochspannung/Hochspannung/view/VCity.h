#pragma once

#include "../logic/IVCity.h"
#include "IViewBuilding.h"

class LCity;

NAMESPACE_VIEW_B


class VCity : public IVCity, public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VCity(VMaster *vMaster, LCity* lCity);
	virtual ~VCity();

	virtual void initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y);
};


NAMESPACE_VIEW_E
