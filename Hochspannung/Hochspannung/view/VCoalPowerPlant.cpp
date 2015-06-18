#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


void VCoalPowerPlant::configViewModel(IViewModel& model, const bool switchedOn)
{
	model.initViewModel(this, switchedOn);
	model.init();

	const float scale = 0.3f;
	model.getPlacementMain()->Scale(scale);
	model.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	model.getPlacementMain()->TranslateZDelta(model.getHeight() * 0.5f * scale - 0.6f);
}

VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
: IViewPowerPlant(lPlant, vMaster, viewModelOn.getPlacementMain(), &viewModelOn, &viewModelOff)
{
	vMaster->registerObserver(this);
}

VCoalPowerPlant::~VCoalPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VCoalPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{	
	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);
	translateViewModel();

	VSoundLoader::play3DSoundLoop(VIdentifier::VCoalPowerPlant, viewModelOn.getPlacementMain());

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
