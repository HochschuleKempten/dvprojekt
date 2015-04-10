#pragma once
#include "ILPowerPlant.h"

class LNuclearPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 2;

	LNuclearPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LNuclearPowerPlant();
};

