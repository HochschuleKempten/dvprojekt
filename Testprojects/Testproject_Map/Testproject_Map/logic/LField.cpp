#include "LField.h"


LField::LField()
{
}


LField::~LField()
{
}

void LField::setBuilding(ILBuilding* building)
{
	this->building = building;
}
ILBuilding* LField::getBuilding()
{
	return building;
}

void LField::setIsPlacingAllowed(bool allowed)
{
	isPlacingAllowed = allowed;
}

bool LField::getIsPlacingAllowed()
{
	return isPlacingAllowed;
}
