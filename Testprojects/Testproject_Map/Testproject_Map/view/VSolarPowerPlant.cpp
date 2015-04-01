#include "VSolarPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
: IViewBuilding(vMaster), IVPowerPlant(lPlant)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(CHVector(1.5, 2.6, 0.8), &m_zm);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VSolarPowerPlant::initPowerPlant(const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(this, x, y);
}

NAMESPACE_VIEW_E
