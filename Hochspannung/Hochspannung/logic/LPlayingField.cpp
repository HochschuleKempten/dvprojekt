#include "LPlayingField.h"
#include "LPlayer.h"
#include "ILBuilding.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include <vector>
#include "LUtility.h"
#include "LPowerLine.h"

LPlayingField::LPlayingField(LMaster* lMaster)
: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this](LField& obj)
{   //Lambda-Expression
	obj.setLPlayingField(this);
	//TODO (MB) create fields randomly with city
	
	
	
		//TODO (MB) create LCity --> placeBuilding
		obj.init(LField::WATER, LField::LEVEL1);
	})




{
	this->createFields();
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);

	createFields();
}

LPlayingField::~LPlayingField()
{
	delete vPlayingField;
}

void LPlayingField::initVPlayingField()
{
	vPlayingField->initPlayingField();
}

LField* LPlayingField::getField(const int x, const int y)
{
	return &fieldArray[x][y];
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
}

void LPlayingField::removeBuilding(const int x, const int y)
{
	if (getField(x, y)->removeBuilding()) {
		vPlayingField->objectRemoved(x, y);
	}
	else {
		//TODO (All) how to handle error checks?
	}
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	if (lMaster->getPlayer()->getMoney() > 50000)
	{
		getField(x, y)->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

void LPlayingField::createFields()
{

	bool hasCity = false;;
	std::vector<LField::FieldType> fieldTypes   = { LField::FieldType::CITY, LField::FieldType::COAL, LField::FieldType::GRASS, LField::FieldType::MOUNTAIN, LField::FieldType::OIL, LField::FieldType::WATER};
	std::vector<LField::FieldLevel> fieldLevels = { LField::FieldLevel::LEVEL1, LField::FieldLevel::LEVEL2, LField::FieldLevel::LEVEL3};
	

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			fieldArray[x][y].setLPlayingField(this);
			int type = rand() % fieldTypes.size();
			int level = rand() % fieldLevels.size();
			

			if (hasCity & type == 0)
			{
				continue;
			}

			else
			{
				fieldArray[x][y].init(fieldTypes[type], fieldLevels[level]);
			}			
			
			if (type == 0)
			{
				hasCity == true;
				//fieldArray[x][y].setBuilding<LPowerLine>(x, y);
			}

			
			
		}
	}
}

LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}