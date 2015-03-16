#pragma once

#include "TriangleStrip.h"

//------------------------------------
// CTriangleStrips, Pluralklasse von CTriangleStrip
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CTriangleStrips
{
public:
	CTriangleStrips();
	~CTriangleStrips();
	CTriangleStrips operator=(CTriangleStrips trianglestrips);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Add(CTriangleStrip * ptrianglestrip);
	bool Sub(CTriangleStrip * ptrianglestrip);

	CTriangleStrip * Make();
	bool Kill(CTriangleStrip * ptrianglestrip);

	CTriangleStrip ** m_aptrianglestrip;
	int m_iTriangleStripAllocs;
	int m_iAllocBlock;
	int m_iTriangleStrips;
};

}