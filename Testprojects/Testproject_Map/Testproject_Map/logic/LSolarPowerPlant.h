#pragma once
#include "ILPowerPlant.h"

class LSolarPowerPlant :
	public ILPowerPlant
{
public:
	LSolarPowerPlant(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y);
	~LSolarPowerPlant();
};

