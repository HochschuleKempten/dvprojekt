#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant : public ILPowerPlant
{
public:
	static const int id = 0;

	LCoalPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LCoalPowerPlant();

	int getID();
};
