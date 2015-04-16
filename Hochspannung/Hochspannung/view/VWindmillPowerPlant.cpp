#include "VWindmillPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VWindmillPowerPlant::VWindmillPowerPlant(VMaster* vMaster, LWindmillPowerPlant* lPlant)
	: IViewBuilding(vMaster, &m_zp), IVPowerPlant(lPlant)
{
	m_zp.RotateX(CASTS<float>(M_PI / 2.0));
	m_zp.ScaleDelta(0.8f);
	m_zp.TranslateZDelta(7.0f);

	vMaster->registerObserver(this);
}

VWindmillPowerPlant::~VWindmillPowerPlant()
{}

void VWindmillPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VWindmillPowerPlant);
}




NAMESPACE_VIEW_E
