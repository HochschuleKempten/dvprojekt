#pragma once
#include "ILPowerPlant.h"

class LHydroelectricPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 1;

	LHydroelectricPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LHydroelectricPowerPlant();

	int getID();
};

