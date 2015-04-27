#include "VTransformerStation.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaster.h"
#include "../logic/LTransformerSation.h"
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
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	//SET_NAME_AND_COORDINATES(VIdentifier::VTransformerStation);
}


NAMESPACE_VIEW_E
