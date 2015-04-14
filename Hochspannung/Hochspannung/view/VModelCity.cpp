#include "VModelCity.h"

NAMESPACE_VIEW_B

VModelCity::VModelCity(void)
{
	
	InitBuildings();
	GetPlacements();
	AddPlacements();
	TranslateBuildings();

}

VModelCity::~VModelCity(void)
{
	
}

void VModelCity::TranslateBuildings() {

	m_zpgebaeude1_01->Translate(150, 0, 0);
	m_zpgebaeude1_02->Translate(-150, 0, 75);
	m_zpgebaeude2_01->Translate(-100, 0, 0);
	m_zpgebaeude2_02->Translate(0, 0, 75);
	m_zpgebaeude3_01->Translate(0, 0, 0);
	m_zpgebaeude3_01->Translate(200, 0, 0);
	m_zpAppartment_01->Translate(0, 0, -75);
	m_zpAppartment_02->Translate(-100, 0, 150);
	m_zpAppartment_03->Translate(0, 0, -90);
	m_zpLargeOfficeBuilding_01->Translate(-150, 0, 0);
	m_zpLargeOfficeBuilding_02->Translate(100, 0, 150);
	m_zpOfficeTower_01->Translate(0, 0, -75);
	m_zpOfficeTower_02->Translate(-50, 0, 50);
	m_zpSmallOfficeBuilding_01->Translate(50, 0, 150);
	m_zpSmallOfficeBuilding_02->Translate(-50, 0, -50);

}

void VModelCity::InitBuildings() {

	gebaeude1_01 = new Gebauede01;
	gebaeude1_02 = new Gebauede01;
	gebaeude2_01 = new Gebaeude02;
	gebaeude2_02 = new Gebaeude02;
	gebaeude3_01 = new Gebaeude03;
	gebaeude3_02 = new Gebaeude03;
	appartment_01 = new CAppartments(5.0F);
	appartment_02 = new CAppartments(5.0F);
	appartment_03 = new CAppartments(5.0F);
	largeOfficeBuilding_01 = new CLargeOfficeBuilding(10.0F);
	largeOfficeBuilding_02 = new CLargeOfficeBuilding(10.0F);
	officeTower_01 = new COfficeTowerViewingDeck(5.0F);
	officeTower_02 = new COfficeTowerViewingDeck(4.0F);
	smallOffice_01 = new CSmallOfficeBuilding(8.0F);
	smallOffice_02 = new CSmallOfficeBuilding(8.0F);

}

void VModelCity::GetPlacements(){

	m_zpgebaeude1_01 = gebaeude1_01->getPlacement();
	m_zpgebaeude1_02 = gebaeude1_02->getPlacement();
	m_zpgebaeude2_01 = gebaeude2_01->getPlacement();
	m_zpgebaeude2_02 = gebaeude2_02->getPlacement();
	m_zpgebaeude3_01 = gebaeude3_01->getPlacement();
	m_zpgebaeude3_02 = gebaeude3_02->getPlacement();
	m_zpAppartment_01 = appartment_01->getPlacement();
	m_zpAppartment_02 = appartment_02->getPlacement();
	m_zpAppartment_03 = appartment_03->getPlacement();
	m_zpLargeOfficeBuilding_01 = largeOfficeBuilding_01->getPlacement();
	m_zpLargeOfficeBuilding_02 = largeOfficeBuilding_02->getPlacement();
	m_zpOfficeTower_01 = officeTower_01->getPlacement();
	m_zpOfficeTower_02 = officeTower_02->getPlacement();
	m_zpSmallOfficeBuilding_01 = smallOffice_01->getPlacement();
	m_zpSmallOfficeBuilding_02 = smallOffice_02->getPlacement();

}

void VModelCity::AddPlacements() {

	AddPlacement(m_zpgebaeude1_01);
	AddPlacement(m_zpgebaeude1_02);
	AddPlacement(m_zpgebaeude2_01);
	AddPlacement(m_zpgebaeude2_02);

	AddPlacement(m_zpgebaeude3_01);
	AddPlacement(m_zpgebaeude3_02);
	AddPlacement(m_zpAppartment_01);
	AddPlacement(m_zpAppartment_02);
	AddPlacement(m_zpAppartment_03);
	AddPlacement(m_zpLargeOfficeBuilding_01);
	AddPlacement(m_zpLargeOfficeBuilding_02);
	AddPlacement(m_zpOfficeTower_01);
	AddPlacement(m_zpOfficeTower_02);
	AddPlacement(m_zpSmallOfficeBuilding_01);
	AddPlacement(m_zpSmallOfficeBuilding_02);

}


NAMESPACE_VIEW_E
