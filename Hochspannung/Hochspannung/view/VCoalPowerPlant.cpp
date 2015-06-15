#include "VCoalPowerPlant.h"
#include "VPlayingField.h"

NAMESPACE_VIEW_B


VCoalPowerPlant::VCoalPowerPlant(VMaster* vMaster, LCoalPowerPlant* lPlant)
: IViewPowerPlant(lPlant, vMaster, viewModelOn.getMainPlacement(), &viewModelOn, &viewModelOff)
{
	vMaster->registerObserver(this);
}

VCoalPowerPlant::~VCoalPowerPlant()
{
	vMaster->unregisterObserver(this);
}

void VCoalPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{	
	auto configViewModel = [this] (IViewModel& model, const bool switchedOn)
	{
		model.initViewModel(this, switchedOn);
		model.init();

		const float scale = 0.3f;
		model.getMainPlacement()->Scale(scale);
		model.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0));
		model.getMainPlacement()->TranslateZDelta(model.getHeight() * 0.5f * scale - 0.6f);
	};

	configViewModel(viewModelOn, true);
	configViewModel(viewModelOff, false);

	if (isOn)
	{
		viewModelOff.getMainPlacement()->TranslateZDelta(-moveZOff);
	}
	else
	{
		viewModelOn.getMainPlacement()->TranslateZDelta(-moveZOff);
	}

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}


NAMESPACE_VIEW_E
