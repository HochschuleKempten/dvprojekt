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
	virtual float getHeight() override
	{
		return 0.0f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

private:
	Building01* Building1_01;
	Building01* Building1_02;
	Building02* Building2_01;
	Building02* Building2_02;
	Building03* Building3_01;
	Building03* Building3_02;
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
