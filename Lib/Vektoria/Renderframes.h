#pragma once

#include "Renderframe.h"

//------------------------------------
// CRenderframes, Pluralklasse von CRenderframe
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

class CRenderframes
{
public:
	CRenderframes();
	~CRenderframes();
	CRenderframes operator=(CRenderframes renderframes);

	void Init();
	void Tick(float & fTimeDelta);
	void Fini();

	void Add(CRenderframe * prenderframe);
	bool Sub(CRenderframe * prenderframe);

	void SetRoot(CRoot * proot);


	CRenderframe * Make(int eRenderApi, HWND hwnd, int iWidthWindow, int iHeightWindow);
	bool Kill(CRenderframe * prenderframe);

	CRenderframe ** m_aprenderframe;
	int m_iRenderframeAllocs;
	int m_iAllocBlock;
	int m_iRenderframes;
	CRoot * m_proot;

};
