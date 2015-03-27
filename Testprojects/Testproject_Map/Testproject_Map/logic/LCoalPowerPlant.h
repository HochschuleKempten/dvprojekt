#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant:
	public ILPowerPlant
{
private:
	int costs;
	int energyValue;

public:
	LCoalPowerPlant(int costs, int energyValue);
	~LCoalPowerPlant();
};

