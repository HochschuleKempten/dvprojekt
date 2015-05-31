#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "LargeOfficeBuilding.h"
#include "VModelPowerLine.h"


NAMESPACE_VIEW_B


class VModelHydroelectricPowerPlant : public IViewModel
{
private:

	// Placements

	CPlacement m_zpWasserKraftwerk;
	CPlacement m_zpWasserRad;
	CPlacement m_zpWasserSchaufel1;
	CPlacement m_zpWasserSchaufel2;
	CPlacement m_zpWasserSchaufel3;
	CPlacement m_zpWasserSchaufel4;
	CPlacement m_zpWasserSchaufel5;
	CPlacement m_zpWasserSchaufel6;
	CPlacement m_zpHaus;
	CPlacement m_zpFluss;
	CPlacement m_zpPowerline;
	CPlacement m_zpFundament;
	//CPlacement m_zpGebaude;
	CPlacement m_zpRad;


	//Geo-Objects

	
	CGeoTube m_zgRad;
	CGeoCube m_zgSchaufel;
	CGeoCube m_zgFluss;



	//CLargeOfficeBuilding *Gebaeude = new CLargeOfficeBuilding(0.2f);
	//VModelPowerLine m_zTrasse1;
	//VModelPowerLine m_zTrasse2;
	//CLargeOfficeBuilding Gebaeude;



public:
	VModelHydroelectricPowerPlant();
	virtual ~VModelHydroelectricPowerPlant() override;

	void rotate(float ftime){
		m_zpWasserRad.TranslateYDelta(-3.5);
		m_zpWasserRad.TranslateXDelta(2.5);
		m_zpWasserRad.RotateXDelta(ftime);
		m_zpWasserRad.TranslateYDelta(3.5);
		m_zpWasserRad.TranslateXDelta(-2.5);
	};

	virtual float getHeight() override
	{
		return 4.3f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

};


NAMESPACE_VIEW_E
