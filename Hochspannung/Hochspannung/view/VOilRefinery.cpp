#include "VOilRefinery.h"
#include "VPlayingField.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VOilRefinery::VOilRefinery(VMaster* vMaster, LOilRefinery* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getPlacementMain(), &viewModel)
{
	vMaster->registerObserver(this);
}

VOilRefinery::~VOilRefinery()
{
	vMaster->unregisterObserver(this);
}

void VOilRefinery::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	viewModel.init();

	const float scale = 0.4f;
	viewModel.getPlacementMain()->Scale(scale);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VOilRefinery, viewModel.getPlacementMain());
}


NAMESPACE_VIEW_E
