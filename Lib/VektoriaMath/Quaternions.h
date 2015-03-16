#pragma once

#include "Quaternion.h"

//------------------------------------
// CQuaternions, Pluralklasse von CQuaternion
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CQuaternions
{
public:
	CQuaternions();
	~CQuaternions();
	CQuaternions operator=(CQuaternions quaternions);

	void Init();
//	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CQuaternion * pquaternion);
	bool Sub(CQuaternion * pquaternion);

	CQuaternion * Make(float fx, float fy, float fz, float fw);
	bool Kill(CQuaternion * pquaternion);

	CQuaternion ** m_apquaternion;
	int m_iQuaternionAllocs;
	int m_iAllocBlock;
	int m_iQuaternions;
};

}