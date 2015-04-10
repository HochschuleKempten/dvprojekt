#include "VOilRefinery.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VOilRefinery::VOilRefinery(VMaster* vMaster, LOilRefinery* lPlant)
	: IViewBuilding(vMaster, &m_zp), IVPowerPlant(lPlant)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &m_zm);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VOilRefinery::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}

int VOilRefinery::id = IDGenerator::generateID();


NAMESPACE_VIEW_E
