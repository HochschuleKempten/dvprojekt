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

	gebaeude1_01 = new Gebauede01;
	gebaeude1_02 = new Gebauede01;
	gebaeude2_01 = new Gebaeude02;
	gebaeude2_02 = new Gebaeude02;
	gebaeude3_01 = new Gebaeude03;
	gebaeude3_02 = new Gebaeude03;
	appartment_01 = new CAppartments(1.0F);
	appartment_02 = new CAppartments(1.0F);
	appartment_03 = new CAppartments(1.0F);
	largeOfficeBuilding_01 = new CLargeOfficeBuilding(1.0F);
	largeOfficeBuilding_02 = new CLargeOfficeBuilding(1.0F);
	officeTower_01 = new COfficeTowerViewingDeck(0.5F);
	officeTower_02 = new COfficeTowerViewingDeck(0.4F);
	smallOffice_01 = new CSmallOfficeBuilding(0.8F);
	smallOffice_02 = new CSmallOfficeBuilding(0.8F);

}



void VModelCity::AddPlacements() {

	AddPlacement(gebaeude1_01);
	AddPlacement(gebaeude1_02);
	AddPlacement(gebaeude2_01);
	AddPlacement(gebaeude2_02);
	AddPlacement(gebaeude3_01);
	AddPlacement(gebaeude3_02);
	AddPlacement(appartment_01);
	AddPlacement(appartment_02);
	AddPlacement(appartment_03);
	AddPlacement(largeOfficeBuilding_01);
	AddPlacement(largeOfficeBuilding_02);
	AddPlacement(officeTower_01);
	AddPlacement(officeTower_02);
	AddPlacement(smallOffice_01);
	AddPlacement(smallOffice_02);

}
void VModelCity::TranslateBuildings() {

	gebaeude1_01->Translate(15, 0, 0);
	gebaeude1_02->Translate(-15, 0, 7.5);
	gebaeude2_01->Translate(-10, 0, 0);
	gebaeude2_02->Translate(0, 0, 7.5);
	gebaeude3_01->Translate(0, 0, 0);
	gebaeude3_01->Translate(20, 0, 0);
	appartment_01->Translate(0, 0, -7.5);
	appartment_02->Translate(-10, 0, 15);
	appartment_03->Translate(0, 0, -9);
	largeOfficeBuilding_01->Translate(-15, 0, 0);
	largeOfficeBuilding_02->Translate(10, 0, 15);
	officeTower_01->Translate(0, 0, -7.5);
	officeTower_02->Translate(-5.0, 0, 5.0);
	smallOffice_01->Translate(5.0, 0, 15);
	smallOffice_02->Translate(-5.0, 0, -5.0);

}


NAMESPACE_VIEW_E
