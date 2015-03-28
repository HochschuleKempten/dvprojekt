#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant:
	public ILPowerPlant
{
public:
	LCoalPowerPlant(int costs, int energyValue);
	~LCoalPowerPlant();
};

