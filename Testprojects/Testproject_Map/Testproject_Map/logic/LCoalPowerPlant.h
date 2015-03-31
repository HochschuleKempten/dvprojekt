#pragma once
#include "ILPowerPlant.h"

class LCoalPowerPlant:
	public ILPowerPlant
{
public:
	LCoalPowerPlant(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y);
	~LCoalPowerPlant();
};

