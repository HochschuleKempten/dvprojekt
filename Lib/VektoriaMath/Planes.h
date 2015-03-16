#pragma once

#include "Plane.h"

//------------------------------------
// CPlanes, Pluralklasse von CPlane
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CPlanes
{
public:
	CPlanes();
	~CPlanes();
	CPlanes operator=(CPlanes planes);

	void Init();
	void Fini();

	void Add(CPlane * pplane);
	bool Sub(CPlane * pplane);

	CPlane * Make(CHVector * pvA, CHVector * pvB, CHVector * pvC);
	bool Kill(CPlane * pplane);

	CPlane ** m_applane;
	int m_iPlaneAllocs;
	int m_iAllocBlock;
	int m_iPlanes;
};

}