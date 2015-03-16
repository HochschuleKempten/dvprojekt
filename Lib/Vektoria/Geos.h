#pragma once

#include "Geo.h"

//------------------------------------
// CGeos, Pluralklasse von CGeo
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CGeos
{
	friend class CPlacement;
	friend class CTriangleLists;
	friend class CTriangleList;
	friend class CGeoWings;
	friend class CGeoWing;
	friend class CGeo;
private:
	void Tick(CHMat & m, bool & bTick);

public:
	CGeos();
	~CGeos();
	CGeos operator=(CGeos geos);

	void Init();
	void Fini();

	void Add(CGeo * pgeo);
	bool Sub(CGeo * pgeo);
	bool AddOnce(CGeo * pgeo); // Fügt pgeo nur hinzu, wenn es noch nicht in der Liste vorhanden ist

	bool HasTransparent();
	bool Has(CGeo * pgeo); // Schaut, ob pgeo in der Liste vorhanden ist, gibt true aus, falls ja

	CGeo * Make();
	bool Kill(CGeo * pgeo);

	CGeo ** m_apgeo;
	int m_iGeoAllocs;
	int m_iAllocBlock;
	int m_iGeos;
};

}