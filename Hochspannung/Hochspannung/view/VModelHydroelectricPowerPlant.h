#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "VModelPowerLine.h"
#include "Building02.h"



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
	CPlacement m_zpGebaude;
	CPlacement m_zpRad;
	CPlacement m_zpRad2;
	CPlacement m_zpStange;


	//Geo-Objects

	
	CGeoTube m_zgRad;
	CGeoTube m_zgRad2;
	CGeoCube m_zgSchaufel;
	CGeoCube m_zgFluss;
	CGeoTube m_zgStange;
	
	Building02 Gebaeude;
	//VModelPowerLine m_zTrasse1;
	//VModelPowerLine m_zTrasse2;

public:
	VModelHydroelectricPowerPlant();
	virtual ~VModelHydroelectricPowerPlant() override;

	virtual void init() override;

	void rotate(float ftime){
		m_zpWasserRad.TranslateYDelta(-2.0);
		m_zpWasserRad.TranslateXDelta(1.5);
		m_zpWasserRad.RotateXDelta(-ftime);
		m_zpWasserRad.TranslateYDelta(2.0);
		m_zpWasserRad.TranslateXDelta(-1.5);
	};

	virtual float getHeight() override
	{
		return 4.3f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

	virtual void switchOn() override;
	virtual void switchOff() override;
};


NAMESPACE_VIEW_E
