#pragma once

#include "Frame.h"

//------------------------------------
// CFrames, Pluralklasse von CFrame
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CFrames
{
public:
	CFrames();
	~CFrames();
	CFrames operator=(CFrames frames);

	void Init();
	void Tick(float & fTimeDelta, bool & bTickTack);
	void Fini();

	void Add(CFrame * pframe);
	bool Sub(CFrame * pframe);



	CFrame * Make(HWND hwnd, EApiRender eApiRender, EApiInput eApiInput);
	bool Kill(CFrame * pframe);

	CFrame ** m_apframe;
	int m_iFrameAllocs;
	int m_iAllocBlock;
	int m_iFrames;

	void SetRoot(CRoot * proot);

	CRoot * m_proot;

};

}