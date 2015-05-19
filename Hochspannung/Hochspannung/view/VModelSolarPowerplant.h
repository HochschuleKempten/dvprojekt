#pragma once

#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


class VModelSolarPowerPlant : public IViewModel
{
private:

	//Placements LOD 0
	CPlacement m_zpStabilisierung;
	CPlacement m_zpCamera;
	CPlacement m_zpSolarPowerplant;
	CPlacement m_zpSockel;
	CPlacement m_zpGrundflaeche;
	CPlacement m_zpSenkrechte;
	CPlacement m_zpZelle1;
	CPlacement m_zpZelle2;
	CPlacement m_zpZelle3;
	CPlacement m_zpZelle4;
	CPlacement m_zpZelle5;
	CPlacement m_zpZelle6;
	CPlacement m_zpZelle7;
	CPlacement m_zpZelle8;
	CPlacement m_zpZelle9;
	CPlacement m_zpZelle10;
	CPlacement m_zpZelle11;
	CPlacement m_zpZelle12;
	CPlacement m_zpZelle13;
	CPlacement m_zpZelle14;
	CPlacement m_zpZelle15;
	CPlacement m_zpZelle16;
	CPlacement m_zpZelle17;
	CPlacement m_zpZelle18;
	CPlacement m_zpZelle19;
	CPlacement m_zpZelle20;
	CPlacement m_zpZelle21;
	CPlacement m_zpZelle22;
	CPlacement m_zpZelle23;
	CPlacement m_zpZelle24;
	CPlacement m_zpZelle25;
	CPlacement m_zpZelle26;
	CPlacement m_zpZelle27;
	CPlacement m_zpZelle28;
	CPlacement m_zpZelle29;
	CPlacement m_zpZelle30;
	CPlacement m_zpZelle31;
	CPlacement m_zpZelle32;
	CPlacement m_zpZelle33;
	CPlacement m_zpZelle34;
	CPlacement m_zpZelle35;
	CPlacement m_zpZelle36;
	CPlacement m_zpZelle37;
	CPlacement m_zpZelle38;
	CPlacement m_zpZelle39;
	CPlacement m_zpZelle40;
	CPlacement m_zpZelle41;
	CPlacement m_zpZelle42;

	

	CGeoCube m_zgStabilisierung;
	CGeoCylinder m_zgSenkrechte;
	CGeoCube m_zgSockel;
	CGeoCube m_zgGrundflaeche;
	CGeoCube m_zgSolarzelle1;
	CGeoCube m_zgSolarzelle2;
	CGeoCube m_zgSolarzelle3;
	CGeoCube m_zgSolarzelle4;
	CGeoCube m_zgSolarzelle5;
	CGeoCube m_zgSolarzelle6;
	CGeoCube m_zgSolarzelle7;
	CGeoCube m_zgSolarzelle8;
	CGeoCube m_zgSolarzelle9;
	CGeoCube m_zgSolarzelle10;
	CGeoCube m_zgSolarzelle11;
	CGeoCube m_zgSolarzelle12;
	CGeoCube m_zgSolarzelle13;
	CGeoCube m_zgSolarzelle14;
	CGeoCube m_zgSolarzelle15;
	CGeoCube m_zgSolarzelle16;
	CGeoCube m_zgSolarzelle17;
	CGeoCube m_zgSolarzelle18;
	CGeoCube m_zgSolarzelle19;
	CGeoCube m_zgSolarzelle20;
	CGeoCube m_zgSolarzelle21;
	CGeoCube m_zgSolarzelle22;
	CGeoCube m_zgSolarzelle23;
	CGeoCube m_zgSolarzelle24;
	CGeoCube m_zgSolarzelle25;
	CGeoCube m_zgSolarzelle26;
	CGeoCube m_zgSolarzelle27;
	CGeoCube m_zgSolarzelle28;
	CGeoCube m_zgSolarzelle29;
	CGeoCube m_zgSolarzelle30;
	CGeoCube m_zgSolarzelle31;
	CGeoCube m_zgSolarzelle32;
	CGeoCube m_zgSolarzelle33;
	CGeoCube m_zgSolarzelle34;
	CGeoCube m_zgSolarzelle35;
	CGeoCube m_zgSolarzelle36;
	CGeoCube m_zgSolarzelle37;
	CGeoCube m_zgSolarzelle38;
	CGeoCube m_zgSolarzelle39;
	CGeoCube m_zgSolarzelle40;
	CGeoCube m_zgSolarzelle41;
	CGeoCube m_zgSolarzelle42;



	//Placements LOD 2

	CPlacement m_zpSolarPowerplant2;
	CPlacement m_zpGrundflaeche2;
	CGeoCube m_zgGrundflaeche2;


public:
	VModelSolarPowerPlant();
	virtual ~VModelSolarPowerPlant() override;

	virtual float getHeight() override
	{
		return 0.35f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}
	inline void rotate(const float angle)
	{
		m_zpGrundflaeche.RotateYDelta(angle);
		m_zpGrundflaeche2.RotateYDelta(angle);
	}

};


NAMESPACE_VIEW_E
