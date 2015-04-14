#pragma once
#include "ILPowerPlant.h"

class LSolarPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 5;

	LSolarPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LSolarPowerPlant();

	int getID();
};

