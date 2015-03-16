#pragma once

#include "GeoWall.h"
#include "Geos.h"

//------------------------------------
// CGeoWalls, Pluralklasse von CGeoWall
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 24.07.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CRoot;
class CGeoWalls
{
public:
	CGeoWalls();
	~CGeoWalls();
	CGeoWalls operator=(CGeoWalls geowalls);

	void Init();
	void Tick(CHMat & m, float & fTimeDelta, bool & bTick);
	void Fini();

	void Add(CGeoWall * pgeowall);
	bool Sub(CGeoWall * pgeowall);

	CGeoWall * Make(float fWidth, float fHeight, float fThickness, CMaterial * pMaterial, bool bLeft, bool bRight, bool bBottom, bool bTop, bool bFront, bool bBack);
	bool Kill(CGeoWall * pgeowall);

	void Draw(float fDistanceToCameraSquare, CHMat & mGlobal);

//	void Draw(CCamera * pcamera, float fDistanceToCameraSquare, CHMat & mGlobal, int & itFatherIsInFrustum);
	void Transform(CHMat & m);

	CGeoWall ** m_apgeowall;
	int m_iGeoWallAllocs;
	int m_iAllocBlock;
	int m_iGeoWalls;

};

}