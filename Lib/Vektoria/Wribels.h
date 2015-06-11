#pragma once

#include "Wribel.h"

//------------------------------------
// CWribels, Pluralklasse von CWribel
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

	class CWribels
	{
		friend class CPlacement;
	protected: 
		void Tick(CHMat & mGlobalFather, float & fTimeDelta, bool & bTick);
	public:
		CWribels();
		~CWribels();
		CWribels operator=(CWribels & wribels);

		void Init();
		void Fini();

		void Add(CWribel * pwribel);
		bool Sub(CWribel * pwribel);

		CWribel * Make(CFloatRect & floatrect, int ixChars, CWritingFont * pwritingfont);
		bool Kill(CWribel * pwribel);

		void Draw(CCamera * pcamera, CHMat & mGlobalFather, int & itFatherIsInFrustum, bool & bTickTack);

		CWribel ** m_apwribel;
		int * m_aiInst;
		int m_iWribelAllocs;
		int m_iAllocBlock;
		int m_iWribels;
	};
}