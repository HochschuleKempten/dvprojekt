#include "LField.h"


LField::LField() :
	placingAllowed(true),
	lBuilding(nullptr)
{
}


LField::~LField()
{
	removeBuilding();
}

void LField::setLPlayingField(LPlayingField* lPlayingField)
{
	this->lPlayingField = lPlayingField;
}

bool LField::removeBuilding()
{
	if (lBuilding != nullptr)
	{
		delete lBuilding;
		lBuilding = nullptr;

		return true;
	}

	return false;
}
ILBuilding* LField::getBuilding()
{
	return lBuilding;
}

void LField::setIsPlacingAllowed(bool allowed)
{
	placingAllowed = allowed;
}

bool LField::isPlacingAllowed()
{
	return placingAllowed;
}

LPlayingField* LField::getLPlayingField()
{
	return lPlayingField;
}
