#include "VTransformerStation.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LTransformerStation.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VTransformerStation::VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation)
	: IVTransformerStation(lTransformerStation), IViewBuilding(vMaster, viewModel.getPlacementMain())
{}

VTransformerStation::~VTransformerStation()
{}

void VTransformerStation::initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	
	viewModel.getPlacementMain()->Scale(0.4f);
	viewModel.getPlacementMain()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	viewModel.getPlacementMain()->TranslateZDelta(-0.1);
	

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VTransformerStation, viewModel.getPlacementMain());
}

ILBuilding* VTransformerStation::getLBuilding()
{
	return CASTD<ILBuilding*>(lTransformerStation);
}

bool VTransformerStation::clicked(action action)
{
	switch (action)
	{
	default:ASSERT("Invalid action"); return false;
	}
}

NAMESPACE_VIEW_E
