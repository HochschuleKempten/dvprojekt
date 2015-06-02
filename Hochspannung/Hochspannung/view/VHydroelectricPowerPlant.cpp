#include "VHydroelectricPowerPlant.h"
#include "VPlayingField.h"
#include "VMaterialLoader.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VHydroelectricPowerPlant::VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getMainPlacement())
{}

VHydroelectricPowerPlant::~VHydroelectricPowerPlant()
{}

void VHydroelectricPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);

	const float scale = 0.3f;
	viewModel.getMainPlacement()->Scale(scale);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() * 0.5f * scale);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VHydroelectricPowerPlant);
}


NAMESPACE_VIEW_E
