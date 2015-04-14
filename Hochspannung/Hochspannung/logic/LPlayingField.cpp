#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LUtility.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this] (LField& f) {
		f.setLPlayingField(this);
	}),
	powerLineGraph(fieldLength*fieldLength)
{
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
	int cityPositionX = 5;// fieldLength * 0.5 + rand() % 3;
	int cityPositionY = 5;// fieldLength * 0.25 + rand() % 3;


	int firstPowerLinePositionX = cityPositionX;
	int firstPowerLinePositionY = cityPositionY +1;

	int secondPowerLinePositionX = firstPowerLinePositionX +1;
	int secondPowerLinePositionY = firstPowerLinePositionY;
		
	int firstPowerPlantPositionX = secondPowerLinePositionX;
	int firstPowerPlantPositionY = secondPowerLinePositionY + 1;

	fieldArray[cityPositionX][cityPositionY].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);
	fieldArray[cityPositionX][cityPositionY].setBuilding<LPowerLine>(cityPositionX, cityPositionY, LPowerLine::EAST); //Until we have a citymodel, we use a powerline


	fieldArray[firstPowerLinePositionX][firstPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[firstPowerLinePositionX][firstPowerLinePositionY].setBuilding<LPowerLine>(firstPowerLinePositionX, firstPowerLinePositionY, LPowerLine::EAST); //Until we have a citymodel, we use a powerline

	fieldArray[secondPowerLinePositionX][secondPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[secondPowerLinePositionX][secondPowerLinePositionY].setBuilding<LPowerLine>(secondPowerLinePositionX, secondPowerLinePositionY, LPowerLine::EAST); //Until we have a citymodel, we use a powerline

	fieldArray[firstPowerPlantPositionX][firstPowerPlantPositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[firstPowerPlantPositionX][firstPowerPlantPositionY].setBuilding<LPowerLine>(firstPowerPlantPositionX, firstPowerPlantPositionY, LPowerLine::EAST);


	std::vector<LField::FieldType> fieldTypes = { LField::FieldType::GRASS, LField::FieldType::GRASS, LField::FieldType::GRASS, LField::FieldType::COAL, LField::FieldType::GRASS, LField::FieldType::MOUNTAIN, LField::FieldType::OIL, LField::FieldType::WATER, LField::FieldType::GRASS };
	std::vector<LField::FieldLevel> fieldLevels = { LField::FieldLevel::LEVEL1, LField::FieldLevel::LEVEL2, LField::FieldLevel::LEVEL3 };

	std::srand(std::time(0));

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			if (x == cityPositionX && y == cityPositionX)
			{
				continue;
			}

			if (x == firstPowerLinePositionX && y == firstPowerLinePositionY)
			{
				continue;
			}

			if (x == secondPowerLinePositionX && y == secondPowerLinePositionY)
			{
				continue;
			}

			if (x == firstPowerPlantPositionX && y == firstPowerPlantPositionY)
			{
				continue;
			}

			int type = rand() % fieldTypes.size();
			int level = rand() % fieldLevels.size();
			fieldArray[x][y].init(fieldTypes[type], fieldLevels[level]);
		}
	}
}


LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}

void LPlayingField::generatePowerLineGraph()
{
	pLine** plArray = new pLine*[fieldLength];

	for (int i = 0; i < fieldLength; i++)
	{
		plArray[i] = new pLine[fieldLength];
	}

	ILBuilding* building = nullptr;

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			plArray[x][y].x = x;
			plArray[x][y].y = y;

			building = getField(x, y)->getBuilding();

			//check if building is a powerline
			if (building != nullptr && building->getID() == LPowerLine::id)
			{
				plArray[x][y].placed = true;

				int orientation = static_cast<LPowerLine*>(building)->getPowerLineOrientation();
				
				if (orientation & LPowerLine::PowerLineOrientation::NORTH)
				{
					if (checkIndex(x - 1, y))
					{
						plArray[x][y].connections.push_back(&plArray[x - 1][y]);
					}
				}

				if (orientation & LPowerLine::PowerLineOrientation::EAST)
				{
					if (checkIndex(x, y + 1))
					{
						plArray[x][y].connections.push_back(&plArray[x][y + 1]);
					}
				}

				if (orientation & LPowerLine::PowerLineOrientation::SOUTH)
				{
					if (checkIndex(x + 1, y))
					{
						plArray[x][y].connections.push_back(&plArray[x + 1][y]);
					}
				}

				if (orientation & LPowerLine::PowerLineOrientation::WEST)
				{
					if (checkIndex(x, y - 1))
					{
						plArray[x][y].connections.push_back(&plArray[x][y - 1]);
					}
				}
			}
		}
	}

	//todo (L) put following part in own method (graph shouldn't be recreated every check!)

	//remove all existing edges and vertices
	powerLineGraph.clear();

	//iterate through struct array, check if field contains a powerline (plArray[][].placed == true) and
	//check on connections to other powerlines

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			//check if field contains a powerline
			if (plArray[x][y].placed)
			{
				//check outgoing connections
				for (int i = 0; i < plArray[x][y].connections.size(); i++)
				{	
					for (int j = 0; j < plArray[x][y].connections[i]->connections.size(); j++)
					{
						//check if outgoing connections of neighbours are incoming connections to this field
						// o -> x
						// x -> o

						if (plArray[x][y].connections[i]->connections[j] == &plArray[x][y])
						{
							//position of neighbour which is connected to this field
							int otherX = plArray[x][y].connections[i]->connections[j]->x;
							int otherY = plArray[x][y].connections[i]->connections[j]->y;

							add_edge(convertIndex(x, y), convertIndex(otherX, otherY), powerLineGraph);
						}
					}
				}
			}
		}
	}



	for (int i = 0; i < fieldLength; i++)
	{
		delete [] plArray[i];
	}

	delete [] plArray;
}

//todo (L) implement method for checking graph

bool LPlayingField::checkIndex(const int x, const int y)
{
	return (x >= 0) && (x < fieldLength) && (y >= 0) && (y < fieldLength);
}

int LPlayingField::convertIndex(const int x, const int y)
{
	return (x*fieldLength + y);
}

