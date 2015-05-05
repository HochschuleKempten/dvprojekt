#include "VSolarPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VSolarPowerPlant::VSolarPowerPlant(VMaster* vMaster, LSolarPowerPlant* lPlant)
	: IVPowerPlant(lPlant), IViewBuilding(vMaster, viewModel.getMainPlacement())
{
}

VSolarPowerPlant::~VSolarPowerPlant()
{}

void VSolarPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	viewModel.getMainPlacement()->RotateY(M_PI);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VSolarPowerPlant);
}

ILBuilding* VSolarPowerPlant::getLBuilding()
{
	return CASTD<ILBuilding*>(lPlant);
}


NAMESPACE_VIEW_E
