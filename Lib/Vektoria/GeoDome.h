#pragma once
#include "geoellipsoid.h"

namespace Vektoria
{

class CGeoDome :
	public CGeoEllipsoid
{
public:
	CGeoDome(void);
	~CGeoDome(void);

	void Init(float fRadius, float fHeight, CMaterial * pmaterial, bool bSkyDome = false, int iLongitude = 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical); // Erzeugt Kuppel

};

}