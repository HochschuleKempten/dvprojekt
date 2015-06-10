#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


class VModelCoalPowerPlant : public IViewModel
{
private:

	// Placements -------------------------------------------------------------------------

	CPlacement m_zpKohlekraftwerk;
	CPlacement m_zpFundament;

	// Gebirge
	CPlacement m_zpGebirge;
	CPlacement m_zpBerg1;
	CPlacement m_zpBerg2;
	CPlacement m_zpBerg3;
	CPlacement m_zpBerg4;
	CPlacement m_zpBerg5;
	CPlacement m_zpBerg6;
	CPlacement m_zpBerg7;
	CPlacement m_zpBerg8;

	//Gleis
	CPlacement m_zpGleis;
	CPlacement m_zpSchieneLinks;
	CPlacement m_zpSchieneRechts;

	//Sprossen
	CPlacement m_zpSprossen[8];

	//Mineneingang
	CPlacement m_zpMineneingang;
	CPlacement m_zpEingangOben;
	CPlacement m_zpEingangRechts;
	CPlacement m_zpEingangLinks;

	//Minenlore
	CPlacement m_zpMinenLore;
	CPlacement m_zpWandLinks;
	CPlacement m_zpWandRechts;
	CPlacement m_zpWandHinten;
	CPlacement m_zpWandVorne;
	CPlacement m_zpBoden;
	CPlacement m_zpRadVorneLinks;
	CPlacement m_zpRadVorneRechts;
	CPlacement m_zpRadHintenLinks;
	CPlacement m_zpRadHintenRechts;
	CPlacement m_zpMinenschacht;

	CPlacement m_zpGebaeude;
	CPlacement m_zpKamin1;
	CPlacement m_zpKamin2;
	CPlacement m_zpKamin3;


	//Geo-Objects --------------------------------------------------------------------------

	CGeoWall m_zgFundament;

	//CAppartments *Gebaeude = new CAppartments(0.2f);
	VModelPowerLine m_zTrasse1;
	VModelPowerLine m_zTrasse2;

	CGeoCone m_zgBerg;
	CGeoWall m_zgSchiene;
	CGeoWall m_zgSprosse;
	CGeoWall m_zgEingangOben;
	CGeoWall m_zgEingangSeite;
	CGeoWall m_zgLoreSeite;
	CGeoWall m_zgLoreVorne;
	CGeoWall m_zgLoreBoden;
	CGeoCylinder m_zgLoreRad;
	CGeoWall m_zgMinenschacht;
	CGeoTube m_zgKamin;

	float absoluteMovement = 0.0f;
	float direction = 1.0f;

public:
	VModelCoalPowerPlant();
	virtual ~VModelCoalPowerPlant() override;

	void init();

	void moveLore(float amount);

	virtual float getHeight() override
	{
		return 4.5f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

	virtual void switchOn() override;
	virtual void switchOff() override;
};


NAMESPACE_VIEW_E
