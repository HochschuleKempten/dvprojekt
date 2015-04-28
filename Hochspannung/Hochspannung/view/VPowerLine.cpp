#include "VPowerLine.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B 


VPowerLine::VPowerLine(VMaster* vMaster, LPowerLine* lpowerLine)
	: IVPowerLine(lpowerLine), IViewBuilding(vMaster, viewModel.getMainPlacement()),
	  viewModel(vMaster->getPlayingField()->getFieldSize())
{}

VPowerLine::~VPowerLine()
{}

void VPowerLine::initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation)
{
	viewModel.Init(static_cast<VModelPowerLine::DIRECTION>(orientation));
	viewModel.getMainPlacement()->RotateX(CASTS<float>(M_PI / 2.0f));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() / 2.0f);

	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VPowerLine);
}


NAMESPACE_VIEW_E
