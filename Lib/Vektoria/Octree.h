#pragma once

#include "../VektoriaMath/AABB.h"
#include "Vertexs.h"
//------------------
// Klasse COctree
// Autor: Tobas Breiner
//--------------------

namespace Vektoria
{

class COctree
{
public:
	COctree(CAABB aabb, int iDepth, COctree * poctreeParent);
	~COctree(void);

	void AddVertex(CAABB aabb, CVertex * pvertex);
	void UniteVerticesLocation();
	void UniteVerticesSame();

	COctree * m_poctreeParent;
	COctree * m_apoctreeChild[2][2][2];
	COctree * m_apoctreeNeigbor[6];
	CVertexs * m_pvertices; 
	CAABB m_aabb;
	int m_iMaxDepth;
	int m_iDepth;
};

}