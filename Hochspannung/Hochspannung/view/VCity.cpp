#include "VCity.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LCity.h"
#include "VUI.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VCity::VCity(VMaster *vMaster, LCity* lCity)
	: IVCity(lCity), IViewBuilding(vMaster, viewModel.getMainPlacement())
{
	viewModel.getMainPlacement()->RotateX(CASTS<float>(M_PI / 2.0F));
	viewModel.getMainPlacement()->ScaleDelta(0.1f);
	//viewModel.getMainPlacement()->TranslateZDelta(0.5f);
}

VCity::~VCity()
{}

void VCity::initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VCity);
}

void VCity::updatePopulation(const int population)
{
	vMaster->getVUi()->updatePopulation(population);
}

void VCity::updateEnergy(const int energy)
{
	//todo (L)
}

void VCity::updateEnergySurplus(const int surplus)
{
	vMaster->getVUi()->updateEnergySurplus(CASTS<float>(lCity->getEnergySurplusRatio()));
}

void VCity::energyLow(const int surplus)
{
	//TODO (V) inform gui about surplus
	VSoundLoader::playSoundeffect(VSoundLoader::ENERGY_LOW, getPlacement());
}

ILBuilding* VCity::getLBuilding()
{
	return CASTD<ILBuilding*>(lCity);
}

bool VCity::clicked(action action) 
{
	switch (action)
	{
	default:ASSERT("Invalid action"); return false;
	}
}


NAMESPACE_VIEW_E
