#include "LField.h"


LField::LField()
{
	placingAllowed = true;
	building = nullptr;
}


LField::~LField()
{
	removeBuilding();
}

bool LField::setBuilding(ILBuilding* building)
{
	if (placingAllowed)
	{
		this->building = building;
		return true;
	}

	return false;
}

bool LField::removeBuilding()
{
	if (building != nullptr)
	{
		delete building;
		building = nullptr;

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
