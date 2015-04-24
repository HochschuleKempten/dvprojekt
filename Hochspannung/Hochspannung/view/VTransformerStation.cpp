#include "VTransformerStation.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LTransformerSation.h"
#include "VUI.h"

NAMESPACE_VIEW_B


VTransformerStation::VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation)
: IVTransformerStation(lTransformerStation), IViewBuilding(vMaster, viewModel.getMainPlacement())
{
	viewModel.getMainPlacement()->RotateX(CASTS<float>(M_PI / 2.0));
	viewModel.getMainPlacement()->ScaleDelta(0.1f);
	viewModel.getMainPlacement()->TranslateZDelta(0.5f);
}

VTransformerStation::~VTransformerStation()
{}

void VTransformerStation::initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VTransformerStation);
}

}