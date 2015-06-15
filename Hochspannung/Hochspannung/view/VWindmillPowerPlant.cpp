#include "VWindmillPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B

VWindmillPowerPlant::VWindmillPowerPlant(VMaster* vMaster, LWindmillPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getPlacementMain(), &viewModel)
{
	vMaster->registerObserver(this);
}

VWindmillPowerPlant::~VWindmillPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VWindmillPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);

	const float scale = 0.3f;
	viewModel.getPlacementMain()->Scale(scale);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getPlacementMain()->TranslateZDelta(viewModel.getHeight() * scale -0.1);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VWindmillPowerPlant, viewModel.getPlacementMain());
}


NAMESPACE_VIEW_E
