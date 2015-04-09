#pragma once
#include "ILPowerPlant.h"

class LSolarPowerPlant :
	public ILPowerPlant
{
public:
	LSolarPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LSolarPowerPlant();
};

