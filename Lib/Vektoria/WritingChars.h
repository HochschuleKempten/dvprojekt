#pragma once

#include "WritingChar.h"

//------------------------------------
// CWritingChars, Pluralklasse von CWritingChar
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 01.06.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{


	class CWritingChars
	{
	public:
		CWritingChars();
		~CWritingChars();
		CWritingChars operator=(CWritingChars & writingchars);

		void Init();
		void Tick(float & fTimeDelta, CFloatRect & floatrectFather, bool bBehind);
		void Fini();

		void Add(CWritingChar * pwritingchar);
		bool Sub(CWritingChar * pwritingchar);

		CWritingChar * Make(CFloatRect & floatrect, CWritingFont * pwritingfont);
		bool Kill(CWritingChar * pwritingchar);

		CWritingChar ** m_apwritingchar;
		int m_iWritingCharAllocs;
		int m_iAllocBlock;
		int m_iWritingChars;
	};

}