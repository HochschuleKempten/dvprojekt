#include "LField.h"
#include "ILBuilding.h"

NAMESPACE_LOGIC_B


LField::LField()
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

void LField::init(const FieldType fieldType, const FieldLevel fieldLevel)
{
	this->fieldType = fieldType;
	this->fieldLevel = fieldLevel;

	energyStock = fieldType * fieldLevel;
	energyLeft = energyStock;
}

LField::FieldType LField::getFieldType() const
{
	return fieldType;
}

LField::FieldLevel LField::getFieldLevel() const
{
	return fieldLevel;
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
	buildingPlaced = allowed;
}

bool LField::isPlacingAllowed()
{
	return buildingPlaced;
}

LPlayingField* LField::getLPlayingField()
{
	return lPlayingField;
}

NAMESPACE_LOGIC_E