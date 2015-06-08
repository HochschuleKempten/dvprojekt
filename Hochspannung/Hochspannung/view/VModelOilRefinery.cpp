#include "VModelOilRefinery.h"

NAMESPACE_VIEW_B


VModelOilRefinery::VModelOilRefinery()
{
}

VModelOilRefinery::~VModelOilRefinery()
{}

void VModelOilRefinery::init()
{
	m_zpLOD[0].AddPlacement(&m_zpOelkraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpOelkraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpOelkraftwerk);
	//Initialisierung der Koerper


	//Initialisierung Fundament
	//m_zgFundament.Init(10.0f, 0.3f, 10.0f, &VMaterialLoader::m_zmOelGrund);
	m_zgFoundation.Init(CHVector(5.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmOelGrund);

	//Initialisierung Kamin
	m_zgKamin.InitStraight(0.2f, 0.3f, 4.0f, &VMaterialLoader::m_zmOelGrund, 32, true);

	//Initialisierung Pfosten
	m_zgPfosten.Init(0.2f, 1.1f, 0.2f, &VMaterialLoader::m_zmOelZaun);

	//Initialisierung Balken
	m_zgBalkenLang.Init(4.7f, 0.1f, 0.1f, &VMaterialLoader::m_zmOelZaun);
	m_zgBalkenKurz.Init(3.2f, 0.1f, 0.1f, &VMaterialLoader::m_zmOelZaun);

	//Initialisierung Trassen
	m_zTrasse1.initViewModel(vBuilding);
	m_zTrasse2.initViewModel(vBuilding);
	m_zTrasse1.Init();
	m_zTrasse2.Init();

	//Initialisierung Drehelement
	m_zgDrehelement.Init(0.12f, 0.12f, 0.1f, &VMaterialLoader::m_zmOelGrund, 32, true, true);

	//Initialisierung Schranke
	m_zgSchranke.Init(2.65f, 0.2f, 0.04f, &VMaterialLoader::m_zmOelSchranke);

	//Initialisierung FundamentPumpe
	m_zgFundamentPumpe.Init(1.8f, 0.07f, 1.2f, &VMaterialLoader::m_zmOelGrund);

	//Initialisierung Streben
	m_zgStrebe.Init(0.07f, 0.05f, 2.2f, &VMaterialLoader::m_zmOelGrund, 32, true, true);

	//Initialisierung DrehpunktHammer
	m_zgDrehpunktHammer.Init(0.2f, 0.2f, 0.65f, &VMaterialLoader::m_zmOelGrund, 32, true, true);

	//Initialisierung Balancier
	m_zgBalancier.Init(3.5f, 0.2f, 0.2f, &VMaterialLoader::m_zmOelGruenstahl);

	//Initialisierung Kopf;
	m_zgKopf.Init(0.8f, 0.35f, 0.35f, &VMaterialLoader::m_zmOelGelbstahl);

	//Initialisierung Kopfspitze;
	m_zgKopfspitze.Init(0.155f, &VMaterialLoader::m_zmOelGelbstahl);

	//Initialisierung Kolbenstange;
	m_zgKolbenstange.Init(0.03f, 0.03f, 1.8f, &VMaterialLoader::m_zmOelGrund, 32, true, true);

	//Initialisierung Kanal;
	m_zgKanal.Init(0.07f, 0.07f, 0.5f, &VMaterialLoader::m_zmOelGruenstahl, 32, true, true);

	//Initialisierung Kanalrahmen;
	m_zgKanalrahmen.Init(0.09f, 0.09f, 0.02f, &VMaterialLoader::m_zmOelGruenstahl, 32, true, true);

	//Initialisierung Pleuel;
	m_zgPleuel.Init(0.03f, 0.03f, 1.2f, &VMaterialLoader::m_zmOelGrund, 32, true, true);

	//Initialisierung Motor
	m_zgGetriebe.Init(0.6f, 0.6f, 0.6f, &VMaterialLoader::m_zmOelGrund);

	//Initialisierung DrehpunktPleuel
	m_zgDrehpunktPleuel.Init(0.15f, 0.15f, 0.3f, &VMaterialLoader::m_zmOelGrund, 32, true, true);





	//Placements
	m_zpLOD[0].AddPlacement(&m_zpOelkraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpOelkraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpOelkraftwerk);
	m_zpMain.AddPlacement(&m_zpOelkraftwerk);
	m_zpOelkraftwerk.AddPlacement(&m_zpFundament);
	m_zpOelkraftwerk.AddPlacement(&m_zpKamin);
	m_zpOelkraftwerk.AddPlacement(m_zTrasse1.getMainPlacement());
	m_zpOelkraftwerk.AddPlacement(m_zTrasse2.getMainPlacement());
	//m_zpOelkraftwerk.AddPlacement(&m_zpGebaeude1);
	//m_zpOelkraftwerk.AddPlacement(&m_zpGebaeude2);
	m_zpOelkraftwerk.AddPlacement(&m_zpAbsperrung);
	m_zpOelkraftwerk.AddPlacement(&m_zpPumpe);

	m_zpPumpe.AddPlacement(&m_zpFundamentPumpe);
	m_zpPumpe.AddPlacement(&m_zpStativ);
	m_zpPumpe.AddPlacement(&m_zpHammer);
	m_zpPumpe.AddPlacement(&m_zpMotor);
	m_zpPumpe.AddPlacement(&m_zpFoerderung);


	m_zpStativ.AddPlacement(&m_zpStrebe1);
	m_zpStativ.AddPlacement(&m_zpStrebe2);
	m_zpStativ.AddPlacement(&m_zpStrebe3);
	m_zpStativ.AddPlacement(&m_zpStrebe4);
	m_zpStativ.AddPlacement(&m_zpDrehpunktHammer);

	m_zpHammer.AddPlacement(&m_zpBalancier);
	m_zpHammer.AddPlacement(&m_zpKopfGesamt);

	m_zpKopfGesamt.AddPlacement(&m_zpKopf);
	m_zpKopfGesamt.AddPlacement(&m_zpKopfspitze);

	m_zpMotor.AddPlacement(&m_zpGetriebe);
	m_zpMotor.AddPlacement(&m_zpPleuel);
	m_zpMotor.AddPlacement(&m_zpDrehpunktPleuel);

	m_zpFoerderung.AddPlacement(&m_zpKolbenstange);
	m_zpFoerderung.AddPlacement(&m_zpKanal);
	m_zpFoerderung.AddPlacement(&m_zpKanalrahmen);

	m_zpAbsperrung.AddPlacement(&m_zpPfosten1);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten2);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten3);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten4);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten5);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten6);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten7);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten8);
	m_zpAbsperrung.AddPlacement(&m_zpPfosten9);

	m_zpAbsperrung.AddPlacement(&m_zpHintenOR);
	m_zpAbsperrung.AddPlacement(&m_zpHintenOL);
	m_zpAbsperrung.AddPlacement(&m_zpHintenUR);
	m_zpAbsperrung.AddPlacement(&m_zpHintenUL);
	m_zpAbsperrung.AddPlacement(&m_zpLinksOH);
	m_zpAbsperrung.AddPlacement(&m_zpLinksUH);
	m_zpAbsperrung.AddPlacement(&m_zpLinksOV);
	m_zpAbsperrung.AddPlacement(&m_zpLinksUV);
	m_zpAbsperrung.AddPlacement(&m_zpRechtsOH);
	m_zpAbsperrung.AddPlacement(&m_zpRechtsUH);
	m_zpAbsperrung.AddPlacement(&m_zpRechtsOV);
	m_zpAbsperrung.AddPlacement(&m_zpRechtsUV);
	m_zpAbsperrung.AddPlacement(&m_zpVorneOR);
	m_zpAbsperrung.AddPlacement(&m_zpVorneOL);
	m_zpAbsperrung.AddPlacement(&m_zpVorneUR);
	m_zpAbsperrung.AddPlacement(&m_zpVorneUL);
	m_zpAbsperrung.AddPlacement(&m_zpDrehelement);
	m_zpAbsperrung.AddPlacement(&m_zpSchranke);

	/*
	m_zpGebaeude1.AddPlacement(&m_zpGebaeudeHaelfte11);
	//	m_zpGebaeudeHaelfte11.AddPlacement(Gebaeude);
	m_zpGebaeude1.AddPlacement(&m_zpGebaeudeHaelfte12);
	//m_zpGebaeudeHaelfte12.AddPlacement(Gebaeude);
	m_zpGebaeude2.AddPlacement(&m_zpGebaeudeHaelfte21);
	//m_zpGebaeudeHaelfte21.AddPlacement(Gebaeude);
	m_zpGebaeude2.AddPlacement(&m_zpGebaeudeHaelfte22);
	m_zpGebaeudeHaelfte22.AddPlacement(Gebaeude);
	*/

	//Adding
	//m_zpFundament.Translate(CHVector(-5.0f, 0.0f, -5.0f));
	m_zpFundament.AddGeo(&m_zgFoundation);

	m_zpKamin.Translate(CHVector(2.5f, 2.15f, 2.0f));
	m_zpKamin.AddGeo(&m_zgKamin);

	m_zpGebaeude1.Translate(CHVector(-1.0f, 0.15f, 0.3f));
	m_zpGebaeudeHaelfte11.Translate(CHVector(1.0f, 0.15f, 2.0f));
	m_zpGebaeudeHaelfte12.TranslateDelta(CHVector(-1.0f, 0.15f, -1.0f));
	m_zpGebaeudeHaelfte12.RotateYDelta(PI);

	m_zpGebaeude2.Translate(CHVector(-2.8f, 0.15f, -3.8f));
	m_zpGebaeude2.RotateYDelta(0.5 * PI);
	m_zpGebaeudeHaelfte21.Translate(CHVector(1.0f, 0.15f, 1.6f));
	m_zpGebaeudeHaelfte22.TranslateDelta(CHVector(-1.0f, 0.15f, -0.6f));
	m_zpGebaeudeHaelfte22.RotateYDelta(PI);

	m_zTrasse1.getMainPlacement()->Translate(CHVector(-3.0f, 0.35f, 3.5f));
	m_zTrasse2.getMainPlacement()->Translate(CHVector(3.0f, 0.35f, 3.5f));

	m_zpFundamentPumpe.Translate(CHVector(0.35f, 0.3f, -2.85f));
	m_zpFundamentPumpe.AddGeo(&m_zgFundamentPumpe);

	m_zpStrebe1.RotateZDelta(-0.1*PI);
	m_zpStrebe1.TranslateDelta(CHVector(0.5f, 0.15f, -2.0f));
	m_zpStrebe1.AddGeo(&m_zgStrebe);
	m_zpStrebe2.RotateZDelta(-0.1*PI);
	m_zpStrebe2.TranslateDelta(CHVector(0.5f, 0.15f, -2.5f));
	m_zpStrebe2.AddGeo(&m_zgStrebe);
	m_zpStrebe3.RotateZDelta(0.1*PI);
	m_zpStrebe3.TranslateDelta(CHVector(2.0f, 0.15f, -2.0f));
	m_zpStrebe3.AddGeo(&m_zgStrebe);
	m_zpStrebe4.RotateZDelta(0.1*PI);
	m_zpStrebe4.TranslateDelta(CHVector(2.0f, 0.15f, -2.5f));
	m_zpStrebe4.AddGeo(&m_zgStrebe);

	m_zpDrehpunktHammer.RotateXDelta(HALFPI);
	m_zpDrehpunktHammer.TranslateDelta(CHVector(1.25f, 2.2f, -2.575f));
	m_zpDrehpunktHammer.AddGeo(&m_zgDrehpunktHammer);

	m_zpBalancier.RotateZDelta(-0.08f * PI);
	m_zpBalancier.TranslateDelta(CHVector(-0.35f, 2.52f, -2.35f));
	m_zpBalancier.AddGeo(&m_zgBalancier);

	m_zpKopfGesamt.Translate(CHVector(0.45f, -0.3f, 0.0f));
	m_zpKopf.RotateZDelta(0.42f * PI);
	m_zpKopf.TranslateDelta(CHVector(-0.85f, 2.6f, -2.425f));
	m_zpKopf.AddGeo(&m_zgKopf);

	m_zgKopfspitze.TaperX(0.85f, true, true, true);
	m_zpKopfspitze.RotateZDelta(0.42f * PI);
	m_zpKopfspitze.TranslateDelta(CHVector(-1.062f, 2.48f, -2.25f));
	m_zpKopfspitze.AddGeo(&m_zgKopfspitze);

	m_zpKolbenstange.Translate(CHVector(-0.65f, 0.3f, -2.25f));
	m_zpKolbenstange.AddGeo(&m_zgKolbenstange);

	m_zpKanal.Translate(CHVector(-0.65f, 0.3f, -2.25f));
	m_zpKanal.AddGeo(&m_zgKanal);

	m_zpKanalrahmen.Translate(CHVector(-0.65f, 0.8f, -2.25f));
	m_zpKanalrahmen.AddGeo(&m_zgKanalrahmen);

	m_zpPleuel.Translate(CHVector(2.97f, 0.6f, -2.25f));
	m_zpPleuel.AddGeo(&m_zgPleuel);

	m_zpGetriebe.Translate(CHVector(2.67f, 0.15f, -2.55f));
	m_zpGetriebe.AddGeo(&m_zgGetriebe);

	m_zpDrehpunktPleuel.RotateXDelta(HALFPI);
	m_zpDrehpunktPleuel.TranslateDelta(CHVector(2.97f, 0.75f, -2.4f));
	m_zpDrehpunktPleuel.AddGeo(&m_zgDrehpunktPleuel);

	m_zpPumpe.ScaleDelta(2.0);
	m_zpPumpe.TranslateYDelta(-0.35);
	m_zpPumpe.TranslateXDelta(-2.5);
	m_zpPumpe.TranslateZDelta(2.0);

	m_zpPfosten1.Translate(CHVector(-1.6f, 0.15f, 4.8f));
	m_zpPfosten1.AddGeo(&m_zgPfosten);
	m_zpPfosten2.Translate(CHVector(-5.0f, 0.15f, 4.8f));
	m_zpPfosten2.AddGeo(&m_zgPfosten);
	m_zpPfosten2.Translate(CHVector(-5.0f, 0.15f, 4.8f));
	m_zpPfosten2.AddGeo(&m_zgPfosten);
	m_zpPfosten2.Translate(CHVector(-5.0f, 0.15f, 4.8f));
	m_zpPfosten2.AddGeo(&m_zgPfosten);
	m_zpPfosten3.Translate(CHVector(-5.0f, 0.15f, -0.1f));
	m_zpPfosten3.AddGeo(&m_zgPfosten);
	m_zpPfosten4.Translate(CHVector(-5.0f, 0.15f, -5.0f));
	m_zpPfosten4.AddGeo(&m_zgPfosten);
	m_zpPfosten5.Translate(CHVector(-0.1f, 0.15f, -5.0f));
	m_zpPfosten5.AddGeo(&m_zgPfosten);
	m_zpPfosten6.Translate(CHVector(4.8f, 0.15f, -5.0f));
	m_zpPfosten6.AddGeo(&m_zgPfosten);
	m_zpPfosten7.Translate(CHVector(4.8f, 0.15f, -0.1f));
	m_zpPfosten7.AddGeo(&m_zgPfosten);
	m_zpPfosten8.Translate(CHVector(4.8f, 0.15f, 4.8f));
	m_zpPfosten8.AddGeo(&m_zgPfosten);
	m_zpPfosten9.Translate(CHVector(1.4f, 0.15f, 4.8f));
	m_zpPfosten9.AddGeo(&m_zgPfosten);

	m_zpHintenUL.Translate(CHVector(-4.8f, 0.55f, -4.95f));
	m_zpHintenUL.AddGeo(&m_zgBalkenLang);
	m_zpHintenOL.Translate(CHVector(-4.8f, 0.95f, -4.95f));
	m_zpHintenOL.AddGeo(&m_zgBalkenLang);
	m_zpHintenUR.Translate(CHVector(0.1f, 0.55f, -4.95f));
	m_zpHintenUR.AddGeo(&m_zgBalkenLang);
	m_zpHintenOR.Translate(CHVector(0.1f, 0.95f, -4.95f));
	m_zpHintenOR.AddGeo(&m_zgBalkenLang);

	m_zpLinksUV.Translate(CHVector(-4.8f, 0.55f, -4.95f));
	m_zpLinksUV.RotateYDelta(0.5*PI);
	m_zpLinksUV.AddGeo(&m_zgBalkenLang);
	m_zpLinksUH.Translate(CHVector(0.1f, 0.55f, -4.95f));
	m_zpLinksUH.RotateYDelta(0.5*PI);
	m_zpLinksUH.AddGeo(&m_zgBalkenLang);
	m_zpLinksOV.Translate(CHVector(-4.8f, 0.95f, -4.95f));
	m_zpLinksOV.RotateYDelta(0.5*PI);
	m_zpLinksOV.AddGeo(&m_zgBalkenLang);
	m_zpLinksOH.Translate(CHVector(0.1f, 0.95f, -4.95f));
	m_zpLinksOH.RotateYDelta(0.5*PI);
	m_zpLinksOH.AddGeo(&m_zgBalkenLang);

	m_zpRechtsUV.Translate(CHVector(-4.8f, 0.55f, -4.95f));
	m_zpRechtsUV.RotateYDelta(-0.5*PI);
	m_zpRechtsUV.AddGeo(&m_zgBalkenLang);
	m_zpRechtsUH.Translate(CHVector(0.1f, 0.55f, -4.95f));
	m_zpRechtsUH.RotateYDelta(-0.5*PI);
	m_zpRechtsUH.AddGeo(&m_zgBalkenLang);
	m_zpRechtsOV.Translate(CHVector(-4.8f, 0.95f, -4.95f));
	m_zpRechtsOV.RotateYDelta(-0.5*PI);
	m_zpRechtsOV.AddGeo(&m_zgBalkenLang);
	m_zpRechtsOH.Translate(CHVector(0.1f, 0.95f, -4.95f));
	m_zpRechtsOH.RotateYDelta(-0.5*PI);
	m_zpRechtsOH.AddGeo(&m_zgBalkenLang);

	m_zpVorneUL.Translate(CHVector(-4.8f, 0.55f, 4.85f));
	m_zpVorneUL.AddGeo(&m_zgBalkenKurz);
	m_zpVorneOL.Translate(CHVector(-4.8f, 0.95f, 4.85f));
	m_zpVorneOL.AddGeo(&m_zgBalkenKurz);
	m_zpVorneUR.Translate(CHVector(1.6f, 0.55f, 4.85f));
	m_zpVorneUR.AddGeo(&m_zgBalkenKurz);
	m_zpVorneOR.Translate(CHVector(1.6f, 0.95f, 4.85f));
	m_zpVorneOR.AddGeo(&m_zgBalkenKurz);

	m_zpDrehelement.Translate(CHVector(-1.4f, -4.95f, 0.8f));
	m_zpDrehelement.RotateXDelta(-0.5*PI);
	m_zpDrehelement.AddGeo(&m_zgDrehelement);

	m_zpSchranke.Translate(CHVector(-0.7f, 1.36f, 4.875f));
	m_zpSchranke.RotateZDelta(0.2*PI);
	m_zpSchranke.AddGeo(&m_zgSchranke);
}

NAMESPACE_VIEW_E
