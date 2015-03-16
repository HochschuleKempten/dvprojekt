#pragma once

#include "IntRect.h"

//------------------------------------
// CIntRects, Pluralklasse von CIntRect
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CIntRects
{
public:
	CIntRects();
	~CIntRects();
	CIntRects operator=(CIntRects intrects);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CIntRect * pintrect);
	bool Sub(CIntRect * pintrect);

	CIntRect * Make(int ixPos, int iyPos, int ixSize, int iySize);
	bool Kill(CIntRect * pintrect);

	CIntRect ** m_apintrect;
	int m_iIntRectAllocs;
	int m_iAllocBlock;
	int m_iIntRects;
};

}