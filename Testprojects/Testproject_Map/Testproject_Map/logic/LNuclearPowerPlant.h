#pragma once
#include "ILPowerPlant.h"
class LNuclearPowerPlant :
	public ILPowerPlant
{
public:
	LNuclearPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y);
	~LNuclearPowerPlant();
};

