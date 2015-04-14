#include "LCity.h"


LCity::LCity()
{
}


LCity::~LCity()
{
}

void LCity::addEnergy(const int energy)
{
	this->energy += energy;
}

void LCity::removeEnergy(const int energy)
{
	//todo (IP) what if energy value is < 0?
	this->energy -= energy;
}

int LCity::getEnergy()
{
	return energy;
}
