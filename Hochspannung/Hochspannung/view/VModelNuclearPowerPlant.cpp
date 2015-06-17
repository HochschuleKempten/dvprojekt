#include "VModelNuclearPowerPlant.h"

NAMESPACE_VIEW_B


VModelNuclearPowerPlant::VModelNuclearPowerPlant()
{}

VModelNuclearPowerPlant::~VModelNuclearPowerPlant()
{}

void VModelNuclearPowerPlant::init()
{
	m_zpLOD[0].AddPlacement(&m_zpAtomkraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpAtomkraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpAtomkraftwerk);

	//Initialisierung Kuehlturm
	m_zgKuehlturm.InitTubeWave(1.2f, 4.0f, 0.2f, 0.1f, 3.5f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FLOOR, switchedState), 0.2f, true, true);

	//Initialisierung Reaktorturm
	m_zgReaktorTurm.InitStraight(0.6f, 0.6f, 1.2f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_REACTOR, switchedState), 32);

	//Initialisierung Reaktorkopf
	m_zgReaktorKopf.Init(0.6f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_REACTOR, switchedState), 32, 32);

	//Initialisierung Kamin
	m_zgKamin.InitStraight(0.2f, 0.3f, 4.0f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FLOOR, switchedState), 32, true);

	//Initialisierung Pfosten
	m_zgPfosten.Init(0.2f, 1.1f, 0.2f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FENCE, switchedState));

	//Initialisierung Balken
	m_zgBalkenLang.Init(4.7f, 0.1f, 0.1f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FENCE, switchedState));
	m_zgBalkenKurz.Init(3.2f, 0.1f, 0.1f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FENCE, switchedState));

	//Initialisierung Trassen
	m_zTrasse1.initViewModel(vBuilding, switchedState);
	m_zTrasse2.initViewModel(vBuilding, switchedState);
	m_zTrasse1.Init();
	m_zTrasse2.Init();

	//Initialisierung Drehelement
	m_zgDrehelement.Init(0.12f, 0.12f, 0.1f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_FLOOR, switchedState), 32, true, true);

	//Initialisierung Schranke
	m_zgSchranke.Init(2.65f, 0.2f, 0.04f, VMaterialLoader::getMaterialModel(VMaterialLoader::NUCLEAR_GATE, switchedState));

	//Initialisierung Smoke
	if (switchedState)
	{
		quadAnimationSmokeFast.Init(2.0f, 2.0f, &VMaterialLoader::materialAnimSmokeFast);
		quadAnimationSmokeSlow.Init(1.9f, 2.0f, &VMaterialLoader::materialAnimSmokeSlow);
		placementAnimationSmokeFast.AddGeo(&quadAnimationSmokeFast);
		placementAnimationSmokeSlow.AddGeo(&quadAnimationSmokeSlow);
		placementAnimationSmoke.AddPlacement(&placementAnimationSmokeFast);
		placementAnimationSmoke.AddPlacement(&placementAnimationSmokeSlow);
		placementAnimationSmokeSlow.TranslateZ(-0.3f);
		placementAnimationSmoke.TranslateY(5.5f);
	}

	//Placements
	m_zpLOD[0].AddPlacement(&m_zpAtomkraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpAtomkraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpAtomkraftwerk);
	m_zpMain.AddPlacement(&m_zpAtomkraftwerk);
	m_zpAtomkraftwerk.AddPlacement(&m_zpFundament);
	m_zpAtomkraftwerk.AddPlacement(&m_zpKuehlturm1);
	m_zpAtomkraftwerk.AddPlacement(&m_zpKuehlturm2);
	m_zpAtomkraftwerk.AddPlacement(&m_zpReaktor1);
	m_zpAtomkraftwerk.AddPlacement(&m_zpReaktor2);
	m_zpAtomkraftwerk.AddPlacement(&m_zpKamin);
	m_zpAtomkraftwerk.AddPlacement(m_zTrasse1.getPlacementMain());
	m_zpAtomkraftwerk.AddPlacement(m_zTrasse2.getPlacementMain());
	m_zpAtomkraftwerk.AddPlacement(&m_zpGebaeude1);
	m_zpAtomkraftwerk.AddPlacement(&m_zpGebaeude2);
	m_zpAtomkraftwerk.AddPlacement(&m_zpAbsperrung);

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

	m_zpReaktor1.AddPlacement(&m_zpReaktorTurm1);
	m_zpReaktor1.AddPlacement(&m_zpReaktorKopf1);
	m_zpReaktor2.AddPlacement(&m_zpReaktorTurm2);
	m_zpReaktor2.AddPlacement(&m_zpReaktorKopf2);

	m_zpGebaeude1.AddPlacement(&m_zpGebaeudeHaelfte11);
	//m_zpGebaeudeHaelfte11.AddPlacement(Gebaeude);
	m_zpGebaeude1.AddPlacement(&m_zpGebaeudeHaelfte12);
	//m_zpGebaeudeHaelfte12.AddPlacement(Gebaeude);
	m_zpGebaeude2.AddPlacement(&m_zpGebaeudeHaelfte21);
	//m_zpGebaeudeHaelfte21.AddPlacement(Gebaeude);
	m_zpGebaeude2.AddPlacement(&m_zpGebaeudeHaelfte22);
	//m_zpGebaeudeHaelfte22.AddPlacement(Gebaeude);

	//Adding

	//m_zpFundament.Translate(-5.0f, 0.0f, -5.0f);
	m_zpFundament.AddGeo(&m_zgFoundation);
	m_zpFundament.ScaleXDelta(12.5f);
	m_zpFundament.ScaleZDelta(12.5f);

	m_zpKuehlturm1.Translate(CHVector(-2.0f, 0.15f, -2.0f));
	m_zpKuehlturm1.AddGeo(&m_zgKuehlturm);

	m_zpKuehlturm2.Translate(CHVector(2.0f, 0.15f, -2.0f));
	m_zpKuehlturm2.AddGeo(&m_zgKuehlturm);

	if (switchedState)
	{
		m_zpKuehlturm1.AddPlacement(&placementAnimationSmoke);
		m_zpKuehlturm2.AddPlacement(&placementAnimationSmoke);
	}

	m_zpReaktorTurm1.Translate(CHVector(-0.9f, 0.85f, 3.0f));
	m_zpReaktorTurm1.AddGeo(&m_zgReaktorTurm);

	m_zpReaktorKopf1.Translate(CHVector(-0.9f, 1.45f, 3.0f));
	m_zpReaktorKopf1.AddGeo(&m_zgReaktorKopf);

	m_zpReaktorTurm2.Translate(CHVector(0.9f, 0.85f, 3.0f));
	m_zpReaktorTurm2.AddGeo(&m_zgReaktorTurm);

	m_zpReaktorKopf2.Translate(CHVector(0.9f, 1.45f, 3.0f));
	m_zpReaktorKopf2.AddGeo(&m_zgReaktorKopf);

	m_zpKamin.Translate(CHVector(0.0f, 2.15f, 2.0f));
	m_zpKamin.AddGeo(&m_zgKamin);

	m_zpGebaeude1.Translate(CHVector(0.0f, 0.15f, -0.7f));
	m_zpGebaeudeHaelfte11.Translate(CHVector(1.0f, 0.15f, 2.0f));
	m_zpGebaeudeHaelfte12.TranslateDelta(CHVector(-1.0f, 0.15f, -1.0f));
	m_zpGebaeudeHaelfte12.RotateYDelta(PI);

	m_zpGebaeude2.Translate(CHVector(-2.8f, 0.15f, -3.8f));
	m_zpGebaeude2.RotateYDelta(0.5 * PI);
	m_zpGebaeudeHaelfte21.Translate(CHVector(1.0f, 0.15f, 1.6f));
	m_zpGebaeudeHaelfte22.TranslateDelta(CHVector(-1.0f, 0.15f, -0.6f));
	m_zpGebaeudeHaelfte22.RotateYDelta(PI);

	m_zTrasse1.getPlacementMain()->Translate(CHVector(3.0f, 0.35f, 2.0f));
	m_zTrasse2.getPlacementMain()->Translate(CHVector(3.0f, 0.35f, 3.5f));

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

void VModelNuclearPowerPlant::switchOn()
{
}

void VModelNuclearPowerPlant::switchOff()
{
}

NAMESPACE_VIEW_E
