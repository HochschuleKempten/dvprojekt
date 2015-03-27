#pragma once
#include "ILPowerPlant.h"
class LSolarPowerPlant :
	public ILPowerPlant
{
public:
	LSolarPowerPlant(int costs, int energyValue);
	~LSolarPowerPlant();
};

