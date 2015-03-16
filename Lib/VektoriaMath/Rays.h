#pragma once

#include "Ray.h"

//------------------------------------
// CRays, Pluralklasse von CRay
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CRays
{
public:
	CRays();
	~CRays();
	CRays operator=(CRays rays);

	void Init();
	void Fini();

	void Add(CRay * pray);
	bool Sub(CRay * pray);

	CRay * Make(CHVector & vOrigin, CHVector & vDirection);
	bool Kill(CRay * pray);

	CRay ** m_apray;
	int m_iRayAllocs;
	int m_iAllocBlock;
	int m_iRays;
};

}