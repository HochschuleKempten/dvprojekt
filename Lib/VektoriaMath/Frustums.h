#pragma once

#include "Frustum.h"

//------------------------------------
// CFrustums, Pluralklasse von CFrustum
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------
namespace Vektoria
{


	class CFrustums
	{
	public:
		CFrustums();
		~CFrustums();
		CFrustums operator=(CFrustums frustums);

		void Init();
		void Fini();

		void Add(CFrustum * pfrustum);
		bool Sub(CFrustum * pfrustum);

		CFrustum * Make(CRay r, CHVector vNormalRight, float faHorizontal, float faVertical);
		bool Kill(CFrustum * pfrustum);

		CFrustum ** m_apfrustum;
		int m_iFrustumAllocs;
		int m_iAllocBlock;
		int m_iFrustums;
	};
}