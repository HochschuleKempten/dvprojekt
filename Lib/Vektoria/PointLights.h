#pragma once

#include "PointLight.h"

//------------------------------------
// CPointLights, Pluralklasse von CPointLight
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CPointLights
{
public:
	CPointLights();
	~CPointLights();
	CPointLights operator=(CPointLights pointlights);

	void Init();
	void Tick(CHMat & m,float & fTimeDelta, bool & bTick);
	void Fini();

	void Add(CPointLight * ppointlight);
	bool Sub(CPointLight * ppointlight);

	CPointLight * Make(CColor color);
	bool Kill(CPointLight * ppointlight);

	CPointLight ** m_appointlight;
	int m_iPointLightAllocs;
	int m_iAllocBlock;
	int m_iPointLights;
};

}