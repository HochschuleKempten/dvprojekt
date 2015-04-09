#include "LField.h"


LField::LField()
{
	placingAllowed = true;
	building = nullptr;
}


LField::~LField()
{
	if (building != nullptr) {
		delete building;
	}
}

//to "remove" a building, set it to null (delete it too?)
bool LField::setBuilding(ILBuilding* building)
{
	if (placingAllowed)
	{
		this->building = building;
		return true;
	}

	return false;
}
ILBuilding* LField::getBuilding()
{
	return building;
}

void LField::setIsPlacingAllowed(bool allowed)
{
	placingAllowed = allowed;
}

bool LField::isPlacingAllowed()
{
	return placingAllowed;
}
