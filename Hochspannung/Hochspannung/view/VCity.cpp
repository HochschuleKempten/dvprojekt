#include "VCity.h"
#include "VPlayingField.h"
#include "VIdentifier.h"
#include "VMaterialLoader.h"
#include "VMaster.h"
#include "../logic/LCity.h"
#include "VUI.h"

NAMESPACE_VIEW_B


VCity::VCity(VMaster *vMaster, LCity* lCity)
	: IVCity(lCity), IViewBuilding(vMaster, &m_zp)
{
	//m_zg.Init(CHVector(1.5f, 2.6f, 0.8f), &VMaterialLoader::materialHydroelectricPowerPlant);
	//m_zp.Init();
	//m_zp.AddGeo(&m_zg);

	m_zp.RotateX(CASTS<float>(M_PI / 2.0));
	m_zp.ScaleDelta(0.01f);
	m_zp.TranslateZDelta(7.0f);
}

VCity::~VCity()
{}

void VCity::initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y)
{
	vMaster->getPlayingField()->placeObject(dynamic_pointer_cast<IViewBuilding>(objPtr), x, y);

	SET_NAME_AND_COORDINATES(VIdentifier::VCity);
}

void VCity::updatePopulation(const int population)
{
	vMaster->getVUi()->updatePopulation(population);
}

void VCity::updateEnergy(const int energy)
{
	DEBUG_OUTPUT("City new energy value = " << energy);
}

NAMESPACE_VIEW_E
