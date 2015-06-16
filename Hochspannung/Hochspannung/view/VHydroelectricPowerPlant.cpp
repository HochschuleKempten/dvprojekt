#include "VHydroelectricPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


void VHydroelectricPowerPlant::configViewModel(IViewModel& model, const bool switchedOn)
{
	model.initViewModel(this,switchedOn);
	model.init();

	const float scale = 0.3f;
	model.getPlacementMain()->Scale(scale);
	model.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	model.getPlacementMain()->TranslateZDelta(model.getHeight() * 0.5f * scale - 0.55f);
    VSoundLoader::play3DSoundLoop(VIdentifier::VHydroelectricPowerPlant, model.getPlacementMain());
}

VHydroelectricPowerPlant::VHydroelectricPowerPlant(VMaster* vMaster, LHydroelectricPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModelOn.getPlacementMain(), &viewModelOn, &viewModelOff)
{
	vMaster->registerObserver(this);
}

VHydroelectricPowerPlant::~VHydroelectricPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VHydroelectricPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{	
	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);
	translateViewModel();
	
	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
