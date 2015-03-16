#pragma once
#include "TriangleList.h"

namespace Vektoria
{

class CApiRender;

class CGeoEllipsoidTiled :
	public CTriangleList
{
public:
	CGeoEllipsoidTiled(void);
	~CGeoEllipsoidTiled(void);
    virtual const char* ClassName(void) { return "CGeoEllipsoidTiled"; }

	void Init(CHVector vSize, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, int iLattitudeMin = 0, int iLattitudeMax = INT_MAX, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Initialisiert eine ellisoide Geometrie 

	CHVector m_vSize;
	CVertex * m_avertex;

	int m_iLongitude;
	int m_iLattitude;
private:
	int GetVertexIndex(int iLo, int iLa, int iCounterclock);

	void CalcMapping(float & frU, float & frV, int iLo, int iLa, int iLongitude, int iLattitude, CHVector & vTangent, CHVector & vBitangent, CHVector v, CHVector vSize, EMapping eMapping, int iRepeatUV);


};

}