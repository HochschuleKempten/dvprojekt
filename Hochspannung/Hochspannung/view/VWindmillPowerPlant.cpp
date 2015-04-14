#include "VWindmillPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


VWindmillPowerPlant::VWindmillPowerPlant(VMaster* vMaster, LWindmillPowerPlant* lPlant)
	: IViewBuilding(vMaster, &m_zp), IVPowerPlant(lPlant)
{
	m_zp.RotateX(M_PI / 2.0);
	m_zp.ScaleDelta(0.8f);
	m_zp.TranslateZDelta(7.0);
	//m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	//m_zg.Init(CHVector(1.5, 2.6, 0.8), &m_zm);
	//m_zp.Init();
	//m_zp.AddGeo(&m_zg);

	vMaster->registerObserver(this);
}

void VWindmillPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VWindmillPowerPlant);
}




NAMESPACE_VIEW_E
