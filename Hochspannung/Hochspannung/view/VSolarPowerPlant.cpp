#include "VSolarPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
	: IVPowerPlant(lPlant), IViewBuilding(vMaster, &m_zp)
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &m_zm);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

VSolarPowerPlant::~VSolarPowerPlant()
{}

void VSolarPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	//viewModel.initViewModel(this);
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VSolarPowerPlant);
}

ILBuilding* VSolarPowerPlant::getLBuilding()
{
	return CASTD<ILBuilding*>(lPlant);
}


NAMESPACE_VIEW_E
