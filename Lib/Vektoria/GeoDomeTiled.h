#pragma once
#include "geoellipsoidtiled.h"

namespace Vektoria
{

class CGeoDomeTiled :
	public CGeoEllipsoidTiled
{
public:
	CGeoDomeTiled(void);
	~CGeoDomeTiled(void);

	void Init(float fRadius, float fHeight, CMaterial * pmaterial, bool bSkyDome = false, int iLongitude = 24, int iLattitude = 12,  EMapping eMapping = eMapping_Cylindrical);  // Erzeugt Kuppel

};

}