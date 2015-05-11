#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "LargeOfficeBuilding.h"
#include "VModelPowerLine.h"


NAMESPACE_VIEW_B


class VModelNuclearPowerPlant : public IViewModel
{
private:

	// Placements

	CPlacement m_zpAtomkraftwerk;
	CPlacement m_zpFundament;
	CPlacement m_zpKuehlturm1;
	CPlacement m_zpKuehlturm2;

	CPlacement m_zpReaktor1;
	CPlacement m_zpReaktor2;
	CPlacement m_zpReaktorTurm1;
	CPlacement m_zpReaktorTurm2;
	CPlacement m_zpReaktorKopf1;
	CPlacement m_zpReaktorKopf2;

	CPlacement m_zpKamin;

	CPlacement m_zpGebaeude1;
	CPlacement m_zpGebaeudeHaelfte11;
	CPlacement m_zpGebaeudeHaelfte12;

	CPlacement m_zpGebaeude2;
	CPlacement m_zpGebaeudeHaelfte21;
	CPlacement m_zpGebaeudeHaelfte22;

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

	CPlacement m_zgFundament;
	CGeoWall m_zgKuehlturm;
	CGeoTube m_zgReaktorTurm;
	CGeoSphere m_zgReaktorKopf;
	CGeoTube m_zgKamin;
	CGeoWall m_zgPfosten;
	CGeoWall m_zgBalkenLang;
	CGeoWall m_zgBalkenKurz;
	CGeoCylinder m_zgDrehelement;
	CGeoWall m_zgSchranke;



	CLargeOfficeBuilding *Gebaeude = new CLargeOfficeBuilding(0.2f);
	VModelPowerLine m_zTrasse1;
	VModelPowerLine m_zTrasse2;



public:
	VModelNuclearPowerPlant();
	virtual ~VModelNuclearPowerPlant() override;

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
