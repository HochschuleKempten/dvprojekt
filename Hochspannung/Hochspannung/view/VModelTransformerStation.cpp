#include "VModelTransformerStation.h"

NAMESPACE_VIEW_B


VModelTransformerStation::VModelTransformerStation()
{
	//Initialisierung der Koerper
	m_zpLOD[0].AddPlacement(&m_zpUmspannwerk);
	m_zpLOD[1].AddPlacement(&m_zpUmspannwerk);
	m_zpLOD[2].AddPlacement(&m_zpUmspannwerk);

	m_zpMain.AddPlacement(&m_zpUmspannwerk);

	//Initialisierung Fundament
	m_zgFoundation.Init(CHVector(5.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmUmspannBoden);
	//Initalisierung Ständer
	m_zgStaender.Init(0.05f, 0.05f, 1.5f, &VMaterialLoader::m_zmUmspannGrund);
	//Initalisierung Querstange
	m_zgQuerstange.Init(2.0f, 0.1f, 0.1f, &VMaterialLoader::m_zmUmspannGrund);
	//Initalisierung Isolator
	m_zgIsolator.Init(1.0f, 1.0f, 2.5f, &VMaterialLoader::m_zmUmspannIsolator, 24);
	//Initalisierung Querstange2
	m_zgQuerstange2.Init(0.1f, 0.1f, 2.0f, &VMaterialLoader::m_zmUmspannGrund);
	//Initialisierung Trasssen
	m_zTrasse1.Init();
	m_zTrasse2.Init();
	m_zTrasse3.Init();
	//Initialisierung Generator
	m_zgGeneratorKasten.Init(2.5f, 1.9f, 3.3f, &VMaterialLoader::m_zmUmspannGrund);
	//Initialisierung Stecka
	m_zgStecka.Init(0.03f, 0.03f, 1.0f, &VMaterialLoader::m_zmUmspannGrund);
	//Initialisierung Kugel
	m_zgKugel.Init(0.05f, &VMaterialLoader::m_zmIsolator);
	//Initialisierung Kabel
	m_zgKabelMitte.Init(0.01f, 0.01f, 1.1f, &VMaterialLoader::m_zmUmspannLeitung);
	m_zgKabelSeite.Init(0.01f, 0.01f, 1.6f, &VMaterialLoader::m_zmUmspannLeitung);






	//Placements
	m_zpUmspannwerk.AddPlacement(&m_zpGenerator);

	m_zpGenerator.AddPlacement(&m_zpGeneratorKasten);
	m_zpGenerator.AddPlacement(&m_zpGIMitteLinks);
	m_zpGenerator.AddPlacement(&m_zpGIMitteRechts);
	m_zpGenerator.AddPlacement(&m_zpGILinksVorne);
	m_zpGenerator.AddPlacement(&m_zpGILinksHinten);
	m_zpGenerator.AddPlacement(&m_zpGIRechtsVorne);
	m_zpGenerator.AddPlacement(&m_zpGIRechtsHinten);
	m_zpGenerator.AddPlacement(&m_zpSteckaVorne);
	m_zpGenerator.AddPlacement(&m_zpSteckaHinten);
	m_zpGenerator.AddPlacement(&m_zpKugelHinten);
	m_zpGenerator.AddPlacement(&m_zpKugelVorne);
	m_zpGenerator.AddPlacement(&m_zpKugelMitteLinks);
	m_zpGenerator.AddPlacement(&m_zpKugelMitteRechts);
	m_zpGenerator.AddPlacement(&m_zpKugelLinksVorne);
	m_zpGenerator.AddPlacement(&m_zpKugelLinksHinten);
	m_zpGenerator.AddPlacement(&m_zpKugelRechtsVorne);
	m_zpGenerator.AddPlacement(&m_zpKugelRechtsHinten);
	m_zpGenerator.AddPlacement(&m_zpKabelMitteLinks);
	m_zpGenerator.AddPlacement(&m_zpKabelMitteRechts);
	m_zpGenerator.AddPlacement(&m_zpKabelLinksVorne);
	m_zpGenerator.AddPlacement(&m_zpKabelLinksHinten);
	m_zpGenerator.AddPlacement(&m_zpKabelRechtsVorne);
	m_zpGenerator.AddPlacement(&m_zpKabelRechtsHinten);


	m_zpUmspannwerk.AddPlacement(m_zTrasse1.getMainPlacement());
	m_zpUmspannwerk.AddPlacement(m_zTrasse2.getMainPlacement());
	m_zpUmspannwerk.AddPlacement(m_zTrasse3.getMainPlacement());
	m_zpUmspannwerk.AddPlacement(&m_zpFundament);
	m_zpUmspannwerk.AddPlacement(&m_zpUmspannmast);
	m_zpUmspannwerk.AddPlacement(&m_zpUmspannmastLinks);
	m_zpUmspannwerk.AddPlacement(&m_zpUmspannmastRechts);
	m_zpUmspannmast.AddPlacement(&m_zpStaender);
	m_zpUmspannmast.AddPlacement(&m_zpQuerstange);
	m_zpUmspannmast.AddPlacement(&m_zpIsolatorLinks);
	m_zpUmspannmast.AddPlacement(&m_zpIsolatorMitte);
	m_zpUmspannmast.AddPlacement(&m_zpIsolatorRechts);
	//Links
	m_zpUmspannmastLinks.AddPlacement(&m_zpStaenderLinks);
	m_zpUmspannmastLinks.AddPlacement(&m_zpQuerstangeLinks);
	m_zpUmspannmastLinks.AddPlacement(&m_zpIsolatorLinksLinks);
	m_zpUmspannmastLinks.AddPlacement(&m_zpIsolatorMitteLinks);
	m_zpUmspannmastLinks.AddPlacement(&m_zpIsolatorRechtsLinks);
	//Rechts
	m_zpUmspannmastRechts.AddPlacement(&m_zpStaenderRechts);
	m_zpUmspannmastRechts.AddPlacement(&m_zpQuerstangeRechts);
	m_zpUmspannmastRechts.AddPlacement(&m_zpIsolatorLinksRechts);
	m_zpUmspannmastRechts.AddPlacement(&m_zpIsolatorMitteRechts);
	m_zpUmspannmastRechts.AddPlacement(&m_zpIsolatorRechtsRechts);



	//Adding

	m_zpFundament.Translate(CHVector(-0.0f, 0.0f, -0.0f));
	m_zpFundament.AddGeo(&m_zgFoundation);

	m_zpStaender.Translate(CHVector(0.0f, 0.3f, 0.0f));
	m_zpStaender.AddGeo(&m_zgStaender);

	m_zpQuerstange.Translate(CHVector(-1.0f, 1.8f, -0.05f));
	m_zpQuerstange.AddGeo(&m_zgQuerstange);

	m_zpIsolatorMitte.Scale(0.05);
	m_zpIsolatorMitte.TranslateDelta(CHVector(0.0f, 1.9f, 0.0f));
	m_zpIsolatorMitte.AddGeo(&m_zgIsolator);

	m_zpIsolatorLinks.Scale(0.05);
	m_zpIsolatorLinks.TranslateDelta(CHVector(-0.85f, 1.9f, 0.0f));
	m_zpIsolatorLinks.AddGeo(&m_zgIsolator);

	m_zpIsolatorRechts.Scale(0.05);
	m_zpIsolatorRechts.TranslateDelta(CHVector(0.85f, 1.9f, 0.0f));
	m_zpIsolatorRechts.AddGeo(&m_zgIsolator);

	m_zpUmspannmast.Translate(CHVector(0.0f, 0.0f, 2.5f));


	//Links

	m_zpStaenderLinks.Translate(CHVector(0.0f, 0.3f, 0.0f));
	m_zpStaenderLinks.AddGeo(&m_zgStaender);

	m_zpQuerstangeLinks.Translate(CHVector(-0.05f, 1.8f, -1.0f));
	m_zpQuerstangeLinks.AddGeo(&m_zgQuerstange2);

	m_zpIsolatorMitteLinks.Scale(0.05);
	m_zpIsolatorMitteLinks.TranslateDelta(CHVector(0.0f, 1.9f, 0.0f));
	m_zpIsolatorMitteLinks.AddGeo(&m_zgIsolator);

	m_zpIsolatorLinksLinks.Scale(0.05);
	m_zpIsolatorLinksLinks.TranslateDelta(CHVector(0.0f, 1.9f, -0.85f));
	m_zpIsolatorLinksLinks.AddGeo(&m_zgIsolator);

	m_zpIsolatorRechtsLinks.Scale(0.05);
	m_zpIsolatorRechtsLinks.TranslateDelta(CHVector(0.0f, 1.9f, 0.85f));
	m_zpIsolatorRechtsLinks.AddGeo(&m_zgIsolator);

	m_zpUmspannmastLinks.Translate(CHVector(-2.5f, 0.0f, 0.0f));

	//Rechts

	m_zpStaenderRechts.Translate(CHVector(0.0f, 0.3f, 0.0f));
	m_zpStaenderRechts.AddGeo(&m_zgStaender);

	m_zpQuerstangeRechts.Translate(CHVector(-0.05f, 1.8f, -1.0f));
	m_zpQuerstangeRechts.AddGeo(&m_zgQuerstange2);

	m_zpIsolatorMitteRechts.Scale(0.05);
	m_zpIsolatorMitteRechts.TranslateDelta(CHVector(0.0f, 1.9f, 0.0f));
	m_zpIsolatorMitteRechts.AddGeo(&m_zgIsolator);

	m_zpIsolatorLinksRechts.Scale(0.05);
	m_zpIsolatorLinksRechts.TranslateDelta(CHVector(0.0f, 1.9f, -0.85f));
	m_zpIsolatorLinksRechts.AddGeo(&m_zgIsolator);

	m_zpIsolatorRechtsRechts.Scale(0.05);
	m_zpIsolatorRechtsRechts.TranslateDelta(CHVector(0.0f, 1.9f, 0.85f));
	m_zpIsolatorRechtsRechts.AddGeo(&m_zgIsolator);

	m_zpUmspannmastRechts.Translate(CHVector(2.5f, 0.0f, 0.0f));

	//Trassen
	m_zTrasse1.getMainPlacement()->Translate(CHVector(-4.0f, 0.35f, 0.0f));
	m_zTrasse2.getMainPlacement()->Translate(4.0f, 0.35f, 0.0f);
	m_zTrasse3.getMainPlacement()->RotateY(HALFPI);
	m_zTrasse3.getMainPlacement()->TranslateDelta(0.0f, 0.35f, 4.0f);

	//Generator
	m_zpGeneratorKasten.Translate(CHVector(-1.3f, 0.0f, -1.6f));
	m_zpGeneratorKasten.AddGeo(&m_zgGeneratorKasten);

	//Generator-Isolatoren
	m_zpGIMitteLinks.Scale(0.05);
	m_zpGIMitteLinks.TranslateDelta(CHVector(-0.85f, 1.9f, 1.4f));
	m_zpGIMitteLinks.AddGeo(&m_zgIsolator);

	m_zpGIMitteRechts.Scale(0.05);
	m_zpGIMitteRechts.TranslateDelta(CHVector(0.85f, 1.9f, 1.4f));
	m_zpGIMitteRechts.AddGeo(&m_zgIsolator);

	m_zpGILinksVorne.Scale(0.05);
	m_zpGILinksVorne.TranslateDelta(CHVector(-0.85f, 1.9f, 0.85f));
	m_zpGILinksVorne.AddGeo(&m_zgIsolator);

	m_zpGILinksHinten.Scale(0.05);
	m_zpGILinksHinten.TranslateDelta(CHVector(-0.85f, 1.9f, -0.85f));
	m_zpGILinksHinten.AddGeo(&m_zgIsolator);

	m_zpGIRechtsVorne.Scale(0.05);
	m_zpGIRechtsVorne.TranslateDelta(CHVector(0.85f, 1.9f, 0.85f));
	m_zpGIRechtsVorne.AddGeo(&m_zgIsolator);

	m_zpGIRechtsHinten.Scale(0.05);
	m_zpGIRechtsHinten.TranslateDelta(CHVector(0.85f, 1.9f, -0.85f));
	m_zpGIRechtsHinten.AddGeo(&m_zgIsolator);

	//Generator-Stecka-Kugel
	m_zpSteckaVorne.Translate(CHVector(0.5f, 1.9f, 0.0f));
	m_zpSteckaVorne.AddGeo(&m_zgStecka);

	m_zpSteckaHinten.Translate(CHVector(-0.5f, 1.9f, 0.0f));
	m_zpSteckaHinten.AddGeo(&m_zgStecka);

	m_zpKugelVorne.Translate(CHVector(0.5f, 2.9f, 0.0f));
	m_zpKugelVorne.AddGeo(&m_zgKugel);

	m_zpKugelHinten.Translate(CHVector(-0.5f, 2.9f, 0.0f));
	m_zpKugelHinten.AddGeo(&m_zgKugel);

	//Generator-Kabel
	m_zpKabelMitteLinks.RotateX(HALFPI);
	m_zpKabelMitteLinks.TranslateDelta(CHVector(-0.85f, 2.0f, 1.4f));
	m_zpKabelMitteLinks.AddGeo(&m_zgKabelMitte);

	m_zpKabelMitteRechts.RotateX(HALFPI);
	m_zpKabelMitteRechts.TranslateDelta(CHVector(0.85f, 2.0f, 1.4f));
	m_zpKabelMitteRechts.AddGeo(&m_zgKabelMitte);

	m_zpKabelLinksVorne.RotateZ(HALFPI);
	m_zpKabelLinksVorne.TranslateDelta(CHVector(-0.85f, 2.0f, 0.85f));
	m_zpKabelLinksVorne.AddGeo(&m_zgKabelSeite);

	m_zpKabelLinksHinten.RotateZ(HALFPI);
	m_zpKabelLinksHinten.TranslateDelta(CHVector(-0.85f, 2.0f, -0.85f));
	m_zpKabelLinksHinten.AddGeo(&m_zgKabelSeite);

	m_zpKabelRechtsVorne.RotateZ(-HALFPI);
	m_zpKabelRechtsVorne.TranslateDelta(CHVector(0.85f, 2.0f, 0.85f));
	m_zpKabelRechtsVorne.AddGeo(&m_zgKabelSeite);

	m_zpKabelRechtsHinten.RotateZ(-HALFPI);
	m_zpKabelRechtsHinten.TranslateDelta(CHVector(0.85f, 2.0f, -0.85f));
	m_zpKabelRechtsHinten.AddGeo(&m_zgKabelSeite);

	//Lightning Animation
	quadForAnimation.Init(0.5f, 0.5f, &VMaterialLoader::materialAnimTransformerStationLightning);
	placementForAnimation.AddGeo(&quadForAnimation);
	m_zpSteckaVorne.AddPlacement(&placementForAnimation);
	placementForAnimation.TranslateX(-0.5f);
	placementForAnimation.TranslateYDelta(1.0f);
}


VModelTransformerStation::~VModelTransformerStation()
{}


NAMESPACE_VIEW_E
