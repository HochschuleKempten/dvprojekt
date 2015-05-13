#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "LargeOfficeBuilding.h"
#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


class VModelOilRefinery : public IViewModel
{
private:
	
	// Placements

	CPlacement m_zpOelkraftwerk;
	CPlacement m_zpFundament;

	CPlacement m_zpKamin;

	CPlacement m_zpGebaeude1;
	CPlacement m_zpGebaeudeHaelfte11;
	CPlacement m_zpGebaeudeHaelfte12;

	CPlacement m_zpGebaeude2;
	CPlacement m_zpGebaeudeHaelfte21;
	CPlacement m_zpGebaeudeHaelfte22;


	CPlacement m_zpPumpe;
	CPlacement m_zpFundamentPumpe;
	CPlacement m_zpStativ;
	CPlacement m_zpHammer;
	CPlacement m_zpMotor;
	CPlacement m_zpFoerderung;

	CPlacement m_zpStrebe1;
	CPlacement m_zpStrebe2;
	CPlacement m_zpStrebe3;
	CPlacement m_zpStrebe4;
	CPlacement m_zpDrehpunktHammer;
	CPlacement m_zpBalancier;
	CPlacement m_zpKopf;
	CPlacement m_zpKopfspitze;
	CPlacement m_zpPleuel;
	CPlacement m_zpDrehpunktPleuel;
	CPlacement m_zpGetriebe;
	CPlacement m_zpKolbenstange;
	CPlacement m_zpKanal;
	CPlacement m_zpKanalrahmen;
	CPlacement m_zpKopfGesamt;

	CPlacement m_zpAbsperrung;
	CPlacement m_zpPfosten1;
	CPlacement m_zpPfosten2;
	CPlacement m_zpPfosten3;
	CPlacement m_zpPfosten4;
	CPlacement m_zpPfosten5;
	CPlacement m_zpPfosten6;
	CPlacement m_zpPfosten7;
	CPlacement m_zpPfosten8;
	CPlacement m_zpPfosten9;

	CPlacement m_zpHintenOR;
	CPlacement m_zpHintenUR;
	CPlacement m_zpHintenOL;
	CPlacement m_zpHintenUL;
	CPlacement m_zpLinksOH;
	CPlacement m_zpLinksUH;
	CPlacement m_zpLinksOV;
	CPlacement m_zpLinksUV;
	CPlacement m_zpRechtsOH;
	CPlacement m_zpRechtsUH;
	CPlacement m_zpRechtsOV;
	CPlacement m_zpRechtsUV;
	CPlacement m_zpVorneOR;
	CPlacement m_zpVorneUR;
	CPlacement m_zpVorneOL;
	CPlacement m_zpVorneUL;

	CPlacement m_zpDrehelement;
	CPlacement m_zpSchranke;

	//Geo-Objects

	CGeoWall m_zgFundament;
	CGeoTube m_zgKamin;
	CGeoWall m_zgPfosten;
	CGeoWall m_zgBalkenLang;
	CGeoWall m_zgBalkenKurz;
	CGeoCylinder m_zgDrehelement;
	CGeoWall m_zgSchranke;

	CGeoWall m_zgFundamentPumpe;
	CGeoCylinder m_zgStrebe;
	CGeoCylinder m_zgDrehpunktHammer;
	CGeoWall m_zgBalancier;
	CGeoWall m_zgKopf;
	CGeoCube m_zgKopfspitze;
	CGeoCylinder m_zgPleuel;
	CGeoCylinder m_zgDrehpunktPleuel;
	CGeoWall m_zgGetriebe;
	CGeoCylinder m_zgKolbenstange;
	CGeoCylinder m_zgKanal;
	CGeoCylinder m_zgKanalrahmen;



	CLargeOfficeBuilding *Gebaeude = new CLargeOfficeBuilding(0.2f);
	VModelPowerLine m_zTrasse1;
	VModelPowerLine m_zTrasse2;

public:
	VModelOilRefinery();
	virtual ~VModelOilRefinery() override;

	virtual float getHeight() override
	{
		return 5.0f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

};


NAMESPACE_VIEW_E
