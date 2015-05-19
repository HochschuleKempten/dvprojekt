#pragma once

#include "VGeneral.h"
#include "IViewModel.h"
#include "VModelPowerLine.h"

NAMESPACE_VIEW_B



class VModelTransformerStation : public IViewModel
{
private:
	// Placements -------------------------------------------------------------------------

	CPlacement m_zpUmspannwerk;
	CPlacement m_zpFundament;

	//Umspannmast

	CPlacement m_zpUmspannmast;
	CPlacement m_zpStaender;
	CPlacement m_zpQuerstange;
	CPlacement m_zpIsolatorLinks;
	CPlacement m_zpIsolatorMitte;
	CPlacement m_zpIsolatorRechts;
	CPlacement m_zpUmspannmastLinks;
	CPlacement m_zpStaenderLinks;
	CPlacement m_zpQuerstangeLinks;
	CPlacement m_zpIsolatorLinksLinks;
	CPlacement m_zpIsolatorMitteLinks;
	CPlacement m_zpIsolatorRechtsLinks;
	CPlacement m_zpUmspannmastRechts;
	CPlacement m_zpStaenderRechts;
	CPlacement m_zpQuerstangeRechts;
	CPlacement m_zpIsolatorLinksRechts;
	CPlacement m_zpIsolatorMitteRechts;
	CPlacement m_zpIsolatorRechtsRechts;
	CPlacement m_zpGenerator;
	CPlacement m_zpGeneratorKasten;
	CPlacement m_zpGIMitteLinks;
	CPlacement m_zpGIMitteRechts;
	CPlacement m_zpGILinksVorne;
	CPlacement m_zpGILinksHinten;
	CPlacement m_zpGIRechtsVorne;
	CPlacement m_zpGIRechtsHinten;
	CPlacement m_zpSteckaVorne;
	CPlacement m_zpSteckaHinten;
	CPlacement m_zpKugelVorne;
	CPlacement m_zpKugelHinten;
	CPlacement m_zpKugelMitteLinks;
	CPlacement m_zpKugelMitteRechts;
	CPlacement m_zpKugelLinksVorne;
	CPlacement m_zpKugelLinksHinten;
	CPlacement m_zpKugelRechtsVorne;
	CPlacement m_zpKugelRechtsHinten;
	CPlacement m_zpKabelMitteLinks;
	CPlacement m_zpKabelMitteRechts;
	CPlacement m_zpKabelLinksVorne;
	CPlacement m_zpKabelLinksHinten;
	CPlacement m_zpKabelRechtsVorne;
	CPlacement m_zpKabelRechtsHinten;




	//Geo-Objects --------------------------------------------------------------------------

	CGeoWall m_zgFundament;

	VModelPowerLine m_zTrasse1;
	VModelPowerLine m_zTrasse2;
	VModelPowerLine m_zTrasse3;

	CMaterial m_zmGreen;
	CMaterial m_zmGrey;

	CDeviceKeyboard m_zdk;

	CGeoCylinder m_zgStaender;
	CGeoWall m_zgQuerstange;
	CGeoCylinder m_zgIsolator;
	CGeoWall m_zgQuerstange2;
	CGeoWall m_zgGeneratorKasten;
	CGeoCylinder m_zgStecka;
	CGeoSphere m_zgKugel;
	CGeoCylinder m_zgKabelMitte;
	CGeoCylinder m_zgKabelSeite;



public:
	VModelTransformerStation();
	virtual ~VModelTransformerStation() override;

	virtual float getHeight() override
	{
		//return 11.0f;
		return 0.3f + 7.0f + 1.3f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

};


NAMESPACE_VIEW_E
