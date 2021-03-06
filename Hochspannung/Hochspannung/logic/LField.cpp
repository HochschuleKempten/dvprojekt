#include "LField.h"
#include "ILBuilding.h"
#include "LBalanceLoader.h"
#include "LPlayingField.h"

NAMESPACE_LOGIC_B


LField::LField()
{
}

LField::~LField()
{
	removeBuilding();
}

void LField::init(const FieldType fieldType, const FieldLevel fieldLevel)
{
	this->fieldType = fieldType;
	this->fieldLevel = fieldLevel;

	const std::unordered_map<LField::FieldLevel, double> fieldLevels = LBalanceLoader::getFieldLevelFactor();
	resourceStock = CASTS<int>(LBalanceLoader::getFieldStorage(LField::fieldType) * fieldLevels.at(fieldLevel));

	resourceLeft = resourceStock;
}

void LField::setInitialValues(LPlayingField* lPlayingField, const int x, const int y)
{
	this->lPlayingField = lPlayingField;
	this->x = x;
	this->y = y;
}

LField::FieldType LField::getFieldType() const
{
	return fieldType;
}

LField::FieldLevel LField::getFieldLevel() const
{
	return fieldLevel;
}

int LField::getBuildingId() const
{
	return lBuilding == nullptr ? -1 : lBuilding->getIdentifier();
}

bool LField::removeBuilding(const std::function<void(const ILBuilding* const)>& fnBeforeDelete)
{
	if (lBuilding != nullptr)
	{
		//Last possibility to work with the object before delete
		if (fnBeforeDelete != nullptr)
		{
			fnBeforeDelete(lBuilding);
		}

		delete lBuilding;
		lBuilding = nullptr;
		buildingPlaced = false;

		return true;
	}

	return false;
}

ILBuilding* LField::getBuilding()
{
	return lBuilding;
}

void LField::setIsPlacingAllowed(const bool allowed)
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

int LField::getResources() const
{
	return resourceLeft;
}

int LField::deductResources()
{
	resourceLeft *= LBalanceLoader::getFactorSabotageResource();
	return resourceLeft;
}

int LField::reduceResources(const int amount)
{
	if (resourceLeft - amount <= 0)
	{
		//Can't reduce all, reduce what is possible
		int amountReduced = resourceLeft - amount;
		resourceLeft = 0;
		return amountReduced;
	}
	
	//Enough resources left on the field to reduce the desired amount
	resourceLeft -= amount;
	return amount;
}

NAMESPACE_LOGIC_E
