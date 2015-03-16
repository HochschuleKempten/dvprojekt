#pragma once

#include "Color.h"

//------------------------------------
// CColors, Pluralklasse von CColor
// 
// Autor: Prof. Dr. Tobias Breiner
// Pfungstadt, 11.10.2011
//------------------------------------

namespace Vektoria
{

class CColors
{
public:
	CColors();
	CColors operator=(CColors colors);

	void Init();
	void Fini();

	void Add(CColor * pcolor);
	bool Sub(CColor * pcolor);

	CColor * Make(float fx, float fy, float fz, float fa);
	bool Kill(CColor * pcolor);

	CColor ** m_apcolor;
	int m_iColorAllocs;
	int m_iAllocBlock;
	int m_iColors;
};

}