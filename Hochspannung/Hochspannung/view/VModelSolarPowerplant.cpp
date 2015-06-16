#include "VModelSolarPowerPlant.h"

NAMESPACE_VIEW_B


VModelSolarPowerPlant::VModelSolarPowerPlant()
{}

VModelSolarPowerPlant::~VModelSolarPowerPlant()
{}

void VModelSolarPowerPlant::init()
{
	m_zpLOD[0].AddPlacement(&m_zpSolarPowerplant);
	m_zpLOD[1].AddPlacement(&m_zpSolarPowerplant);
	m_zpLOD[2].AddPlacement(&m_zpSolarPowerplant2);
	//LOD 0 Placement
	m_zpMain.AddPlacement(&m_zpSolarPowerplant);
	m_zpSolarPowerplant.AddPlacement(&m_zpGrundflaeche);
	m_zpSolarPowerplant.AddPlacement(&m_zpSockel);
	m_zpSolarPowerplant.AddPlacement(&m_zpSenkrechte);
	m_zpSenkrechte.AddPlacement(&m_zpGrundflaeche);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle1);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle2);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle3);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle4);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle5);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle6);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle7);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle8);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle9);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle10);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle11);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle12);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle13);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle14);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle15);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle16);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle17);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle18);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle19);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle20);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle21);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle22);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle23);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle24);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle25);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle26);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle27);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle28);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle29);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle30);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle31);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle32);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle33);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle34);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle35);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle36);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle37);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle38);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle39);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle40);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle41);
	m_zpGrundflaeche.AddPlacement(&m_zpZelle42);

	m_zpGrundflaeche.AddPlacement(&m_zpStabilisierung);




	m_zgStabilisierung.Init(CHVector(1.8, 0.05, 0.1), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_FLOOR, switchedState));

	m_zgSenkrechte.Init(0.2, 0.2, 1.08, VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_FLOOR, switchedState));
	m_zgGrundflaeche.Init(CHVector(2, 0.05, 1.5), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_FLOOR, switchedState));
	m_zgSockel.Init(CHVector(1, 0.05, 1), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_FLOOR, switchedState));
	m_zgFoundation.Init(CHVector(1, 0.05, 1), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_FLOOR, switchedState));
	m_zgSolarzelle1.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle2.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle3.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle4.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle5.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle6.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle7.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle8.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle9.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle10.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle11.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle12.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle13.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle14.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle15.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle16.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle17.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle18.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle19.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle20.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle21.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle22.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle23.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle24.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle25.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle26.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle27.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle28.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle29.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle30.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle31.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle32.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle33.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle34.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle35.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle36.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle37.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle38.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle39.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle40.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle41.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));
	m_zgSolarzelle42.Init(CHVector(0.3, 0.05, 0.2), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELL, switchedState));


	m_zpStabilisierung.AddGeo(&m_zgStabilisierung);
	m_zpGrundflaeche.AddGeo(&m_zgGrundflaeche);
	m_zpSockel.AddGeo(&m_zgFoundation);
	m_zpSenkrechte.AddGeo(&m_zgSenkrechte);
	m_zpZelle1.AddGeo(&m_zgSolarzelle1);
	m_zpZelle2.AddGeo(&m_zgSolarzelle2);
	m_zpZelle3.AddGeo(&m_zgSolarzelle3);
	m_zpZelle4.AddGeo(&m_zgSolarzelle4);
	m_zpZelle5.AddGeo(&m_zgSolarzelle5);
	m_zpZelle6.AddGeo(&m_zgSolarzelle6);
	m_zpZelle7.AddGeo(&m_zgSolarzelle7);
	m_zpZelle8.AddGeo(&m_zgSolarzelle8);
	m_zpZelle9.AddGeo(&m_zgSolarzelle9);
	m_zpZelle10.AddGeo(&m_zgSolarzelle10);
	m_zpZelle11.AddGeo(&m_zgSolarzelle11);
	m_zpZelle12.AddGeo(&m_zgSolarzelle12);
	m_zpZelle13.AddGeo(&m_zgSolarzelle13);
	m_zpZelle14.AddGeo(&m_zgSolarzelle14);
	m_zpZelle15.AddGeo(&m_zgSolarzelle15);
	m_zpZelle16.AddGeo(&m_zgSolarzelle16);
	m_zpZelle17.AddGeo(&m_zgSolarzelle17);
	m_zpZelle18.AddGeo(&m_zgSolarzelle18);
	m_zpZelle19.AddGeo(&m_zgSolarzelle19);
	m_zpZelle20.AddGeo(&m_zgSolarzelle20);
	m_zpZelle21.AddGeo(&m_zgSolarzelle21);
	m_zpZelle22.AddGeo(&m_zgSolarzelle22);
	m_zpZelle23.AddGeo(&m_zgSolarzelle23);
	m_zpZelle24.AddGeo(&m_zgSolarzelle24);
	m_zpZelle25.AddGeo(&m_zgSolarzelle25);
	m_zpZelle26.AddGeo(&m_zgSolarzelle26);
	m_zpZelle27.AddGeo(&m_zgSolarzelle27);
	m_zpZelle28.AddGeo(&m_zgSolarzelle28);
	m_zpZelle29.AddGeo(&m_zgSolarzelle29);
	m_zpZelle30.AddGeo(&m_zgSolarzelle30);
	m_zpZelle31.AddGeo(&m_zgSolarzelle31);
	m_zpZelle32.AddGeo(&m_zgSolarzelle32);
	m_zpZelle33.AddGeo(&m_zgSolarzelle33);
	m_zpZelle34.AddGeo(&m_zgSolarzelle34);
	m_zpZelle35.AddGeo(&m_zgSolarzelle35);
	m_zpZelle36.AddGeo(&m_zgSolarzelle36);
	m_zpZelle37.AddGeo(&m_zgSolarzelle37);
	m_zpZelle38.AddGeo(&m_zgSolarzelle38);
	m_zpZelle39.AddGeo(&m_zgSolarzelle39);
	m_zpZelle40.AddGeo(&m_zgSolarzelle40);
	m_zpZelle41.AddGeo(&m_zgSolarzelle41);
	m_zpZelle42.AddGeo(&m_zgSolarzelle42);


	//LOD 2 Placement
	m_zpSolarPowerplant2.AddPlacement(&m_zpGrundflaeche2);
	m_zgGrundflaeche2.Init(CHVector(2, 0.05, 1.5), VMaterialLoader::getMaterialModel(VMaterialLoader::SOLAR_CELLS_LOD, true));
	m_zpGrundflaeche2.AddGeo(&m_zgGrundflaeche2);
	m_zpSolarPowerplant2.AddPlacement(&m_zpSockel);
	m_zpSolarPowerplant2.AddPlacement(&m_zpSenkrechte);
	m_zpGrundflaeche2.Translate(0, 1.0f, -1);
	m_zpGrundflaeche2.RotateDelta(1, 0, 0, 0.5);






	m_zpGrundflaeche.Translate(0, 1.0f, -1);
	m_zpStabilisierung.Translate(0, -0.1f, 0.35);

	m_zpZelle1.TranslateDelta(-1.69, 0.01f, -1.27);
	m_zpZelle2.TranslateDelta(-1.69, 0.01f, -0.85);
	m_zpZelle3.TranslateDelta(-1.69, 0.01f, -0.43);
	m_zpZelle4.TranslateDelta(-1.69, 0.01f, -0.01);
	m_zpZelle5.TranslateDelta(-1.69, 0.01f, 0.41);
	m_zpZelle6.TranslateDelta(-1.69, 0.01f, 0.83);
	m_zpZelle7.TranslateDelta(-1.69, 0.01f, 1.25);

	m_zpZelle8.TranslateDelta(-1.02, 0.01f, -1.27);
	m_zpZelle9.TranslateDelta(-1.02, 0.01f, -0.85);
	m_zpZelle10.TranslateDelta(-1.02, 0.01f, -0.43);
	m_zpZelle11.TranslateDelta(-1.02, 0.01f, -0.01);
	m_zpZelle12.TranslateDelta(-1.02, 0.01f, 0.41);
	m_zpZelle13.TranslateDelta(-1.02, 0.01f, 0.83);
	m_zpZelle14.TranslateDelta(-1.02, 0.01f, 1.25);


	m_zpZelle15.TranslateDelta(-0.36, 0.01f, -1.27);
	m_zpZelle16.TranslateDelta(-0.36, 0.01f, -0.85);
	m_zpZelle17.TranslateDelta(-0.36, 0.01f, -0.43);
	m_zpZelle18.TranslateDelta(-0.36, 0.01f, -0.01);
	m_zpZelle19.TranslateDelta(-0.36, 0.01f, 0.41);
	m_zpZelle20.TranslateDelta(-0.36, 0.01f, 0.83);
	m_zpZelle21.TranslateDelta(-0.36, 0.01f, 1.25);



	m_zpZelle22.TranslateDelta(0.32, 0.01f, -1.27);
	m_zpZelle23.TranslateDelta(0.32, 0.01f, -0.85);
	m_zpZelle24.TranslateDelta(0.32, 0.01f, -0.43);
	m_zpZelle25.TranslateDelta(0.32, 0.01f, -0.01);
	m_zpZelle26.TranslateDelta(0.32, 0.01f, 0.41);
	m_zpZelle27.TranslateDelta(0.32, 0.01f, 0.83);
	m_zpZelle28.TranslateDelta(0.32, 0.01f, 1.25);

	m_zpZelle29.TranslateDelta(1.01, 0.01f, -1.27);
	m_zpZelle30.TranslateDelta(1.01, 0.01f, -0.85);
	m_zpZelle31.TranslateDelta(1.01, 0.01f, -0.43);
	m_zpZelle32.TranslateDelta(1.01, 0.01f, -0.01);
	m_zpZelle33.TranslateDelta(1.01, 0.01f, 0.41);
	m_zpZelle34.TranslateDelta(1.01, 0.01f, 0.83);
	m_zpZelle35.TranslateDelta(1.01, 0.01f, 1.25);


	m_zpZelle36.TranslateDelta(1.69, 0.01f, -1.27);
	m_zpZelle37.TranslateDelta(1.69, 0.01f, -0.85);
	m_zpZelle38.TranslateDelta(1.69, 0.01f, -0.43);
	m_zpZelle39.TranslateDelta(1.69, 0.01f, -0.01);
	m_zpZelle40.TranslateDelta(1.69, 0.01f, 0.41);
	m_zpZelle41.TranslateDelta(1.69, 0.01f, 0.83);
	m_zpZelle42.TranslateDelta(1.69, 0.01f, 1.25);


	m_zpGrundflaeche.RotateDelta(1, 0, 0, 0.5);
}

void VModelSolarPowerPlant::switchOn()
{}

void VModelSolarPowerPlant::switchOff()
{}

NAMESPACE_VIEW_E
