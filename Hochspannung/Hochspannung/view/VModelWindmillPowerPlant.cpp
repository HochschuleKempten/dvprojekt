#include "VModelWindmillPowerPlant.h"

NAMESPACE_VIEW_B


VModelWindmillPowerPlant::VModelWindmillPowerPlant()
{}


void VModelWindmillPowerPlant::switchOn()
{

}

void VModelWindmillPowerPlant::switchOff()
{

}

VModelWindmillPowerPlant::~VModelWindmillPowerPlant()
{

}

void VModelWindmillPowerPlant::init()
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

	//Initialisierung Turm
	m_zgTurm.Init(0.6f, 0.2f, 8.0f, VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_RAD, switchedState));

	//Initialisierung Netzanschluss
	m_zgNetzanschluss.Init(0.5f, 0.5f, 0.3f, VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_RAD, switchedState));

	//Initialisierung Gondel
	m_zgGondel.Init(CHVector(0.4f, 1.0f, 0.4f), VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_RAD, switchedState));

	//Initialisierung Rotorblatt
	m_zgRotorblatt1.Init(CHVector(0.2f, 2.0f, 0.1f), VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_FLUEGEL1, switchedState));
	m_zgRotorblatt2.Init(CHVector(0.2f, 2.0f, 0.1f), VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_FLUEGEL2, switchedState));
	m_zgRotorblatt3.Init(CHVector(0.2f, 2.0f, 0.1f), VMaterialLoader::getMaterialModel(VMaterialLoader::WIND_FLUEGEL3, switchedState));



	m_zpTurm.Translate(CHVector(0.0f, -1.0f, 0.0f));
	m_zpTurm.AddGeo(&m_zgTurm);
	m_zpFundament.Translate(CHVector(0.0f, -0.5f, 0.0f));
	m_zpFundament.AddGeo(&m_zgFoundation);
	m_zpFundament.ScaleXDelta(4.0f);
	m_zpFundament.ScaleZDelta(4.0f);
	m_zpFundament.ScaleYDelta(2.0f);
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

NAMESPACE_VIEW_E
