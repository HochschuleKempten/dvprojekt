#include "VOilRefinery.h"
#include "VPlayingField.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


void VOilRefinery::configViewModel(IViewModel& model, const bool switchedOn)
{
	model.initViewModel(this, switchedOn);
	model.init();

	const float scale = 0.4f;
	model.getPlacementMain()->Scale(scale);
	model.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	VSoundLoader::play3DSoundLoop(VIdentifier::VOilRefinery, model.getPlacementMain());
}

VOilRefinery::VOilRefinery(VMaster* vMaster, LOilRefinery* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModelOn.getPlacementMain(), &viewModelOn, &viewModelOff)
{
	vMaster->registerObserver(this);
}

VOilRefinery::~VOilRefinery()
{
	vMaster->unregisterObserver(this);
}

void VOilRefinery::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);
	translateViewModel();

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
