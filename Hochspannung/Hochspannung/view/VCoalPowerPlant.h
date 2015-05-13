#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "VMaster.h"
#include "IViewPowerPlant.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IViewPowerPlant
{
private:
	CPlacement m_zp;
	CGeoCone m_zg;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant);
	virtual ~VCoalPowerPlant();

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) override;
};


NAMESPACE_VIEW_E
