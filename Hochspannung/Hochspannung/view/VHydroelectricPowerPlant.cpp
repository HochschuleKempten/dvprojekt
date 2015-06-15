#include "VHydroelectricPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VHydroelectricPowerPlant::VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getPlacementMain(), &viewModel)
{
	vMaster->registerObserver(this);
}

VHydroelectricPowerPlant::~VHydroelectricPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VHydroelectricPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{	
	viewModel.initViewModel(this);
	viewModel.init();

	const float scale = 0.3f;
	viewModel.getPlacementMain()->Scale(scale);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getPlacementMain()->TranslateZDelta(viewModel.getHeight() * 0.5f * scale - 0.55f);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VHydroelectricPowerPlant, viewModel.getPlacementMain());
}


NAMESPACE_VIEW_E
