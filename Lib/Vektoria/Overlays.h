#pragma once

#include "Overlay.h"

//------------------------------------
// COverlays, Pluralklasse von COverlay
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 11.10.2011
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class COverlays
{
public:
	COverlays();
	~COverlays();
	COverlays operator=(COverlays overlays);

	void Init();
	void Tick(float & fTimeDelta, CFloatRect & floatrectFather, bool bBehind = false);
	void Fini();

	void Add(COverlay * poverlay);
	bool Sub(COverlay * poverlay);

	COverlay * Make(CImage * pimage, CFloatRect & floatrect);
	bool Kill(COverlay * poverlay);

	void SetViewport(CViewport * pviewport);
	void SetInnerOn();
	void SetInnerOff();
	void SetBehindOn();
	void SetBehindOff();

	COverlay ** m_apoverlay;
	int m_iOverlayAllocs;
	int m_iAllocBlock;
	int m_iOverlays;
	CViewport * m_pviewport;
};

}