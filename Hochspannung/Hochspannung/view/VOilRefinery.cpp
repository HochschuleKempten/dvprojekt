#include "VOilRefinery.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VOilRefinery::VOilRefinery(VMaster* vMaster, LOilRefinery* lPlant)
	: IVPowerPlant(lPlant), IViewBuilding(vMaster, viewModel.getMainPlacement())
{}

VOilRefinery::~VOilRefinery()
{}

void VOilRefinery::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	viewModel.getMainPlacement()->Scale(0.4f);
	viewModel.getMainPlacement()->RotateYDelta(M_PI);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VOilRefinery);
}

ILBuilding* VOilRefinery::getLBuilding()
{
	return CASTD<ILBuilding*>(lPlant);
}


NAMESPACE_VIEW_E
