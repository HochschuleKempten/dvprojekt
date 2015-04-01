#include "LOilRefinery.h"

LOilRefinery::LOilRefinery(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
	:ILPowerPlant(costs, energyValue, lPlayingField, x, y, nullptr)//TODO (V) fill with concrete View Object
{
}


LOilRefinery::~LOilRefinery()
{
}
