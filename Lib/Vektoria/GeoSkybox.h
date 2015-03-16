#pragma once
#include "TriangleList.h"
#include "Vertex.h"
#include "Face.h"
#include "ParallelLight.h"

//------------------------------------------------------------------
// CGeSkybox: Klasse f�r eine Skybox
//
// Autor: Michael R�cker
// Letzte �nderung: 2013-10-28
//-------------------------------------------------------------------

namespace Vektoria
{

class CApiRender;

class CGeoSkybox :
	public CTriangleList
{
public:
	CGeoSkybox(void);
	~CGeoSkybox(void);

	void Init(CHVector vSize, CMaterial * pmaterial, CParallelLight * pParallelLight); 

	float m_fSize;
	CVertex m_avertex[24];
};

}