#pragma once

#include "Viewport.h"

//------------------------------------
// CViewports, Pluralklasse von CViewport
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CViewports
{
public:
	CViewports();
	~CViewports();
	CViewports operator=(CViewports viewports);

	void Init();
	void Tick(float & fTimeDelta, bool & bTickTack);
	void Fini();

	void Add(CViewport * pviewport);
	bool Sub(CViewport * pviewport);

	CViewport * Make(CCamera * pcamera, float frx, float fry, float frWidth, float frHeight);
	bool Kill(CViewport * pviewport);


	void ReSize();

	CViewport ** m_apviewport;
	int m_iViewportAllocs;
	int m_iAllocBlock;
	int m_iViewports;
	CFrame * m_pframe;
	void SetRoot(CRoot * proot);
	void SetFrame(CFrame * pframe);
	CRoot * m_proot;

};

}