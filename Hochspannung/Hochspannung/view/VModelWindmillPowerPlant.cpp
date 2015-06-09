#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


VModelWindmillPowerPlant::VModelWindmillPowerPlant()
:
m_zmWindRad(VMaterialLoader::m_zmWindRad),
m_zmWindGrund(VMaterialLoader::m_zmWindGrund),
m_zmWindFluegel1(VMaterialLoader::m_zmWindFluegel1),
m_zmWindFluegel2(VMaterialLoader::m_zmWindFluegel2),
m_zmWindFluegel3(VMaterialLoader::m_zmWindFluegel3)
{
	m_zpLOD[0].AddPlacement(&m_zpWindkraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpWindkraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpWindkraftwerk);
	m_zpMain.AddPlacement(&m_zpWindkraftwerk);
	m_zpWindkraftwerk.AddPlacement(&m_zpBasis);
	m_zpWindkraftwerk.AddPlacement(&m_zpKopf);
	m_zpBasis.AddPlacement(&m_zpTurm);
	m_zpBasis.AddPlacement(&m_zpFundament);
	m_zpBasis.AddPlacement(&m_zpNetzanschluss);

	m_zpKopf.AddPlacement(&m_zpGondel);
	m_zpKopf.AddPlacement(&m_zpRotorblatt1);
	m_zpKopf.AddPlacement(&m_zpRotorblatt2);
	m_zpKopf.AddPlacement(&m_zpRotorblatt3);


	//Initialisierung der Koerper

	//Initialisierung Turm
	m_zgTurm.Init(0.6f, 0.2f, 8.0f, &m_zmWindRad);

	//Initialisierung Fundament
	m_zgFundament.Init(2.0f, 0.3f, 2.0f, &m_zmWindGrund);
	m_zgFoundation.Init(CHVector(2.0f, 0.3f, 2.0f), &m_zmWindGrund);

	//Initialisierung Netzanschluss
	m_zgNetzanschluss.Init(0.5f, 0.5f, 0.3f, &m_zmWindRad);

	//Initialisierung Gondel
	m_zgGondel.Init(CHVector(0.4f, 1.0f, 0.4f), &m_zmWindRad);

	//Initialisierung Rotorblatt
	m_zgRotorblatt1.Init(CHVector(0.2f, 2.0f, 0.1f), &m_zmWindFluegel1);
	m_zgRotorblatt2.Init(CHVector(0.2f, 2.0f, 0.1f), &m_zmWindFluegel2);
	m_zgRotorblatt3.Init(CHVector(0.2f, 2.0f, 0.1f), &m_zmWindFluegel3);

	

	m_zpTurm.Translate(CHVector(0.0f, -1.0f, 0.0f));
	m_zpTurm.AddGeo(&m_zgTurm);
	m_zpFundament.Translate(CHVector(-1.0f, -1.3f, -1.0f));
	m_zpFundament.AddGeo(&m_zgFundament);
	m_zpNetzanschluss.Translate(CHVector(-0.25f, -1.0f, -0.8f));
	m_zpNetzanschluss.AddGeo(&m_zgNetzanschluss);
	m_zpGondel.RotateX(PI / 2);
	m_zpGondel.TranslateDelta(CHVector(0.0f, 7.2f, -0.0f));
	m_zpGondel.AddGeo(&m_zgGondel);

	m_zpRotorblatt1.Translate(CHVector(0.0f, 9.3f, 0.8f));
	m_zpRotorblatt1.AddGeo(&m_zgRotorblatt1);

	m_zpRotorblatt2.RotateZDelta((2 * PI) / 3);
	m_zpRotorblatt2.TranslateDelta(CHVector(-1.5f, 6.3f, 0.75f));
	m_zpRotorblatt2.AddGeo(&m_zgRotorblatt2);

	m_zpRotorblatt3.RotateZ(2 * (2 * PI) / 3);
	m_zpRotorblatt3.TranslateDelta(CHVector(1.5f, 6.3f, 0.75f));
	m_zpRotorblatt3.AddGeo(&m_zgRotorblatt3);

	m_zpBasis.TranslateDelta(CHVector(0.0f, -7.0f, 0.0f));
	m_zpKopf.TranslateDelta(CHVector(0.0f, -7.2f, 0.0f));
}


void VModelWindmillPowerPlant::switchOn()
{
	m_zmWindRad.SetColorAmbient(colorAmbientOn);
	m_zmWindGrund.SetColorAmbient(colorAmbientOn);
	m_zmWindFluegel1.SetColorAmbient(colorAmbientOn);
	m_zmWindFluegel2.SetColorAmbient(colorAmbientOn);
	m_zmWindFluegel3.SetColorAmbient(colorAmbientOn);
}

void VModelWindmillPowerPlant::switchOff()
{
	m_zmWindRad.SetColorAmbient(colorAmbientOff);
	m_zmWindGrund.SetColorAmbient(colorAmbientOff);
	m_zmWindFluegel1.SetColorAmbient(colorAmbientOff);
	m_zmWindFluegel2.SetColorAmbient(colorAmbientOff);
	m_zmWindFluegel3.SetColorAmbient(colorAmbientOff);
}

VModelWindmillPowerPlant::~VModelWindmillPowerPlant()
{
	removeMaterial(&m_zmWindRad);
	removeMaterial(&m_zmWindGrund);
	removeMaterial(&m_zmWindFluegel1);
	removeMaterial(&m_zmWindFluegel2);
	removeMaterial(&m_zmWindFluegel3);
}


NAMESPACE_VIEW_E
