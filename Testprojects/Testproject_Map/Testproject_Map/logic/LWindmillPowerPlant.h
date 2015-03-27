#pragma once
#include "ILPowerPlant.h"
class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	LWindmillPowerPlant(int costs, int energyValue);
	~LWindmillPowerPlant();
};

