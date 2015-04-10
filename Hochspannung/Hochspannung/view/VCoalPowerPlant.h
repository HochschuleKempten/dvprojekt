#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewBuilding.h"
#include "Trasse.h"


NAMESPACE_VIEW_B


class VCoalPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CTrasse m_zp;
	//CPlacement m_zp;
	//CGeoCone m_zg;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant);

	virtual ~VCoalPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);


	static const int id = __COUNTER__;
};


NAMESPACE_VIEW_E
