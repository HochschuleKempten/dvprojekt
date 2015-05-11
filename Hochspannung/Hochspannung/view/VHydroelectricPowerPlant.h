#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "IViewPowerPlant.h"


NAMESPACE_VIEW_B


class VHydroelectricPowerPlant : public IViewPowerPlant
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant);
	virtual ~VHydroelectricPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
};


NAMESPACE_VIEW_E
