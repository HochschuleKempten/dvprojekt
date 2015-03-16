#pragma once
#include "TriangleList.h"

//------------------------------------------------------------------
// CGeoTetraeder: Klasse f�r eine Tetraeder-Geometrie
// Autor: Prof. Dr. Tobias Breiner 
// 
// Anmerkung: Aus Performanzgr�nden wurden keine Schleifen verwendet.
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTetraeder :
	public CTriangleList
{
public:
	CGeoTetraeder(void);
	~CGeoTetraeder(void);

	void Init(CHVector vSize, CMaterial * pmaterial, bool bFlip=false); // Initialisiert eine Geometrie mit Tetraeder 

	float m_fSize;
	CVertex m_avertex[12];
//	CFace m_aface[4];
};

}