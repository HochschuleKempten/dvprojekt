#pragma once
#include "TriangleList.h"

//------------------------------------------------------------------
// CGeoTriangle: Klasse f�r ein 2D Dreieck im Raum
// Autor: Prof. Dr. Tobias Breiner 
// 
// Anmerkung: Aus Performanzgr�nden wurden keine Schleifen verwendet.
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoTriangle :
	public CTriangleList
{
public:
	CGeoTriangle(void);
	~CGeoTriangle(void);

	void Init(float fWidth, float fHeight, CMaterial * pmaterial); // Initialisiert eine Geometrie mit Triangle 
	CVertex m_avertex[3];

};

}