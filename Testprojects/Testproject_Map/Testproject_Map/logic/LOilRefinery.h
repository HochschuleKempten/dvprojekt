#pragma once
#include "ILPowerPlant.h"
class LOilRefinery :
	public ILPowerPlant
{
public:
	LOilRefinery(int costs, int energyValue);
	~LOilRefinery();
};

