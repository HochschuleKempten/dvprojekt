#pragma once

#include "VGeneral.h"
#include "Gebauede01.h"
#include "Gebaeude02.h"
#include "Gebaeude03.h"
#include "Appartments.h"
#include "LargeOfficeBuilding.h"
#include "SmallOfficeBuilding.h"
#include "OfficeTowerViewingDeck.h"
#include "TwistedTower.h"

NAMESPACE_VIEW_B


class VModelCity : public CPlacement
{
public:
	VModelCity(void);
	~VModelCity(void);

	void TranslateBuildings();
	void InitBuildings();
	void AddPlacements();
	

private:

	
	
	Gebauede01* gebaeude1_01;
	Gebauede01* gebaeude1_02;
	Gebaeude02* gebaeude2_01;
	Gebaeude02* gebaeude2_02;
	Gebaeude03* gebaeude3_01;
	Gebaeude03* gebaeude3_02;
	CAppartments* appartment_01;
	CAppartments* appartment_02;
	CAppartments* appartment_03;
	CLargeOfficeBuilding* largeOfficeBuilding_01;
	CLargeOfficeBuilding* largeOfficeBuilding_02;
	COfficeTowerViewingDeck* officeTower_01;
	COfficeTowerViewingDeck* officeTower_02;
	CSmallOfficeBuilding* smallOffice_01;
	CSmallOfficeBuilding* smallOffice_02;
};


NAMESPACE_VIEW_E
