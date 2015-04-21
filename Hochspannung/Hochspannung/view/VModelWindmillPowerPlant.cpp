#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


VModelWindmillPowerPlant::VModelWindmillPowerPlant()
{
	this->AddPlacement(&m_zpWindkraftanlage);
	m_zpWindkraftanlage.AddPlacement(&m_zpBasis);
	m_zpWindkraftanlage.AddPlacement(&m_zpKopf);
	m_zpBasis.AddPlacement(&m_zpTurm);
	m_zpBasis.AddPlacement(&m_zpFundament);
	m_zpBasis.AddPlacement(&m_zpNetzanschluss);

	m_zpKopf.AddPlacement(&m_zpGondel);
	m_zpKopf.AddPlacement(&m_zpRotorblatt1);
	m_zpKopf.AddPlacement(&m_zpRotorblatt2);
	m_zpKopf.AddPlacement(&m_zpRotorblatt3);


	//Initialisierung der Koerper

	//Initialisierung Turm
	m_zgTurm.Init(0.6f, 0.2f, 8.0f, &m_zm);

	//Initialisierung Fundament
	m_zgFundament.Init(2.0f, 0.3f, 2.0f, &m_zm);

	//Initialisierung Netzanschluss
	m_zgNetzanschluss.Init(0.5f, 0.5f, 0.3f, &m_zm);

	//Initialisierung Gondel
	m_zgGondel.Init(CHVector(0.4f, 1.0f, 0.4f), &m_zm);

	//Initialisierung Rotorblatt
	m_zgRotorblatt.Init(CHVector(0.2f, 2.0f, 0.1f), &m_zm);

	m_zm.MakeTextureDiffuse("Textures\\Metall.jpg");

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
	m_zpRotorblatt1.AddGeo(&m_zgRotorblatt);

	m_zpRotorblatt2.RotateZDelta((2 * PI) / 3);
	m_zpRotorblatt2.TranslateDelta(CHVector(-1.5f, 6.3f, 0.75f));
	m_zpRotorblatt2.AddGeo(&m_zgRotorblatt);

	m_zpRotorblatt3.RotateZ(2 * (2 * PI) / 3);
	m_zpRotorblatt3.TranslateDelta(CHVector(1.5f, 6.3f, 0.75f));
	m_zpRotorblatt3.AddGeo(&m_zgRotorblatt);

	m_zpBasis.TranslateDelta(CHVector(0.0f, -7.0f, 0.0f));
	m_zpKopf.TranslateDelta(CHVector(0.0f, -7.2f, 0.0f));
}


VModelWindmillPowerPlant::~VModelWindmillPowerPlant()
{
}


NAMESPACE_VIEW_E
