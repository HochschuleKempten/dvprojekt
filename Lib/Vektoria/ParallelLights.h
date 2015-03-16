#pragma once

#include "ParallelLight.h"

//------------------------------------
// CParallelLights, Pluralklasse von CParallelLight
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CParallelLights
{
public:
	CParallelLights();
	~CParallelLights();
	CParallelLights operator=(CParallelLights & parallellights);

	void Init();
	void Tick(CHMat & m, float & fTimeDelta, bool & bTick);
	void Fini();

	void Add(CParallelLight * pparallellight);
	bool Sub(CParallelLight * pparallellight);

	CParallelLight * Make(CHVector vDirection, CColor color);
	bool Kill(CParallelLight * pparallellight);

	CParallelLight ** m_apparallellight;
	int m_iParallelLightAllocs;
	int m_iAllocBlock;
	int m_iParallelLights;
};

}