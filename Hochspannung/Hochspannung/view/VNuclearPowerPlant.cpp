#include "VNuclearPowerPlant.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


VNuclearPowerPlant::VNuclearPowerPlant(VMaster* vMaster, LNuclearPowerPlant* lPlant)
: IVPowerPlant(lPlant), IViewBuilding(vMaster, viewModel.getMainPlacement())
{

}

void VNuclearPowerPlant::initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	//SET_NAME_AND_COORDINATES(VIdentifier::VNuclearPowerPlant);
}


NAMESPACE_VIEW_E
