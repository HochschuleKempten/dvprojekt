#pragma once
#include "ILPowerPlant.h"
class LHydroelectricPowerPlant :
	public ILPowerPlant
{
public:
	LHydroelectricPowerPlant(int costs, int energyValue);
	~LHydroelectricPowerPlant();
};

