#include "VModelCity.h"

NAMESPACE_VIEW_B


VModelCity::VModelCity(void)
: Building1_01_1(1.0F)
, Building1_02_1(1.0F)
, Building2_01_1(1.0F)
, Building2_02_1(1.0F)
, Building3_01_1(1.0F)
, Building3_02_1(1.0F)
, appartment_01_1(1.0F)
, appartment_02_1(1.0F)
, appartment_03_1(1.0F)
, largeOfficeBuilding_02_1(1.0F)
, officeTower_01_1(1.0F)
, officeTower_02_1(1.0F)
, smallOffice_01_1(1.0F)
, smallOffice_02_1(1.0F)
, largeOfficeBuilding_01_1(1.0F)

, Building1_01_2(2.0F)
, Building1_02_2(2.0F)
, Building2_01_2(2.0F)
, Building2_02_2(2.0F)
, Building3_01_2(2.0F)
, Building3_02_2(2.0F)
, appartment_01_2(2.0F)
, appartment_02_2(2.0F)
, appartment_03_2(2.0F)
, largeOfficeBuilding_02_2(2.0F)
, officeTower_01_2(2.0F)
, officeTower_02_2(2.0F)
, smallOffice_01_2(2.0F)
, smallOffice_02_2(2.0F)
, largeOfficeBuilding_01_2(2.0F)

, Building1_01_3(3.0F)
, Building1_02_3(3.0F)
, Building2_01_3(3.0F)
, Building2_02_3(3.0F)
, Building3_01_3(3.0F)
, Building3_02_3(3.0F)
, appartment_01_3(3.0F)
, appartment_02_3(3.0F)
, appartment_03_3(3.0F)
, largeOfficeBuilding_02_3(3.0F)
, officeTower_01_3(3.0F)
, officeTower_02_3(3.0F)
, smallOffice_01_3(3.0F)
, smallOffice_02_3(3.0F)
, largeOfficeBuilding_01_3(3.0F)

{
	
	//InitBuildings();
	
	AddPlacements();
	TranslateBuildings();

	fillLODArray();
}

VModelCity::~VModelCity(void)
{
	
}

void VModelCity::InitBuildings() {
}

void VModelCity::AddPlacements() {

	m_zpNear.AddPlacement(&Building1_01_1);
	m_zpNear.AddPlacement(&Building1_02_1);
	m_zpNear.AddPlacement(&Building2_01_1);
	m_zpNear.AddPlacement(&Building2_02_1);
	m_zpNear.AddPlacement(&Building3_01_1);
	m_zpNear.AddPlacement(&Building3_02_1);
	m_zpNear.AddPlacement(&appartment_01_1);
	m_zpNear.AddPlacement(&appartment_02_1);
	m_zpNear.AddPlacement(&appartment_03_1);
	m_zpNear.AddPlacement(&largeOfficeBuilding_01_1);
	m_zpNear.AddPlacement(&largeOfficeBuilding_02_1);
	m_zpNear.AddPlacement(&officeTower_01_1);
	m_zpNear.AddPlacement(&officeTower_02_1);
	m_zpNear.AddPlacement(&smallOffice_01_1);
	m_zpNear.AddPlacement(&smallOffice_02_1);

	/*m_zpMiddle.AddPlacement(&Building1_01_2);
	m_zpMiddle.AddPlacement(&Building1_02_2);
	m_zpMiddle.AddPlacement(&Building2_01_2);
	m_zpMiddle.AddPlacement(&Building2_02_2);
	m_zpMiddle.AddPlacement(&Building3_01_2);
	m_zpMiddle.AddPlacement(&Building3_02_2);
	m_zpMiddle.AddPlacement(&appartment_01_2);
	m_zpMiddle.AddPlacement(&appartment_02_2);
	m_zpMiddle.AddPlacement(&appartment_03_2);
	m_zpMiddle.AddPlacement(&largeOfficeBuilding_01_2);
	m_zpMiddle.AddPlacement(&largeOfficeBuilding_02_2);
	m_zpMiddle.AddPlacement(&officeTower_01_2);
	m_zpMiddle.AddPlacement(&officeTower_02_2);
	m_zpMiddle.AddPlacement(&smallOffice_01_2);
	m_zpMiddle.AddPlacement(&smallOffice_02_2); */

	//m_zpFar.AddPlacement(&Building1_01_3);
//	m_zpFar.AddPlacement(&Building1_02_3);
//	m_zpFar.AddPlacement(&Building2_01_3);
//	m_zpFar.AddPlacement(&Building2_02_3);
//	m_zpFar.AddPlacement(&Building3_01_3);
//	m_zpFar.AddPlacement(&Building3_02_3);
//	m_zpFar.AddPlacement(&appartment_01_3);
//	m_zpFar.AddPlacement(&appartment_02_3);
//	m_zpFar.AddPlacement(&appartment_03_3);
//	m_zpFar.AddPlacement(&largeOfficeBuilding_01_3);
//	m_zpFar.AddPlacement(&largeOfficeBuilding_02_3);
//	m_zpFar.AddPlacement(&officeTower_01_3);
////	m_zpFar.AddPlacement(&officeTower_02_3);
//	m_zpFar.AddPlacement(&smallOffice_01_3);
//	m_zpFar.AddPlacement(&smallOffice_02_3);


	
	
	

}

void VModelCity::TranslateBuildings() {

	Building1_01_1.Translate(15, 0, 0);
	Building1_02_1.Translate(-15, 0, 7.5);
	Building2_01_1.Translate(0, 0, -10);//-10
	Building2_02_1.Translate(-10, 0, -10);//0
	Building3_01_1.Translate(0, 0, 0);
	Building3_02_1.Translate(-8, 0, 0);
	appartment_01_1.Translate(0, 0, -7.5);
	appartment_02_1.Translate(-10, 0, 15);
	appartment_03_1.Translate(0, 0, -9);
	largeOfficeBuilding_01_1.Translate(-15, 0, 0);
	largeOfficeBuilding_02_1.Translate(10, 0, 15);
	officeTower_01_1.Translate(0, 0, -7.5);
	officeTower_02_1.Translate(-5.0, 0, 5.0);
	smallOffice_01_1.Translate(5.0, 0, 15);
	smallOffice_02_1.Translate(-5.0, 0, -5.0);

}

float VModelCity::getWidth() {
	return 100.0F;
}

float VModelCity::getHeight() {
	return 100.0F;
}

float VModelCity::getBroad() {
	return 100.0F;
}

void VModelCity::fillLODArray() {
	m_zpLOD[0].AddPlacement(&m_zpNear);
	m_zpLOD[1].AddPlacement(&m_zpMiddle);
	m_zpLOD[2].AddPlacement(&m_zpFar);
}
NAMESPACE_VIEW_E
