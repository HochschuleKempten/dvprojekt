#include "VMountains.h"

NAMESPACE_VIEW_B


VMountains::VMountains(VMaster* vMaster, const int x, const int y)
	: IViewBuilding(vMaster, viewModel.getPlacementMain())
{
	viewModel.initViewModel(nullptr);
	viewModel.init();
	viewModel.getPlacementMain()->RotateX(CASTS<float>(M_PI / 2.0F));
	viewModel.getPlacementMain()->ScaleDelta(0.3f);

	vMaster->getVPlayingField()->placeObject(this, x, y);
}

VMountains::~VMountains()
{}

bool VMountains::clicked(action /*action*/)
{
	ASSERT("Invalid action");
	return false;
}

ILBuilding* VMountains::getLBuilding()
{
	return nullptr;
}

NAMESPACE_VIEW_E
