#pragma once

#include "IView.h"

class ILPowerPlant;

class IVPowerPlant : public IView
{
protected:
	ILPowerPlant* plant;

public:
	IVPowerPlant(ILPowerPlant* plant)
		: plant(plant)
	{}
	virtual ~IVPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y) = 0;
};
