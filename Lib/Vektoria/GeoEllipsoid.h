#pragma once
#include "TriangleStrip.h"
#include "Face.h"

namespace Vektoria
{

class CApiRender;


class CGeoEllipsoid :
	public CTriangleStrip
{
public:
	CGeoEllipsoid(void);
	~CGeoEllipsoid(void);
    virtual const char* ClassName(void) { return "CGeoEllipsoid"; }

	int GetVertexIndex(int iLo, int iLa);

	void Init(CHVector vSize, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, int iLattitudeMin = 0, int iLattitudeMax = INT_MAX, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Initialisiert eine ellisoide Geometrie 

	CHVector m_vSize;
	CVertex * m_avertex;

	int m_iLongitude;
	int m_iLattitude;
};

}