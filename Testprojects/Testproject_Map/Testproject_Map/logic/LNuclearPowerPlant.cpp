#include "LNuclearPowerPlant.h"

LNuclearPowerPlant::LNuclearPowerPlant(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, playingField, x, y, nullptr)//TODO (V) fill with concrete View Object
{
}


LNuclearPowerPlant::~LNuclearPowerPlant()
{
}
