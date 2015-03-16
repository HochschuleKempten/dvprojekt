#pragma once
#include "Light.h"

//---------------------------------------------------
// CPointLight: Klasse für Spotlight
//
// Autoren: Florian Schnell & Patrick Fleischmann
// Letzte Änderung: 2013-10-13
//---------------------------------------------------

namespace Vektoria
{

class CSpotLight : public CLight
{
public:
	CSpotLight();
	~CSpotLight();
	CSpotLight operator=(CSpotLight spotlight);
	void Copy(CSpotLight spotlight);

	void Init(CColor color, float fInnerAngle, float fOuterAngle);
	void Init(CColor color, float fInnerAngle, float fOuterAngle, float fIntensity);
	void Fini();

	
	void SetMaxDistance(float fMaxDistance);
	void SetMinDistance(float fMinDistance);

	void SetOuterAngle(float fAngle);
	void SetInnerAngle(float fAngle);
	void SetAngles(float fInner, float fOuter);
	void SetRadius(float fRadius);

	float m_fFarClipping;
	float m_fNearClipping;
	float m_fOuterAngle;
	float m_fOuterCosAngle;
	float m_fInnerAngle;
	float m_fInnerCosAngle;

	void SetShadowOff();
	void SetShadowOn();
	void SetSoftShadowOn();
	void SetCascadedShadowOn();

	bool m_bSoftShadow;
	//Funktioniert nur mit m_bSoftShadows = true
	bool m_bCascadedShadow;
	float m_fRadius;
};

}