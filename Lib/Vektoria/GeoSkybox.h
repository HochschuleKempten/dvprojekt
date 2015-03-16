#pragma once
#include "TriangleList.h"
#include "Vertex.h"
#include "Face.h"
#include "ParallelLight.h"

//------------------------------------------------------------------
// CGeSkybox: Klasse für eine Skybox
//
// Autor: Michael Rücker
// Letzte Änderung: 2013-10-28
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