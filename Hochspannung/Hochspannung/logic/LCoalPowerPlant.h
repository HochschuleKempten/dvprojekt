#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant : public ILPowerPlant
{
public:
	LCoalPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y);
	virtual ~LCoalPowerPlant();
};
