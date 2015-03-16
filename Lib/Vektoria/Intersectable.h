////////////////////////////////////////////////////
/// @file Intersectable.h
/// @author Matthias Sommer
/// ** Copyright (c) Matthias Sommer **
////////////////////////////////////////////////////
#pragma once

#include "../VektoriaMath/HVector.h"

namespace Vektoria
{

class CIntersectable
{
public:
	CIntersectable(void) {}
	~CIntersectable(void) {}

    virtual bool Intersects(CHVector &a_vOrigin, CHVector &a_vRayDirection, CIntersectable** r_pFound, float* r_fDistance) = 0; // Führt eine Ray/AABB Intersection durch und gibt bei erfolgreicher Intersection den Knoten der zuerst gefunden wurde über r_pFound zurück.
};

}