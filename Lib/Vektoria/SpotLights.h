#pragma once

#include "SpotLight.h"

//------------------------------------
// CSpotLights, Pluralklasse von CSpotLight
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CSpotLights
{
public:
	CSpotLights();
	~CSpotLights();
	CSpotLights operator=(CSpotLights spotlights);

	void Init();
	void Tick(CHMat & m, float & fTimeDelta, bool & bTick);
	void Fini();

	void Add(CSpotLight * pspotlight);
	bool Sub(CSpotLight * pspotlight);

	CSpotLight * Make(CColor color, float fInnerAngle, float fOuterAngle, float fIntensity);
	bool Kill(CSpotLight * pspotlight);

	CSpotLight ** m_apspotlight;
	int m_iSpotLightAllocs;
	int m_iAllocBlock;
	int m_iSpotLights;
};

}