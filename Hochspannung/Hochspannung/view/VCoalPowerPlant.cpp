#include "VCoalPowerPlant.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, &m_zp)
{
	m_zg.Init(2.0, 2.0, &VMaterialLoader::materialCoalPowerPlant, 24, true);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

VCoalPowerPlant::~VCoalPowerPlant()
{}

void VCoalPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	//viewModel.initViewModel(this);
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	//SET_NAME_AND_COORDINATES(VIdentifier::VCoalPowerPlant);
}


NAMESPACE_VIEW_E
