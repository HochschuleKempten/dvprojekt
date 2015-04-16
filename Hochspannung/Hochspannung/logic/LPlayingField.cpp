#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "LMaster.h"
#include "IVPlayingField.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LUtility.h"
#include "LCity.h"
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include "LCoalPowerPlant.h"
#ifdef _DEBUG
#include <iostream>
#endif

NAMESPACE_LOGIC_B

using namespace boost;

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this] (LField& f) {
		f.setLPlayingField(this);
	}),
	powerLineGraph(fieldLength*fieldLength)
{
	vPlayingField = lMaster->getVMaster()->getFactory()->createPlayingField(this);
	vPlayingField->initPlayingField(vPlayingField);	//Sets the shared_ptr (need to be done before the fields can be created)
	createFields();									//Create the fields (also places some buildings)
	vPlayingField->buildPlayingField();				//Now build the playing field

	//todo (L) where?
	calculateEnergyValueCity();
}

LPlayingField::~LPlayingField()
{
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
	fieldArray[cityPositionX][cityPositionY].setBuilding<LCity>(cityPositionX, cityPositionY);


	fieldArray[firstPowerLinePositionX][firstPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[firstPowerLinePositionX][firstPowerLinePositionY].setBuilding<LPowerLine>(firstPowerLinePositionX, firstPowerLinePositionY, LPowerLine::WEST | LPowerLine::SOUTH); //Until we have a citymodel, we use a powerline

	fieldArray[secondPowerLinePositionX][secondPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[secondPowerLinePositionX][secondPowerLinePositionY].setBuilding<LPowerLine>(secondPowerLinePositionX, secondPowerLinePositionY, LPowerLine::NORTH | LPowerLine::EAST); //Until we have a citymodel, we use a powerline

	fieldArray[firstPowerPlantPositionX][firstPowerPlantPositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	fieldArray[firstPowerPlantPositionX][firstPowerPlantPositionY].setBuilding<LCoalPowerPlant>(firstPowerPlantPositionX, firstPowerPlantPositionY);


	std::vector<LField::FieldType> fieldTypes = { LField::FieldType::GRASS, LField::FieldType::GRASS, LField::FieldType::GRASS, LField::FieldType::COAL, LField::FieldType::GRASS, LField::FieldType::MOUNTAIN, LField::FieldType::OIL, LField::FieldType::WATER, LField::FieldType::GRASS };
	std::vector<LField::FieldLevel> fieldLevels = { LField::FieldLevel::LEVEL1, LField::FieldLevel::LEVEL2, LField::FieldLevel::LEVEL3 };

	std::srand(CASTS<unsigned int>(std::time(0)));

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

struct pLine
{
	bool placed = false;
	std::vector<pLine*> connections;
	int x, y;
};

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
			if (building != nullptr && dynamic_cast<LPowerLine*>(building) != nullptr)
			{
				plArray[x][y].placed = true;

				int orientation = CASTD<LPowerLine*>(building)->getPowerLineOrientation();
				
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

	//remove all existing edges
	for (int i = 0; i < fieldLength*fieldLength; i++)
	{
		powerLineGraph.m_vertices[i].m_out_edges.clear();
	}

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
				for (size_t i = 0; i < plArray[x][y].connections.size(); i++)
				{	
					//position of neighbour which is connected to this field
					int otherX = plArray[x][y].connections[i]->x;
					int otherY = plArray[x][y].connections[i]->y;

					add_edge(convertIndex(x, y), convertIndex(otherX, otherY), powerLineGraph);
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

bool LPlayingField::checkIndex(const int x, const int y)
{
	return (x >= 0) && (x < fieldLength) && (y >= 0) && (y < fieldLength);
}

int LPlayingField::convertIndex(const int x, const int y)
{
	return (x*fieldLength + y);
}

//needed for vertexConnected()
class custom_bfs_visitor : public default_bfs_visitor
{
private:
	int vertex = 0;
	LPlayingField * lPlayingField;
public:

	custom_bfs_visitor(int vertex, LPlayingField* lPl) :
		vertex(vertex),
		lPlayingField(lPl)
	{
	}

	template < typename Vertex, typename Graph >
	void discover_vertex(Vertex u, const Graph & g) const
	{
		if (u == vertex)
		{
			//todo (L) ugly..
			lPlayingField->setVertexConnected(true);
		}
	}

};

void LPlayingField::setVertexConnected(const bool b)
{
	plVertexConnected = b;
}

bool LPlayingField::powerlinesConnected(const int start, const int destination)
{
	plVertexConnected = false;

	custom_bfs_visitor vis(destination, this);

	breadth_first_search(powerLineGraph, vertex(start, powerLineGraph), visitor(vis));

	return plVertexConnected;
}

void LPlayingField::calculateEnergyValueCity()
{
	generatePowerLineGraph();

	LCity* city = nullptr;
	std::pair<int, int> cityPosition;
	//first = index of vertex, second = energy value
	std::vector<std::pair<int, int>> powerPlants;

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			if (city == nullptr && dynamic_cast<LCity*>(getField(x, y)->getBuilding()) != nullptr)
			{
				city = dynamic_cast<LCity*>(getField(x, y)->getBuilding());
				cityPosition = std::pair<int, int>(x, y);
			}

			if (dynamic_cast<ILPowerPlant*>(getField(x, y)->getBuilding()) != nullptr)
			{
				ILPowerPlant* powerPlant = dynamic_cast<ILPowerPlant*>(getField(x, y)->getBuilding());
				powerPlants.push_back(std::pair<int, int>(convertIndex(x,y), powerPlant->getEnergyValue()));
			}
		}
	}

	//vertex indices of powerlines connected to the city
	std::vector<int> cityPowerLines = getConnectedPowerLines(cityPosition.first, cityPosition.second);

	//vertex indices of powerlines connected to the powerplant
	//std::vector<int> powerPlantPowerLines;

	int energyValue = 0;

	for (int i = 0; i < powerPlants.size(); i++)
	{

		for (int j = 0; j < cityPowerLines.size(); j++)
		{
			if (powerlinesConnected(cityPowerLines[j], powerPlants[i].first))
			{
				energyValue += powerPlants[i].second;

				break;
			}
		}
	}

	city->setEnergy(energyValue);
}

std::vector<int> LPlayingField::getConnectedPowerLines(const int x, const int y)
{
	LPowerLine* powerLine = nullptr;

	std::vector<int> plIndex;

	if (getField(x, y)->getBuilding() != nullptr)
	{
		//todo (L) redundant
		//north
		if (checkIndex(x - 1, y))
		{
			powerLine = dynamic_cast<LPowerLine*>(getField(x - 1, y)->getBuilding());

			if (powerLine != nullptr)
			{
				if (powerLine->getPowerLineOrientation() & LPowerLine::SOUTH)
				{
					plIndex.push_back(convertIndex(x - 1, y));
				}
			}
		}

		//east
		if (checkIndex(x, y + 1))
		{
			powerLine = dynamic_cast<LPowerLine*>(getField(x, y + 1)->getBuilding());

			if (powerLine != nullptr)
			{
				if (powerLine->getPowerLineOrientation() & LPowerLine::WEST)
				{
					plIndex.push_back(convertIndex(x, y + 1));
				}
			}
		}

		//south
		if (checkIndex(x + 1, y))
		{
			powerLine = dynamic_cast<LPowerLine*>(getField(x + 1, y)->getBuilding());

			if (powerLine != nullptr)
			{
				if (powerLine->getPowerLineOrientation() & LPowerLine::NORTH)
				{
					plIndex.push_back(convertIndex(x + 1, y));
				}
			}
		}


		//west
		if (checkIndex(x, y - 1))
		{
			powerLine = dynamic_cast<LPowerLine*>(getField(x, y - 1)->getBuilding());

			if (powerLine != nullptr)
			{
				if (powerLine->getPowerLineOrientation() & LPowerLine::EAST)
				{
					plIndex.push_back(convertIndex(x, y - 1));
				}
			}
		}


	}

	return plIndex;
}
NAMESPACE_LOGIC_E
