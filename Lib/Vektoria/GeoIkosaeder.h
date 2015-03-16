#pragma once
#include "TriangleList.h"
// #include "Vertex.h"

namespace Vektoria
{

class CGeoIkosaeder :
	public CTriangleList
{
public:
	CGeoIkosaeder(void);
	~CGeoIkosaeder(void);
	CHVector GetPoint(int i);
	void Init(CHVector vSize, CMaterial * pmaterial,  bool bFlip = false); // Initialisiert eine Geometrie mit Wuerfel 
	void MakeFace(int iA, int iB, int iC, int & iIndex);

	CHVector m_avPoint[12];
	CVertex m_avertex[60];
//	CMaterial * m_pmaterial;
};

}