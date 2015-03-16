////////////////////////////////////////////////////
// Klasse: AABB.h
// Von Tobias Breiner komplett neu geschrieben
////////////////////////////////////////////////////

#pragma once

#include "HVector.h"
#include "HMAt.h"
#include "Ray.h"

namespace Vektoria
{

	class CAABB
	{
	public:
		CAABB(void);
		CAABB(CHVector &vMin, CHVector &vMax);

		CAABB Transform(CHMat & m);

		void AddAABB(CAABB &aabb);
		void AddAABB(CAABB &aabb, CHMat & m);
		void AddAABBMax(CAABB &aabb, CHMat & m);
		void AddRadius(float & fRadius, CHMat & m);
		void AddMax();

		void AddVector(CHVector &vPos);
		bool IsInside(CHVector &vPos);
		bool Intersects(CAABB &aabb);
		bool Intersects(CHVector &origin, CHVector &direction, float* r_fDistance);

		bool Intersects(CRay & r);



		CHVector GetMid(); 
		CHVector &GetMin(void) { return m_vMin; }
		CHVector &GetMax(void) { return m_vMax; }
		CHVector GetSize(void) { return m_vMax - m_vMin; }

		void Copy(CAABB &aabb) { m_vMin = aabb.m_vMin; m_vMax = aabb.m_vMax; }

		CHVector m_vMin;
		CHVector m_vMax;

		CHVector m_av[8];
		CHVector m_avGlobal[8];
		bool m_bClear;
	private:
		void CalcCube();


	};

}