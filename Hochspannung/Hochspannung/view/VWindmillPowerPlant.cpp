#include "VWindmillPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B

VWindmillPowerPlant::VWindmillPowerPlant(VMaster* vMaster, LWindmillPowerPlant* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getMainPlacement())
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
	viewModel.getMainPlacement()->Scale(scale);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() * scale -0.1);

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VWindmillPowerPlant, viewModel.getMainPlacement());
	SET_NAME_AND_COORDINATES(VIdentifier::VWindmillPowerPlant);	//TODO (JS) remove
}


NAMESPACE_VIEW_E
