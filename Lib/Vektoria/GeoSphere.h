#pragma once
#include "geoellipsoid.h"

#include "DistributedGlobal.h"

namespace Vektoria
{

class CGeoSphere : 
    public CGeoEllipsoid
{
public:
	CGeoSphere(void);
	~CGeoSphere(void);
    virtual const char* ClassName(void) { return "CGeoSphere"; }

	void Init(float fRadius, CMaterial * pmaterial, int iLongitude= 24, int iLattitude = 12, EMapping eMapping = eMapping_Cylindrical, int iRepeatUV = 1); // Erzeugt Kugel

};

}