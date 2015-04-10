# pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "IViewBuilding.h"
#include "../logic/IDGenerator.h"

NAMESPACE_VIEW_B


class VNuclearPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CPlacement m_zp;
	CMaterial m_zm;
	CGeoEllipsoid m_zg;

public:
	VNuclearPowerPlant(VMaster *vMaster, LNuclearPowerPlant* lPlant);
	virtual ~VNuclearPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y);

	static int id;
};


NAMESPACE_VIEW_E
