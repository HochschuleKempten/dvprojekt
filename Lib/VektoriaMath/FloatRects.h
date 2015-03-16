#pragma once

#include "FloatRect.h"

//------------------------------------
// CFloatRects, Pluralklasse von CFloatRect
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CFloatRects
{
public:
	CFloatRects();
	CFloatRects operator=(CFloatRects floatrects);

	void Init();
	void Fini();

	void Add(CFloatRect * pfloatrect);
	bool Sub(CFloatRect * pfloatrect);

	CFloatRect * Make(float fxPos, float fyPos, float fxSize, float fySize);
	bool Kill(CFloatRect * pfloatrect);

	CFloatRect ** m_apfloatrect;
	int m_iFloatRectAllocs;
	int m_iAllocBlock;
	int m_iFloatRects;
};

}