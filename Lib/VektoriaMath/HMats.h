#pragma once

#include "HMat.h"

//------------------------------------
// CHMats, Pluralklasse von CHMat
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CHMats
{
public:
	CHMats();
	CHMats operator=(CHMats hmats);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CHMat * phmat);
	bool Sub(CHMat * phmat);

	CHMat * Make(float fx00, float fx01, float fx02, float fx03, float fx10, float fx11, float fx12, float fx13, float fx20, float fx21, float fx22, float fx23, float fx30, float fx31, float fx32, float fx33);
	bool Kill(CHMat * phmat);

	CHMat ** m_aphmat;
	int m_iHMatAllocs;
	int m_iAllocBlock;
	int m_iHMats;
};

}