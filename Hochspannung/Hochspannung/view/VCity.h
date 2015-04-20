#pragma once

#include "../logic/IVCity.h"
#include "IViewBuilding.h"
#include "VModelCity.h"

NAMESPACE_VIEW_B


class LCity;

class VCity : public IVCity, public IViewBuilding
{
private:
	//VModelCity m_zp;
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VCity(VMaster *vMaster, LCity* lCity);
	virtual ~VCity();

	virtual void initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y);
	virtual void updatePopulation(const int population) override;
	virtual void updateEnergy(const int energy) override;
};


NAMESPACE_VIEW_E
