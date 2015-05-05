#include "VModelCity.h"

NAMESPACE_VIEW_B


VModelCity::VModelCity(void)
{
	
	InitBuildings();
	
	AddPlacements();
	TranslateBuildings();

}

VModelCity::~VModelCity(void)
{
	
}

void VModelCity::InitBuildings() {

	Building01 building1_01;
	Building01 building1_02;
	Building02 building2_01;
	Building02 building2_02;
	Building03 building3_01;
	Building03 building3_02;
	CAppartments appartment_01(1.0F);
	CAppartments appartment_02(1.0F);
	CAppartments appartment_03(1.0F);
	CLargeOfficeBuilding largeOfficeBuilding_01(1.0F);
	CLargeOfficeBuilding largeOfficeBuilding_02(1.0F);
	COfficeTowerViewingDeck officeTower_01(0.5F);
	COfficeTowerViewingDeck officeTower_02(0.4F);
	CSmallOfficeBuilding smallOffice_01(0.8F);
	CSmallOfficeBuilding smallOffice_02(0.8F);

	m_zgsocket.Init(CHVector(20.F, 1.F, 20), &m_zmsocket);

}

void VModelCity::AddPlacements() {

	m_zpMain.AddPlacement(&Building1_01);
	m_zpMain.AddPlacement(&Building1_02);
	m_zpMain.AddPlacement(&Building2_01);
	m_zpMain.AddPlacement(&Building2_02);
	m_zpMain.AddPlacement(&Building3_01);
	m_zpMain.AddPlacement(&Building3_02);
	m_zpMain.AddPlacement(&appartment_01);
	m_zpMain.AddPlacement(&appartment_02);
	m_zpMain.AddPlacement(&appartment_03);
	m_zpMain.AddPlacement(&largeOfficeBuilding_01);
	m_zpMain.AddPlacement(&largeOfficeBuilding_02);
	m_zpMain.AddPlacement(&officeTower_01);
	m_zpMain.AddPlacement(&officeTower_02);
	m_zpMain.AddPlacement(&smallOffice_01);
	m_zpMain.AddPlacement(&smallOffice_02);

	m_zpsocket.AddGeo(&m_zgsocket);
	m_zpMain.AddPlacement(&m_zpsocket);
	
	

}

void VModelCity::TranslateBuildings() {

	Building1_01.Translate(15, 1, 0);
	Building1_02.Translate(-15, 1, 7.5);
	Building2_01.Translate(-10, 1, 0);
	Building2_02.Translate(0, 1, 7.5);
	Building3_01.Translate(0, 1, 0);
	Building3_01.Translate(10, 1, 0);
	appartment_01.Translate(0, 1, -7.5);
	appartment_02.Translate(-10, 1, 15);
	appartment_03.Translate(0, 1, -9);
	largeOfficeBuilding_01.Translate(-15, 1, 0);
	largeOfficeBuilding_02.Translate(10, 1, 15);
	officeTower_01.Translate(0, 1, -7.5);
	officeTower_02.Translate(-5.0, 1, 5.0);
	smallOffice_01.Translate(5.0, 1, 15);
	smallOffice_02.Translate(-5.0, 1, -5.0);

}


NAMESPACE_VIEW_E
