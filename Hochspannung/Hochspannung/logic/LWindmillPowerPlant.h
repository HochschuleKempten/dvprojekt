#pragma once
#include "ILPowerPlant.h"

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 6;

	LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LWindmillPowerPlant();
};

