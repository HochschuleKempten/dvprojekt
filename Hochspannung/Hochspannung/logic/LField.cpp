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

bool LField::removeBuilding()
{
	if (lBuilding != nullptr)
	{
		//Player gets money back
		lPlayingField->getLMaster()->getPlayer(LPlayer::Local)->addMoney(CASTS<int>(LBalanceLoader::getSellRevenue() * lBuilding->getValue()));

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

bool LField::reduceRecources(int amount) 
{
	if (resourceLeft > 0) 
	{
		resourceLeft -= amount;

		if (resourceLeft > 0)
		{
			return true;
		}
		else
		{
			resourceLeft = 0;
		}
	}
	
	return false;
}

NAMESPACE_LOGIC_E