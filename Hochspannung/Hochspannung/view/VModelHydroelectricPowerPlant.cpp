#include "VModelHydroelectricPowerPlant.h"

NAMESPACE_VIEW_B


VModelHydroelectricPowerPlant::VModelHydroelectricPowerPlant()
	: m_zmHolz(VMaterialLoader::m_zmWasserHolz),
	  m_zmAtomgrundGreen(VMaterialLoader::m_zmAllgemeinGreen),
	  Gebaeude(1.0f)
{
	m_zgFluss.Init(CHVector(2.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmWasser);
	m_zgRad.InitStraight(3.0f, 4.0f, 0.2f, &m_zmHolz);
	m_zgRad2.InitStraight(3.0f, 4.0f, 0.2f, &m_zmHolz);
	m_zgStange.InitStraight(0.05f, 0.2f, 5.0f, &m_zmHolz);
	m_zgSchaufel.Init(CHVector(1.0f, 0.1f, 4.5f), &m_zmHolz);
	m_zgFoundation.Init(CHVector(5.0f, 0.3f, 5.0f), &m_zmAtomgrundGreen);
	
	//Initialisierung Trassen
	///m_zTrasse1.Init();
	//m_zTrasse2.Init();


	//Placements
	m_zpLOD[0].AddPlacement(&m_zpWasserKraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpWasserKraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpWasserKraftwerk);
	
	m_zpMain.AddPlacement(&m_zpWasserKraftwerk);
	m_zpWasserKraftwerk.AddPlacement(&m_zpWasserRad);
	m_zpWasserKraftwerk.AddPlacement(&m_zpFluss);
	m_zpWasserKraftwerk.AddPlacement(&m_zpFundament);
	m_zpWasserRad.AddPlacement(&m_zpRad);
	m_zpWasserRad.AddPlacement(&m_zpRad2);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel1);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel2);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel3);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel4);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel5);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel6);
	m_zpWasserRad.AddPlacement(&m_zpStange);
	//m_zpWasserKraftwerk.AddPlacement(m_zTrasse1.getMainPlacement());
	//m_zpWasserKraftwerk.AddPlacement(m_zTrasse2.getMainPlacement());
	m_zpWasserKraftwerk.AddPlacement(&m_zpGebaude);
	m_zpGebaude.AddPlacement(&Gebaeude);

	

	//Adding

	Gebaeude.TranslateZDelta(2.0f);

	m_zpStange.AddGeo(&m_zgStange);
	m_zpStange.RotateZ(PI / 2);
	m_zpStange.TranslateXDelta(2.0f);

	m_zpFluss.AddGeo(&m_zgFluss);
	m_zpFluss.TranslateY(0.01f);
	m_zpFluss.TranslateXDelta(-2.0f);

	m_zpFundament.AddGeo(&m_zgFoundation);

	m_zpRad.AddGeo(&m_zgRad);
	m_zpRad.RotateZ(PI / 2);
	m_zpRad.TranslateXDelta(-1.0f);

	m_zpRad2.AddGeo(&m_zgRad2);
	m_zpRad2.RotateZ(PI / 2);
	m_zpRad2.TranslateXDelta(1.0f);

	m_zpWasserRad.ScaleDelta(0.7f);
	m_zpWasserRad.TranslateYDelta(2.0f);
	m_zpWasserRad.TranslateXDelta(-1.5f);


	m_zpWasserSchaufel1.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel1.RotateX(0.5235987755982988f);


	m_zpWasserSchaufel2.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel2.RotateX(1.0471975511965976f);

	m_zpWasserSchaufel3.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel3.RotateX(PI/2);

	m_zpWasserSchaufel4.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel4.RotateX(2.0943951023931953f);

	m_zpWasserSchaufel5.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel5.RotateX(2.6179938779914944f);

	m_zpWasserSchaufel6.AddGeo(&m_zgSchaufel);
	m_zpWasserSchaufel6.RotateX(PI);
}

VModelHydroelectricPowerPlant::~VModelHydroelectricPowerPlant()
{}

void VModelHydroelectricPowerPlant::switchOn() 
{
	m_zmHolz.SetColorAmbient(colorAmbientOn);
	m_zmAtomgrundGreen.SetColorAmbient(colorAmbientOn);
	Gebaeude.switchOn();
}

void VModelHydroelectricPowerPlant::switchOff()
{
	m_zmHolz.SetColorAmbient(colorAmbientOff);
	m_zmAtomgrundGreen.SetColorAmbient(colorAmbientOff);
	Gebaeude.switchOff();
}


NAMESPACE_VIEW_E
