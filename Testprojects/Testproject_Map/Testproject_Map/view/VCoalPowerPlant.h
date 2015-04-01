#pragma once

#include "../logic/IVPowerPlant.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/Array2D.h"
#include "VMaster.h"
#include "IViewBuilding.h"

NAMESPACE_VIEW_B


class VCoalPowerPlant : public IVPowerPlant, public IViewBuilding
{
private:
	CGeoCone m_zg;

public:
	VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* plant)
		: IVPowerPlant(plant), IViewBuilding(vMaster)
	{
		m_zm.MakeTextureDiffuse("textures\\_original.jpg");
		m_zg.Init(2.0, 2.0, &m_zm, 24, true);
		m_zp.Init();
		m_zp.AddGeo(&m_zg);
	}

	virtual ~VCoalPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y);

};


NAMESPACE_VIEW_E
