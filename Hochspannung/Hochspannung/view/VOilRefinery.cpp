#include "VOilRefinery.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VOilRefinery::VOilRefinery(VMaster* vMaster, LOilRefinery* lPlant)
	: IViewPowerPlant(lPlant, vMaster, viewModel.getMainPlacement())
{}

VOilRefinery::~VOilRefinery()
{}

void VOilRefinery::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);

	const float scale = 0.4f;
	viewModel.getMainPlacement()->Scale(scale);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() * scale * 0.5f);

	vMaster->getPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VOilRefinery);
}


NAMESPACE_VIEW_E
