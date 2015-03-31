#include "LOilRefinery.h"

LOilRefinery::LOilRefinery(const int costs, const int energyValue, LPlayingField* playingField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, playingField, x, y)
{
}


LOilRefinery::~LOilRefinery()
{
}
