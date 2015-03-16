#pragma once

#include "Drawable.h"

//------------------------------------
// CDrawables, Pluralklasse von CDrawable
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CDrawables
{
public:
	CDrawables();
	~CDrawables();
	CDrawables operator=(CDrawables drawables);

	void Init();
	void Tick(CHMat & m, bool & bTick);
	void Fini();

	void Add(CDrawable * pdrawable);
	bool Sub(CDrawable * pdrawable);

	CDrawable * Make();
	bool Kill(CDrawable * pdrawable);

	bool HasTransparent();


	CDrawable ** m_apdrawable;
	int m_iDrawableAllocs;
	int m_iAllocBlock;
	int m_iDrawables;
};

}