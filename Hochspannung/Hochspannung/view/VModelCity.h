#pragma once

#include "VGeneral.h"
#include "Building01.h"
#include "Building02.h"
#include "Building03.h"
#include "Appartments.h"
#include "LargeOfficeBuilding.h"
#include "SmallOfficeBuilding.h"
#include "OfficeTowerViewingDeck.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


class VModelCity : public IViewModel
{
public:
	VModelCity(void);
	virtual ~VModelCity(void) override;

	void TranslateBuildings();
	void InitBuildings();
	void AddPlacements();
	
	//TODO (City) implement these methods
	virtual float getHeight() override;
	virtual float getWidth() override;
	virtual float getBroad();

	void fillLODArray();

private:
	
	//lodstufe1
	Building01 Building1_01_1;
	Building01 Building1_02_1;
	Building02 Building2_01_1;
	Building02 Building2_02_1;
	Building03 Building3_01_1;
	Building03 Building3_02_1;

	CAppartments appartment_01_1;
	CAppartments appartment_02_1;
	CAppartments appartment_03_1;

	CLargeOfficeBuilding largeOfficeBuilding_01_1;
	CLargeOfficeBuilding largeOfficeBuilding_02_1;
	COfficeTowerViewingDeck officeTower_01_1;
	COfficeTowerViewingDeck officeTower_02_1;
	CSmallOfficeBuilding smallOffice_01_1;
	CSmallOfficeBuilding smallOffice_02_1;

	//lodstufe2
	Building01 Building1_01_2;
	Building01 Building1_02_2;
	Building02 Building2_01_2;
	Building02 Building2_02_2;
	Building03 Building3_01_2;
	Building03 Building3_02_2;

	CAppartments appartment_01_2;
	CAppartments appartment_02_2;
	CAppartments appartment_03_2;

	CLargeOfficeBuilding largeOfficeBuilding_01_2;
	CLargeOfficeBuilding largeOfficeBuilding_02_2;
	COfficeTowerViewingDeck officeTower_01_2;
	COfficeTowerViewingDeck officeTower_02_2;
	CSmallOfficeBuilding smallOffice_01_2;
	CSmallOfficeBuilding smallOffice_02_2;

	//lodstufe3
	Building01 Building1_01_3;
	Building01 Building1_02_3;
	Building02 Building2_01_3;
	Building02 Building2_02_3;
	Building03 Building3_01_3;
	Building03 Building3_02_3;

	CAppartments appartment_01_3;
	CAppartments appartment_02_3;
	CAppartments appartment_03_3;

	CLargeOfficeBuilding largeOfficeBuilding_01_3;
	CLargeOfficeBuilding largeOfficeBuilding_02_3;
	COfficeTowerViewingDeck officeTower_01_3;
	COfficeTowerViewingDeck officeTower_02_3;
	CSmallOfficeBuilding smallOffice_01_3;
	CSmallOfficeBuilding smallOffice_02_3;


	//PlacementsLods
	CPlacement m_zpNear;
	CPlacement m_zpMiddle;
	CPlacement m_zpFar;
};


NAMESPACE_VIEW_E
