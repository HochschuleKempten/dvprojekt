#pragma once
#include "geoellipsoidtiled.h"

#include "DistributedGlobal.h"

namespace Vektoria
{

class CGeoSphereTiled : 
    public CGeoEllipsoidTiled
{
public:
	CGeoSphereTiled(void);
	~CGeoSphereTiled(void);
    virtual const char* ClassName(void) { return "CGeoSphereTiled"; }

	void Init(float fRadius, CMaterial * pmaterial, int iLongitude = 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Erzeugt getilte Kugel

};

}