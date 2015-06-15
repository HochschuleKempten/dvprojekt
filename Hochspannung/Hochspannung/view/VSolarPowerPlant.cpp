#include "VSolarPowerPlant.h"
#include "VPlayingField.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getPlacementMain(), &viewModel)
{
	vMaster->registerObserver(this);
}

VSolarPowerPlant::~VSolarPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VSolarPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	viewModel.getPlacementMain()->TranslateZDelta(viewModel.getHeight() / 2.0f - 0.1f);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
