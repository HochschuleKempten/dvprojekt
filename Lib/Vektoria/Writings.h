#pragma once

#include "Writing.h"

//------------------------------------
// CWritings, Pluralklasse von CWriting
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 24.09.2012
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CWritings
{
public:
	CWritings();
	~CWritings();
	CWritings operator=(CWritings & writings);

	void Init();
	void Tick(float & fTimeDelta, CFloatRect & floatrectFather);
	void Fini();

	void Add(CWriting * pwriting);
	bool Sub(CWriting * pwriting);

	CWriting * Make(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont);
	bool Kill(CWriting * pwriting);

	CWriting ** m_apwriting;
	int m_iWritingAllocs;
	int m_iAllocBlock;
	int m_iWritings;

	void SetViewport(CViewport * pviewport);

	CViewport * m_pviewport;
};

}