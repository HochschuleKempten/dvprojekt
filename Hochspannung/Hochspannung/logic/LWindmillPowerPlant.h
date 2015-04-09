#pragma once
#include "ILPowerPlant.h"

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	const static int id = 6;

	LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LWindmillPowerPlant();
};

