#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getMainPlacement(), &viewModel)
{
	vMaster->registerObserver(this);
}

VCoalPowerPlant::~VCoalPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VCoalPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{	
	viewModel.initViewModel(this);
	viewModel.init();

	const float scale = 0.3f;
	viewModel.getMainPlacement()->Scale(scale);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() * 0.5f * scale - 0.6f);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
	
}


NAMESPACE_VIEW_E
