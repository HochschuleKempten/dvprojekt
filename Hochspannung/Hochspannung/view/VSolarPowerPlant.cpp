#include "VSolarPowerPlant.h"
#include "VPlayingField.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


void VSolarPowerPlant::configViewModel(IViewModel& model, const bool switchedOn)
{
	model.initViewModel(this, switchedOn);
	model.init();

	model.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	model.getPlacementMain()->TranslateZDelta(model.getHeight() / 2.0f - 0.1f);
}

VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModelOn.getPlacementMain(), &viewModelOn, &viewModelOff)
{
	vMaster->registerObserver(this);
}

VSolarPowerPlant::~VSolarPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VSolarPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);
	translateViewModel();

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
