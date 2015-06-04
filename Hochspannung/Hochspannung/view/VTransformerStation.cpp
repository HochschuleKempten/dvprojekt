#include "VTransformerStation.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LTransformerStation.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VTransformerStation::VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation)
	: IVTransformerStation(lTransformerStation), IViewBuilding(vMaster, viewModel.getMainPlacement())
{}

VTransformerStation::~VTransformerStation()
{}

void VTransformerStation::initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	
	viewModel.getMainPlacement()->Scale(0.4f);
	viewModel.getMainPlacement()->RotateXDelta(CASTS<float>(M_PI / 2.0f));
	//viewModel.getMainPlacement()->TranslateZDelta(viewModel.getHeight() / 2.0f);
	

	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	VSoundLoader::play3DSoundLoop(VIdentifier::VTransformerStation, viewModel.getMainPlacement());
	
	SET_NAME_AND_COORDINATES(VIdentifier::VTransformerStation);
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
