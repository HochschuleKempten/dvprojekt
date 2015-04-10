#pragma once
#include "ILPowerPlant.h"
class LOilRefinery :
	public ILPowerPlant
{
public:
	static const int id = 3;

	LOilRefinery(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LOilRefinery();
};

