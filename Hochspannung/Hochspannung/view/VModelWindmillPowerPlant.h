#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VModelWindmillPowerPlant : public CPlacement
{
private:
	CPlacement m_zpWindkraftanlage;
	CPlacement m_zpBasis;
	CPlacement m_zpTurm;
	CPlacement m_zpFundament;
	CPlacement m_zpNetzanschluss;
	CPlacement m_zpKopf;
	CPlacement m_zpGondel;
	CPlacement m_zpRotorblatt1;
	CPlacement m_zpRotorblatt2;
	CPlacement m_zpRotorblatt3;

	CGeoCylinder m_zgTurm;
	CGeoWall m_zgFundament;
	CGeoWall m_zgNetzanschluss;
	CGeoEllipsoid m_zgGondel;
	CGeoEllipsoid m_zgRotorblatt;

	CMaterial m_zm;

public:
	VModelWindmillPowerPlant();
	~VModelWindmillPowerPlant();

	inline void rotate(const float angle)
	{
		m_zpKopf.RotateZDelta(angle);
	}
};


NAMESPACE_VIEW_E
