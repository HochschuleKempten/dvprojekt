#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LUtility.h"
#include "LCity.h"
#include <boost/graph/breadth_first_search.hpp>
#include "LCoalPowerPlant.h"
#include <boost/graph/strong_components.hpp>

NAMESPACE_LOGIC_B


using namespace boost;

template<typename Graph>
static std::vector<int> strongConnectedSearch(const Graph& g, const int startIdx)
{
	std::vector<int> component(num_vertices(g)), discover_time(num_vertices(g));
	strong_components(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

	int mainComponent = component[startIdx];
	std::vector<int> vertices;

	for (size_t i = 0; i < component.size(); i++) {
		if (component[i] == mainComponent && i != startIdx) {
			vertices.push_back(i);
		}
	}

	return vertices;
}

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this] (LField& f) {
		f.setLPlayingField(this);
	}),
	powerLineGraph(fieldLength*fieldLength),
	fieldTypes({ LField::MOUNTAIN, LField::AIR, LField::SOLAR, LField::WATER, LField::COAL }),
	fieldLevels({ LField::LEVEL1, LField::LEVEL2, LField::LEVEL3 })
{
	vPlayingField = lMaster->getVMaster()->getFactory()->createPlayingField(this);
	vPlayingField->initPlayingField(vPlayingField);	//Sets the shared_ptr (need to be done before the fields can be created)
	createFields();									//Create the fields (also places some buildings)
	vPlayingField->buildPlayingField();				//Now build the playing field
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
	//remove all outgoing edges
	powerLineGraph.m_vertices[convertIndex(x, y)].m_out_edges.clear();

	if (getField(x, y)->removeBuilding()) 
	{
		vPlayingField->objectRemoved(x, y);
	}
	else 
	{
		//TODO (All) how to handle error checks?
	}

	//todo (L) when?
	calculateEnergyValueCity();
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	//todo (IP) getPlayers(): get current player
	if (lMaster->getPlayer(1)->getMoney() > 50000)
	{
		getField(x, y)->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

void LPlayingField::createFields()
{
	int cityPositionX = 5;// fieldLength * 0.5 + rand() % 3;
	int cityPositionY = 5;// fieldLength * 0.25 + rand() % 3;
	usedCoordinates.emplace_back(cityPositionX, cityPositionY);

	int firstPowerLinePositionX = cityPositionX;
	int firstPowerLinePositionY = cityPositionY +1;
	usedCoordinates.emplace_back(firstPowerLinePositionX, firstPowerLinePositionY);

	int secondPowerLinePositionX = firstPowerLinePositionX +1;
	int secondPowerLinePositionY = firstPowerLinePositionY;
	usedCoordinates.emplace_back(secondPowerLinePositionX, secondPowerLinePositionY);
		
	int firstPowerPlantPositionX = secondPowerLinePositionX;
	int firstPowerPlantPositionY = secondPowerLinePositionY + 1;
	usedCoordinates.emplace_back(firstPowerPlantPositionX, firstPowerPlantPositionY);

	fieldArray[cityPositionX][cityPositionY].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);
	placeBuilding<LCity>(cityPositionX, cityPositionY);

	//save city position 
	cityPosition = std::make_pair(cityPositionX, cityPositionY);

	fieldArray[firstPowerLinePositionX][firstPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(firstPowerLinePositionX, firstPowerLinePositionY, LPowerLine::NORTH | LPowerLine::EAST | LPowerLine::SOUTH | LPowerLine::WEST);

	fieldArray[secondPowerLinePositionX][secondPowerLinePositionY].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(secondPowerLinePositionX, secondPowerLinePositionY, LPowerLine::NORTH | LPowerLine::EAST | LPowerLine::SOUTH | LPowerLine::WEST);

	fieldArray[firstPowerPlantPositionX][firstPowerPlantPositionY].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);
	placeBuilding<LCoalPowerPlant>(firstPowerPlantPositionX, firstPowerPlantPositionY);

	int windmillPowerPlantPositionX = 2;
	int windmillPowerPlantPositionY = 0;
	usedCoordinates.emplace_back(windmillPowerPlantPositionX, windmillPowerPlantPositionY);
	fieldArray[windmillPowerPlantPositionX][windmillPowerPlantPositionY].init(LField::AIR, LField::LEVEL1);

	//TODO (JS) grass around buildings

	//Set grass around the city
	placeGrassAroundPosition(cityPosition, 1);

	//Fill with the requested number of power plants
	const int numberOfPowerPlants = 10;
	for (int i = 0; i < numberOfPowerPlants; i++) {
		std::pair<int, int> newCoordinates = retrieveFreeCoordinates();
		int type = rand() % fieldTypes.size();
		int level = rand() % fieldLevels.size();
		fieldArray[newCoordinates.first][newCoordinates.second].init(fieldTypes[type], fieldLevels[level]);
	}

	//Fill the rest with grass
	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {
			if (std::find(usedCoordinates.begin(), usedCoordinates.end(), std::pair<int, int>(x, y)) != usedCoordinates.end()) {
				//Coordinate already assigned
				continue;
			}
			else {
				int level = rand() % fieldLevels.size();
				std::pair<int, int> coordinates = retrieveFreeCoordinates(x, y);
				fieldArray[coordinates.first][coordinates.second].init(LField::GRASS, fieldLevels[level]);
			}
		}
	}
}

