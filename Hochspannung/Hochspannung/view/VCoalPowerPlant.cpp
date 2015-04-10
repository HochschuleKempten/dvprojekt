#include "VCoalPowerPlant.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
	: IViewBuilding(vMaster, &m_zp), IVPowerPlant(lPlant)
{
	m_zg.Init(2.0, 2.0, &VMaterialLoader::materialCoalPowerPlant, 24, true);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

void VCoalPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES
}





NAMESPACE_VIEW_E
