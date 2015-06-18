#include "VPowerLine.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "VSoundLoader.h"
#include "../logic/LRemoteOperation.h"
#include "../logic/LSabotage.h"

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
	: IVPowerLine(lpowerLine), IViewBuilding(vMaster, viewModel.getPlacementMain()),
	  viewModel(vMaster->getVPlayingField()->getFieldSize())
{}

VPowerLine::~VPowerLine()
{}

void VPowerLine::initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation)
{
	viewModel.initViewModel(this);
	viewModel.Init(convertOrientation(orientation));
	viewModel.getPlacementMain()->RotateX(CASTS<float>(M_PI / 2.0f));
	viewModel.getPlacementMain()->TranslateZDelta(viewModel.getHeight() / 2.0f -0.45f);
	
	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
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
		case sabotageRemove:
			{
				LRemoteOperation remoteOperation(lPowerLine->getLField()->getLPlayingField(), vMaster->getLMaster()->getPlayer(LPlayer::Local));
				return remoteOperation.sabotageRemove(lPowerLine);
			}
		case sell:
			{
				return lPowerLine->checkSell();
			}

		default: ASSERT("Invalid action");
			return false;
	}
}

void VPowerLine::sabotagePowerLineRemoved()
{
	VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_RECEIVED, getPlacement());
}

void VPowerLine::updateValue(const int value)
{
	std::pair<int, int> position = std::make_pair(lPowerLine->getLField()->getX(), lPowerLine->getLField()->getY());
	vMaster->getVUi()->contextMenuUpdateValue(position, value);
}

NAMESPACE_VIEW_E