LMaster* LPlayingField::getLMaster()
{
	return lMaster;
}

IVPlayingField* LPlayingField::getVPlayingField()
{
	return vPlayingField.get();
}

bool LPlayingField::checkIndex(const int x, const int y)
{
	return (x >= 0) && (x < fieldLength) && (y >= 0) && (y < fieldLength);
}

int LPlayingField::convertIndex(const int x, const int y)
{
	return (x*fieldLength + y);
}

void LPlayingField::calculateEnergyValueCity()
{
	int energyValue = 0;

	std::vector<int> vec = strongConnectedSearch(powerLineGraph, convertIndex(cityPosition.first, cityPosition.second));
	std::pair<int, int> coord;

	for (size_t i = 0; i < vec.size(); i++)
	{
		coord = convertIndex(vec[i]);
		ILPowerPlant* pP = dynamic_cast<ILPowerPlant*>(getField(coord.first, coord.second)->getBuilding());

		if (pP != nullptr)
		{
			energyValue += pP->getEnergyValue();
		}
	}

	CASTD<LCity*>(getField(cityPosition.first, cityPosition.second)->getBuilding())->setEnergy(energyValue);
}

void LPlayingField::addBuildingToGraph(const int x, const int y, const int orientation)
{
	if (orientation & LPowerLine::PowerLineOrientation::NORTH)
	{
		if (checkIndex(x - 1, y))
		{
			add_edge(convertIndex(x, y), convertIndex(x - 1, y), powerLineGraph);
		}
	}

	if (orientation & LPowerLine::PowerLineOrientation::EAST)
	{
		if (checkIndex(x, y + 1))
		{
			add_edge(convertIndex(x, y), convertIndex(x, y + 1), powerLineGraph);
		}
	}

	if (orientation & LPowerLine::PowerLineOrientation::SOUTH)
	{
		if (checkIndex(x + 1, y))
		{
			add_edge(convertIndex(x, y), convertIndex(x + 1, y), powerLineGraph);
		}
	}

	if (orientation & LPowerLine::PowerLineOrientation::WEST)
	{
		if (checkIndex(x, y - 1))
		{
			add_edge(convertIndex(x, y), convertIndex(x, y - 1), powerLineGraph);
		}
	}
}

std::pair<int, int> LPlayingField::convertIndex(const int idx)
{
	return std::make_pair(idx / fieldLength, idx % fieldLength);
}

void LPlayingField::placeGrassAroundPosition(const std::pair<int, int>& coordinates, const int space)
{
	for (int x = -space; x <= space; x++) {
		for (int y = -space; y <= space; y++) {
			if (x == 0 || y == 0) {
				continue;
			}

			int level = rand() % fieldLevels.size();
			fieldArray[coordinates.first + x][coordinates.second + y].init(LField::GRASS, fieldLevels[level]);
		}
	}
}

std::pair<int, int> LPlayingField::retrieveFreeCoordinates()
{
	std::srand(CASTS<unsigned int>(std::time(0)));
	int count = 0;
	while (count++ < 20) {
		int x = rand() % fieldLength;
		int y = rand() % fieldLength;

		if (std::find(usedCoordinates.begin(), usedCoordinates.end(), std::pair<int, int>(x, y)) == usedCoordinates.end()) {
			//Coordinate is unused
			usedCoordinates.emplace_back(x, y);
			return usedCoordinates.back();
		}
	}

	ASSERT(true, "No coordinates could be delivered. This should not happen.");
	return {};
}

std::pair<int, int> LPlayingField::retrieveFreeCoordinates(const int x, const int y)
{
	ASSERT(std::find(usedCoordinates.begin(), usedCoordinates.end(), std::pair<int, int>(x, y)) == usedCoordinates.end(), "The coordinates requested are already used.");
	usedCoordinates.emplace_back(x, y);
	return usedCoordinates.back();
}


NAMESPACE_LOGIC_E
