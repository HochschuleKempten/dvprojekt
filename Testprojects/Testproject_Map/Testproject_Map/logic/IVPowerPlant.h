#pragma once

#include "IView.h"

class LPowerPlant;

class IVPowerPlant : public IView
{
protected:
	LPowerPlant* plant;

public:
	IVPowerPlant(LPowerPlant* plant)
		: plant(plant)
	{}
	virtual ~IVPowerPlant()
	{}

	virtual void initPowerPlant(const int i, const int j) = 0;
};
