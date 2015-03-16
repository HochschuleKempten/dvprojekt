#pragma once

#include "TriangleList.h"

//------------------------------------
// CTriangleLists, Pluralklasse von CTriangleList
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CTriangleLists
{
	friend class CGeos;
	friend class CGeoWing;
public:
	CTriangleLists();
	~CTriangleLists();
	CTriangleLists operator=(CTriangleLists trianglelists);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Add(CTriangleList * ptrianglelist);
	bool Sub(CTriangleList * ptrianglelist);

	CTriangleList * Make();
	bool Kill(CTriangleList * ptrianglelist);

	CTriangleList ** m_aptrianglelist;
	int m_iTriangleListAllocs;
	int m_iAllocBlock;
	int m_iTriangleLists;
};

}