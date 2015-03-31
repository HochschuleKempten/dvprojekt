#include "LCoalPowerPlant.h"

LCoalPowerPlant::LCoalPowerPlant(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, playingField,x, y)
{
}

LCoalPowerPlant::~LCoalPowerPlant()
{
}
