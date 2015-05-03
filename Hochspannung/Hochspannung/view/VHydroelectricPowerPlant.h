#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "IViewBuilding.h"


NAMESPACE_VIEW_B


class VHydroelectricPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant);
	virtual ~VHydroelectricPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
	virtual ILBuilding* getLBuilding() override;
};


NAMESPACE_VIEW_E
