#include "VHydroelectricPowerPlant.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VHydroelectricPowerPlant::VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, &m_zp)
{
	m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &VMaterialLoader::materialHydroelectricPowerPlant);
	m_zp.Init();
	m_zp.AddGeo(&m_zg);
}

VHydroelectricPowerPlant::~VHydroelectricPowerPlant()
{}

void VHydroelectricPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	//viewModel.initViewModel(this);
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	//SET_NAME_AND_COORDINATES(VIdentifier::VHydroelectricPowerPlant);
}


NAMESPACE_VIEW_E
