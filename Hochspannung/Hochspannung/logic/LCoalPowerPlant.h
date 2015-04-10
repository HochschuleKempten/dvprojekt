#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant : public ILPowerPlant
{
public:
	const static int id = 0;

	LCoalPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	virtual ~LCoalPowerPlant();
};
