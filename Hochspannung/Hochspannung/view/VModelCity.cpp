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
, largeOfficeBuilding_01_1(1.0F)
, largeOfficeBuilding_02_1(1.0F)
, officeTower_01_1(1.0F)
, officeTower_02_1(1.0F)
, smallOffice_01_1(1.0F)
, smallOffice_02_1(1.0F)

, Building1_01_2(2.0F)
, Building1_02_2(2.0F)
, Building2_01_2(2.0F)
, Building2_02_2(2.0F)
, Building3_01_2(2.0F)
, Building3_02_2(2.0F)
, appartment_01_2(2.0F)
, appartment_02_2(2.0F)
, appartment_03_2(2.0F)
, largeOfficeBuilding_01_2(2.0F)
, largeOfficeBuilding_02_2(2.0F)
, officeTower_01_2(2.0F)
, officeTower_02_2(2.0F)
, smallOffice_01_2(2.0F)
, smallOffice_02_2(2.0F)


//Bei Lod stufe 3 werden ein paar Gebäude ausgeblendet
, Building1_01_3(3.0F)
, Building1_02_3(3.0F)
, Building2_01_3(3.0F)
, Building2_02_3(3.0F)
, Building3_01_3(3.0F)
, Building3_02_3(3.0F)
, appartment_01_3(3.0F)
, appartment_02_3(3.0F)
, appartment_03_3(3.0F)
, largeOfficeBuilding_01_3(3.0F)
, largeOfficeBuilding_02_3(3.0F)
, officeTower_01_3(3.0F)
, officeTower_02_3(3.0F)
, smallOffice_01_3(3.0F)
, smallOffice_02_3(3.0F)

{
	//InitBuildings();
	
	AddPlacements();
	TranslateBuildings();

	fillLODArray();
}

VModelCity::~VModelCity(void)
{
	
}

void VModelCity::init()
{
	Building2_01_1.initViewModel(vBuilding, switchedState);
	Building2_01_1.Init();
	Building2_02_1.initViewModel(vBuilding, switchedState);
	Building2_02_1.Init();

	Building2_01_2.initViewModel(vBuilding, switchedState);
	Building2_01_2.Init();
	Building2_02_2.initViewModel(vBuilding, switchedState);
	Building2_02_2.Init();

	Building2_01_3.initViewModel(vBuilding, switchedState);
	Building2_01_3.Init();
	Building2_02_3.initViewModel(vBuilding, switchedState);
	Building2_02_3.Init();

	appartment_01_1.initViewModel(vBuilding, switchedState);
	appartment_01_1.Init();
	appartment_02_1.initViewModel(vBuilding, switchedState);
	appartment_02_1.Init();
	appartment_03_1.initViewModel(vBuilding, switchedState);
	appartment_03_1.Init();

	appartment_01_2.initViewModel(vBuilding, switchedState);
	appartment_01_2.Init();
	appartment_02_2.initViewModel(vBuilding, switchedState);
	appartment_02_2.Init();
	appartment_03_2.initViewModel(vBuilding, switchedState);
	appartment_03_2.Init();

	appartment_01_3.initViewModel(vBuilding, switchedState);
	appartment_01_3.Init();
	appartment_02_3.initViewModel(vBuilding, switchedState);
	appartment_02_3.Init();
	appartment_03_3.initViewModel(vBuilding, switchedState);
	appartment_03_3.Init();

	largeOfficeBuilding_01_1.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_01_1.Init();
	largeOfficeBuilding_02_1.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_02_1.Init();

	largeOfficeBuilding_01_2.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_01_2.Init();
	largeOfficeBuilding_02_2.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_02_2.Init();

	largeOfficeBuilding_01_3.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_01_3.Init();
	largeOfficeBuilding_02_3.initViewModel(vBuilding, switchedState);
	largeOfficeBuilding_02_3.Init();
}

void VModelCity::InitBuildings() {
}

