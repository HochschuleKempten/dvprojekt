#include "VPowerLine.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"

NAMESPACE_VIEW_B


static VModelPowerLine::DIRECTION convertOrientation(const int orientation)
{
	int modelOrientation = 0;

	if (orientation & ILBuilding::NORTH) {
		modelOrientation |= VModelPowerLine::NORTH;
	}
	if (orientation & ILBuilding::EAST) {
		modelOrientation |= VModelPowerLine::EAST;
	}
	if (orientation & ILBuilding::SOUTH) {
		modelOrientation |= VModelPowerLine::SOUTH;
	}
	if (orientation & ILBuilding::WEST) {
		modelOrientation |= VModelPowerLine::WEST;
	}

	return static_cast<VModelPowerLine::DIRECTION>(modelOrientation);
}

VPowerLine::VPowerLine(VMaster* vMaster, LPowerLine* lpowerLine)
	: IVPowerLine(lpowerLine), IViewBuilding(vMaster, viewModel.getMainPlacement()),
	  viewModel(vMaster->getPlayingField()->getFieldSize())
{}

VPowerLine::~VPowerLine()
{}

void VPowerLine::initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation)
{
	viewModel.initViewModel(this);
	viewModel.Init(convertOrientation(orientation));
	viewModel.getMainPlacement()->RotateX(CASTS<float>(M_PI / 2.0f));
	viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() / 2.0f);

	vMaster->getPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VPowerLine);
}

void VPowerLine::orientationChanged(const int orientation)
{
	viewModel.SetDirection(convertOrientation(orientation));
}

ILBuilding* VPowerLine::getLBuilding()
{
	return CASTD<ILBuilding*>(lPowerLine);
}

bool VPowerLine::clicked(action action)
{
	switch (action)
	{	
	  default:ASSERT("Invalid action"); return false;
	}
}

NAMESPACE_VIEW_E
