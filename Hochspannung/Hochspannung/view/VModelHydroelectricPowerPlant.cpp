#include "VModelHydroelectricPowerPlant.h"

NAMESPACE_VIEW_B


VModelHydroelectricPowerPlant::VModelHydroelectricPowerPlant()
{

	m_zgFluss.Init(CHVector(2.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmWasser);
	m_zgRad.InitStraight(3.5f, 4.0f, 2.0f, &VMaterialLoader::m_zmHolz);
	m_zgSchaufel.Init(CHVector(1.0f, 0.1f, 4.5f), &VMaterialLoader::m_zmHolz);
	m_zgFoundation.Init(CHVector(5.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmAtomgrundGreen);


	//Initialisierung Trassen
	///m_zTrasse1.Init();
	//m_zTrasse2.Init();
	//Gebaeude.Init();

	//Placements
	m_zpLOD[0].AddPlacement(&m_zpWasserKraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpWasserKraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpWasserKraftwerk);
	
	m_zpMain.AddPlacement(&m_zpWasserKraftwerk);
	m_zpWasserKraftwerk.AddPlacement(&m_zpWasserRad);
	m_zpWasserKraftwerk.AddPlacement(&m_zpFluss);
	m_zpWasserKraftwerk.AddPlacement(&m_zpFundament);
	m_zpWasserRad.AddPlacement(&m_zpRad);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel1);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel2);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel3);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel4);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel5);
	m_zpWasserRad.AddPlacement(&m_zpWasserSchaufel6);
	//m_zpWasserKraftwerk.AddPlacement(m_zTrasse1.getMainPlacement());
	//m_zpWasserKraftwerk.AddPlacement(m_zTrasse2.getMainPlacement());
	//m_zpGebaude.AddPlacement(&Gebaeude);

	
	

	//Adding

	m_zpFluss.AddGeo(&m_zgFluss);
	m_zpFluss.TranslateY(0.01f);
	m_zpFluss.TranslateXDelta(-2.0f);

	m_zpFundament.AddGeo(&m_zgFoundation);

	m_zpRad.AddGeo(&m_zgRad);
	m_zpRad.RotateZ(PI / 2);
	m_zpWasserRad.TranslateYDelta(3.5);
	m_zpWasserRad.TranslateXDelta(-2.5);

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


NAMESPACE_VIEW_E
