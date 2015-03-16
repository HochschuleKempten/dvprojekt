#pragma once

#include "Face.h"

//------------------------------------
// CFaces, Pluralklasse von CFace
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CFaces
{
public:
	CFaces();
	~CFaces();
	CFaces operator=(CFaces faces);

	void Init();
	void Fini();

	void Add(CFace * pface);
	bool Sub(CFace * pface);

	CFace * Make(CVertex * pvertexA, CVertex * pvertexB, CVertex * pvertexC);
	bool Kill(CFace * pface);

	CFace ** m_apface;
	int m_iFaceAllocs;
	int m_iAllocBlock;
	int m_iFaces;
};

}