#pragma once
#include "GeoWing.h"

namespace Vektoria
{


//------------------------------------
// CGeoWings, Pluralklasse von CGeoWing
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

class CGeoWings
{
	friend class CGeo;
	friend class CGeos;
public:
	CGeoWings();
	~CGeoWings();
	CGeoWings operator=(CGeoWings geowings);

	void Init();
//	void Tick(float & fTimeDelta);
	void Tick(CHMat &mGlobal);

	void Fini();

	void Add(CGeoWing * pgeowing);
	bool Sub(CGeoWing * pgeowing);

//	CGeoWing * Make(float fHeight, float fThickness, CHVectors * phvectorsFootPrint, CHVectors * phvectorsRoofPrint, bool * abRoof);
//	bool Kill(CGeoWing * pgeowing);

	CGeoWing ** m_apgeowing;
	int m_iGeoWingAllocs;
	int m_iAllocBlock;
	int m_iGeoWings;
};
}