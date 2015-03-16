#pragma once
#include "GeoSweep.h"

namespace Vektoria
{

class CGeoCone :
	public CGeoSweep
{
public:
	CGeoCone(void);
	~CGeoCone(void);

	void Init(float fRadius, float fHeight, CMaterial * pmaterial, int iLongitude = 24, bool bHasBottom = true); // Initialisiert eine Kegel-Geometrie, fRadius = Radius des Basis, fHeight = Höhe des Kegels, iLongitude = Anzahl der radialen Vertices, bHasBottom = true, wenn Boden damei  

};

}