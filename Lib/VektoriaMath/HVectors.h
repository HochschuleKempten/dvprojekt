#pragma once

#include "HVector.h"

//------------------------------------
// CHVectors, Pluralklasse von CHVector
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 10.10.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CHVectors
{
public:
	CHVectors();
	CHVectors operator=(CHVectors hvectors);

	void Init();
	void Fini();

	void Add(CHVector * phvector);
	bool Sub(CHVector * phvector);

	CHVector * Make(float fx, float fy, float fz, float fw);
	bool Kill(CHVector * phvector);

	CHVector Mid(); // Rechnet arithmetischen Mittelpunkt aller Vektoren aus

	CHVector ** m_aphvector;
	int m_iHVectorAllocs;
	int m_iAllocBlock;
	int m_iHVectors;
};

}