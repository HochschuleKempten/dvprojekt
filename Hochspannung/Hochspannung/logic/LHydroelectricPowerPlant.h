#pragma once
#include "ILPowerPlant.h"

class LHydroelectricPowerPlant :
	public ILPowerPlant
{
public:
	LHydroelectricPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LHydroelectricPowerPlant();
};

