#pragma once
#include "geosweep.h"

namespace Vektoria
{

class CGeoSlice :
	public CGeoSweep
{
public:
	CGeoSlice(void);
	~CGeoSlice(void);

	void Init(float fLength, float fRadius, float faArcStart, float faArcStop, CMaterial * pmaterial, int iLongitude = 24, bool bHasFront = true, bool bHasBack = true,bool bIsPlanarBottom = true); // Initialisiert eine Zylinder-Geometrie, fRadiusBottom = Radius des Basis, fRadiusTop = Radius des Spitze, Height = Höhe des Kegels, iLongitude = Anzahl der radialen Vertices, bHasBottom = true, wenn Boden damei  


};

}