#pragma once

#include "GeoWindow.h"

//------------------------------------
// CGeoWindows, Pluralklasse von CGeoWindow
// 
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt, 05.09.2013
// Copyright: Moyzelle Vektoria
//------------------------------------

namespace Vektoria
{

class CGeoWindows
{
public:
	CGeoWindows();
	~CGeoWindows();
	CGeoWindows operator=(CGeoWindows geowindows);

	void Init();
	void Fini();

	void Add(CGeoWindow * pgeowindow);
	bool Sub(CGeoWindow * pgeowindow);

	CGeoWindow * Make(CFloatRect floatrect, EGeoWindowStyle eStyle, bool bAbsolute, float frRadius, float frRectHeight, int iGranularity);
	bool Kill(CGeoWindow * pgeowindow);

	CGeoWindow ** m_apgeowindow;
	int m_iGeoWindowAllocs;
	int m_iAllocBlock;
	int m_iGeoWindows;
};
}