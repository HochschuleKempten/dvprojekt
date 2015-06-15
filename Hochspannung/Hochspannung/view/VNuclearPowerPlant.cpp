#include "VNuclearPowerPlant.h"
#include "VPlayingField.h"
#include "VMaster.h"

NAMESPACE_VIEW_B

VNuclearPowerPlant::VNuclearPowerPlant(VMaster* vMaster, LNuclearPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getPlacementMain(), &viewModel)
{}

void VNuclearPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	viewModel.init();

	const float scale = 0.4f;
	viewModel.getPlacementMain()->Scale(scale);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	viewModel.getPlacementMain()->TranslateZDelta(0.1);
	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
