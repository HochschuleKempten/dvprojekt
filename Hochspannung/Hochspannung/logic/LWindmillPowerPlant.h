#pragma once
#include "ILPowerPlant.h"

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LWindmillPowerPlant();
};