void VModelCity::AddPlacements() {

	m_zpNear.AddPlacement(&m_zpFundament);
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

	m_zpMiddle.AddPlacement(&m_zpFundament);
	m_zpMiddle.AddPlacement(&Building1_01_2);
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
	m_zpMiddle.AddPlacement(&smallOffice_02_2);

	m_zpFar.AddPlacement(&m_zpFundament);
	m_zpFar.AddPlacement(&Building1_01_3);
	m_zpFar.AddPlacement(&Building1_02_3);
	m_zpFar.AddPlacement(&Building2_01_3);
	m_zpFar.AddPlacement(&Building2_02_3);
	m_zpFar.AddPlacement(&Building3_01_3);
	m_zpFar.AddPlacement(&Building3_02_3);
	m_zpFar.AddPlacement(&appartment_01_3);
	m_zpFar.AddPlacement(&appartment_02_3);
	m_zpFar.AddPlacement(&appartment_03_3);
	m_zpFar.AddPlacement(&largeOfficeBuilding_01_3);
	m_zpFar.AddPlacement(&largeOfficeBuilding_02_3);
	m_zpFar.AddPlacement(&officeTower_01_3);
	m_zpFar.AddPlacement(&officeTower_02_3);
	m_zpFar.AddPlacement(&smallOffice_01_3);
	m_zpFar.AddPlacement(&smallOffice_02_3);
	

	
	
	

}

void VModelCity::TranslateBuildings() {

	Building1_01_1.Translate(-15.0, 0.0, 12.0);
	Building1_02_1.Translate(15.0, 0.0, -15.0);
	Building2_01_1.Translate(-15.0, 0.0, -4.0);//-10
	Building2_02_1.Translate(-8.0, 0.0, -15.0);//0
	Building3_01_1.Translate(-1.0, 0.0, -12.0);
	Building3_02_1.Translate(-15.0, 0.0, -15.0);

	appartment_01_1.Translate(-1.5, 0.0, 5.0);
	appartment_02_1.Translate(1.5, 0.0, -5.0);
	appartment_03_1.Translate(0.0, 0.0, 0.0);
	largeOfficeBuilding_01_1.Translate(-8.0, 0.0, 0.0);
	largeOfficeBuilding_02_1.Translate(-15.0, 0.0, 5.0);

	officeTower_01_1.Translate(-8.0, 0.0, 15.0);
	officeTower_02_1.Translate(6.0, 0.0, 15.0);
	smallOffice_01_1.Translate(-2.0, 0.0, 15.0);
	smallOffice_02_1.Translate(14.0, 0.0, 15.0);



	Building1_01_2.Translate(-15.0, 0.0, 12.0);
	Building1_02_2.Translate(15.0, 0.0, -15.0);
	Building2_01_2.Translate(-15, 0.0, -4.0);//-10
	Building2_02_2.Translate(-8.0, 0.0, -15.0);//0
	Building3_01_2.Translate(-1.0, 0.0, -12.0);
	Building3_02_2.Translate(-15.0, 0.0, -15.0);

	appartment_01_2.Translate(-1.5, 0.0, 5.0);
	appartment_02_2.Translate(1.5, 0.0, -5.0);
	appartment_03_2.Translate(0.0, 0.0, 0.0);
	largeOfficeBuilding_01_2.Translate(-8.0, 0.0, 0.0);
	largeOfficeBuilding_02_2.Translate(-15.0, 0.0, 5.0);

	officeTower_01_2.Translate(-8.0, 0.0, 15.0);
	officeTower_02_2.Translate(6.0, 0.0, 15.0);
	smallOffice_01_2.Translate(-2.0, 0.0, 15.0);
	smallOffice_02_2.Translate(14.0, 0.0, 15.0);


	Building1_01_3.Translate(-15.0, 0.0, 12.0);
	Building1_02_3.Translate(15.0, 0.0, -15.0);
	Building2_01_3.Translate(-15.0, 0.0, -4.0);//-10
	Building2_02_3.Translate(-8.0, 0.0, -15.0);//0
	Building3_01_3.Translate(-1.0, 0.0, -12.0);
	Building3_02_3.Translate(-15.0, 0.0, -15.0);

	appartment_01_3.Translate(-1.5, 0.0, 5.0);
	appartment_02_3.Translate(1.5, 0.0, -5.0);
	appartment_03_3.Translate(0.0, 0.0, 0.0);
	largeOfficeBuilding_01_3.Translate(-8.0, 0.0, 0.0);
	largeOfficeBuilding_02_3.Translate(-15.0, 0.0,5.0);

	officeTower_01_3.Translate(-8.0, 0.0, 15.0);
	officeTower_02_3.Translate(6.0, 0.0, 15.0);
	smallOffice_01_3.Translate(-2.0, 0.0, 15.0);
	smallOffice_02_3.Translate(14.0, 0.0, 15.0);

	m_zpFundament.AddGeo(&m_zgFoundation);
	m_zpFundament.ScaleXDelta(50.0f);
	m_zpFundament.ScaleZDelta(50.0f);
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
