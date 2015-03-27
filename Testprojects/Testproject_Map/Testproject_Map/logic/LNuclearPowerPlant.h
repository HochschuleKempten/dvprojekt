#pragma once
#include "ILPowerPlant.h"
class LNuclearPowerPlant :
	public ILPowerPlant
{
public:
	LNuclearPowerPlant(int costs, int energyValue);
	~LNuclearPowerPlant();
};

