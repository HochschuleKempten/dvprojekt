#include "VCity.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LCity.h"
#include "VUI.h"
#include "VSoundLoader.h"

NAMESPACE_VIEW_B


VCity::VCity(VMaster *vMaster, LCity* lCity)
	: IVCity(lCity), IViewBuilding(vMaster, viewModel.getPlacementMain())
{
	viewModel.getPlacementMain()->RotateX(CASTS<float>(M_PI / 2.0F));
	viewModel.getPlacementMain()->ScaleDelta(0.1f);
}

VCity::~VCity()
{}

void VCity::initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y)
{
	viewModel.initViewModel(this);
	vMaster->getVPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);
}

void VCity::updatePopulation(const int population)
{
	if (this->lCity->getPlayerId() & LPlayer::Local)
	{
		vMaster->getVUi()->updatePopulation(population);
	}

	std::pair<int, int> position = std::make_pair(lCity->getLField()->getX(), lCity->getLField()->getY());
	vMaster->getVUi()->contextMenuUpdatePopulation(position, population);
}

void VCity::updateEnergy(const int energy)
{
	//todo (V) what should happen here?
	std::pair<int, int> position = std::make_pair(lCity->getLField()->getX(), lCity->getLField()->getY());
	vMaster->getVUi()->contextMenuUpdateEnergy(position, energy);
}

void VCity::updateEnergySurplus(const int surplus)
{
	if (this->lCity->getPlayerId() & LPlayer::Local)
	{
		vMaster->getVUi()->updateEnergySurplus(surplus);
	}

	std::pair<int, int> position = std::make_pair(lCity->getLField()->getX(), lCity->getLField()->getY());
	vMaster->getVUi()->contextMenuUpdateEnergySurplus(position, surplus);
}

void VCity::energyLow(const int surplus)
{
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
