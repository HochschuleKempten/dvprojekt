#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
	: IViewBuilding(vMaster), IVPowerPlant(lPlant)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(2.0, 2.0, &m_zm, 24, true);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VCoalPowerPlant::initPowerPlant(const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(this, x, y);
}


NAMESPACE_VIEW_E
