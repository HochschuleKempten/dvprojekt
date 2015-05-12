#include "VTransformerStation.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LTransformerStation.h"
#include "VUI.h"

NAMESPACE_VIEW_B


VTransformerStation::VTransformerStation(VMaster *vMaster, LTransformerStation* lTransformerStation)
	: IVTransformerStation(lTransformerStation), IViewBuilding(vMaster, &m_zp)
{
	m_zg.Init(1.2f, &VMaterialLoader::materialGreen);
	m_zp.AddGeo(&m_zg);
}

VTransformerStation::~VTransformerStation()
{}

void VTransformerStation::initTransformerStation(const std::shared_ptr<IVTransformerStation>& objPtr, const int x, const int y)
{
	//viewModel.initViewModel(this);
	vMaster->getPlayingField()->placeObject(std::dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	//SET_NAME_AND_COORDINATES(VIdentifier::VTransformerStation);
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
