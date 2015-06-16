#include "VNuclearPowerPlant.h"
#include "VPlayingField.h"
#include "VMaster.h"

NAMESPACE_VIEW_B

void VNuclearPowerPlant::configViewModel(IViewModel& model, const bool switchedOn)
{
	model.initViewModel(this, switchedOn);
	model.init();

	const float scale = 0.4f;
	model.getPlacementMain()->Scale(scale);
	model.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	model.getPlacementMain()->TranslateZDelta(0.1);
}

VNuclearPowerPlant::VNuclearPowerPlant(VMaster* vMaster, LNuclearPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModelOn.getPlacementMain(), &viewModelOn, &viewModelOff)
{}

void VNuclearPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);
	translateViewModel();

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
