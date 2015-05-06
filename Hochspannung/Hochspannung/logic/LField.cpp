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

void LField::setFieldType(FieldType fieldType)
{
	this->fieldType = fieldType;

	energyStock = fieldType * fieldLevel;
	energyLeft = energyStock;
}

LField::FieldLevel LField::getFieldLevel() const
{
	return fieldLevel;
}

void LField::setFieldLevel(FieldLevel fieldLevel)
{
	this->fieldLevel = fieldLevel;

	energyStock = fieldType * fieldLevel;
	energyLeft = energyStock;
}


bool LField::removeBuilding()
{
	if (lBuilding != nullptr)
	{
		//Player gets money back
		lPlayingField->getLMaster()->getPlayer(LPlayer::Local)->addMoney(CASTS<int>(LBalanceLoader::getMoneyBackAmount() * lBuilding->getValue()));

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