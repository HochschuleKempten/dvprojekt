#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "ILBuilding.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this] (LField& obj)
	{ //Lambda-Expression
		obj.setLPlayingField(this);
	})
{
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);
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

LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}

bool LPlayingField::powerPlantConnected(const int x, const int y)
{
	ILBuilding* building = nullptr;

	//todo (IP) redundant parts, fix this

	// check fields around the building:
	//		x
	//    x B x
	//      x

	// check north 
	if (x - 1 >= 0)
	{
		building = getField(x - 1, y)->getBuilding();

		if (building != nullptr && building->getID() == LPowerLine::id)
		{
			// north field contains a powerline

			if (dynamic_cast<LPowerLine*>(building)->getPowerLineOrientation() & LPowerLine::SOUTH)
			{
				// power line is connected to building (powerline orientation = SOUTH)

				//todo (IP) trace path
			}
		}
	}

	// check east
	if (y + 1 < fieldLength)
	{
		building = getField(x, y + 1)->getBuilding();

		if (building != nullptr && building->getID() == LPowerLine::id)
		{
			if (dynamic_cast<LPowerLine*>(building)->getPowerLineOrientation() & LPowerLine::WEST)
			{
			}
		}
	}

	// check south
	if (x + 1 < fieldLength)
	{
		building = getField(x + 1, y)->getBuilding();

		if (building != nullptr && building->getID() == LPowerLine::id)
		{
			if (dynamic_cast<LPowerLine*>(building)->getPowerLineOrientation() & LPowerLine::NORTH)
			{
			}
		}
	}

	// check west
	if (y - 1 >= 0)
	{
		building = getField(x, y - 1)->getBuilding();

		if (building != nullptr && building->getID() == LPowerLine::id)
		{
			if (dynamic_cast<LPowerLine*>(building)->getPowerLineOrientation() & LPowerLine::EAST)
			{
			}
		}
	}
}


bool LPlayingField::helper(const int x, const int y, ILPowerLine::PowerLineOrientation mask)
{
	LPowerLine::PowerLineOrientation otherDirections = static_cast<LPowerLine::PowerLineOrientation>(
		static_cast<LPowerLine*>(getField(x, y)->getBuilding())
		->getPowerLineOrientation() ^ mask
		);

	//todo (IP) check other directions
}