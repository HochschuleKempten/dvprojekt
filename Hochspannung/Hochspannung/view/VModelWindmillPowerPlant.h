#pragma once

#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


/**
 * @brief The VModelWindmillPowerPlant class holds the model for the windmill power plant.
 *
 * The image shows the internal hierarchy of the scenegraph and the structure of the model.
 *
 * @image html images/VModelWindmillPowerPlant.png "Scenegraph and structure of the model"
 */
class VModelWindmillPowerPlant : public IViewModel
{
private:
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



public:
	VModelWindmillPowerPlant();
	virtual ~VModelWindmillPowerPlant() override;

	virtual float getHeight() override
	{
		//return 11.0f;
		return 0.3f + 7.0f + 1.3f;
	}
	virtual float getWidth() override
	{
		return 0.0f;
	}

	inline void rotate(const float angle)
	{
		m_zpKopf.RotateZDelta(angle);
	}
};


NAMESPACE_VIEW_E
