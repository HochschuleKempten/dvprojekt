#pragma once
#include "TriangleList.h"

//------------------------------------------------------------------
// CGeoFrustum: Klasse zum Erzeugen einer OPyramidenstumpfgeometrie
//
// Autor: Prof. Dr. Tobias Breiner
//-------------------------------------------------------------------



namespace Vektoria
{

	class CGeoFrustum : public CTriangleList
	{
	public:
		CGeoFrustum();
		~CGeoFrustum();
		void Init(float fzHeight, float fxBaseX, float fyBase, float fxTop, float fyTop, CMaterial * pmaterial, float fTextureRepeat = 1, bool bFlip = false);
		void Init(CCamera & camera, CMaterial & material);
		CVertex m_avertex[24];

	};

}
