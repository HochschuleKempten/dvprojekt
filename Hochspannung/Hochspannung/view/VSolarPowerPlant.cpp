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
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VSolarPowerPlant);
}



NAMESPACE_VIEW_E
