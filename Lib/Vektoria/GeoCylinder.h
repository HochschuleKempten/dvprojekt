#pragma once
#include "GeoSweep.h"

namespace Vektoria
{

class CGeoCylinder :
	public CGeoSweep
{
public:
	CGeoCylinder(void);
	~CGeoCylinder(void);

	void Init(float fRadiusBottom, float fRadiusTop, float fHeight, CMaterial * pmaterial, int iLongitude = 24, bool bHasBottom = true, bool bHasTop = true); // Initialisiert eine Zylinder-Geometrie, fRadiusBottom = Radius des Basis, fRadiusTop = Radius des Spitze, Height = Höhe des Kegels, iLongitude = Anzahl der radialen Vertices, bHasBottom = true, wenn Boden damei  

};

}