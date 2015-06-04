#include "VHydroelectricPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VHydroelectricPowerPlant::VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getMainPlacement())
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

	const float scale = 0.3f;
	viewModel.getMainPlacement()->Scale(scale);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() * 0.5f * scale - 0.6f);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
	
	VSoundLoader::play3DSoundLoop(VIdentifier::VHydroelectricPowerPlant, viewModel.getMainPlacement());

	SET_NAME_AND_COORDINATES(VIdentifier::VHydroelectricPowerPlant);
}


NAMESPACE_VIEW_E
