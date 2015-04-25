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

template <typename Graph>
static std::vector<int> strongConnectedSearch(const Graph& g, const int startIdx)
{
	std::vector<int> component(num_vertices(g)), discover_time(num_vertices(g));
	strong_components(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

	int mainComponent = component[startIdx];
	std::vector<int> vertices;

	for (size_t i = 0; i < component.size(); i++) {
		if (component[i] == mainComponent && i != CASTS<size_t>(startIdx)) {
			vertices.push_back(CASTS<int>(i));
		}
	}

	return vertices;
}

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength, [this] (LField& f) {
		                               f.setLPlayingField(this);
	                               }),
	  powerLineGraph(fieldLength * fieldLength),
	  isCoordinateUsed(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  fieldTypes({LField::MOUNTAIN, LField::AIR, LField::SOLAR, LField::WATER, LField::COAL, LField::OIL}),
	  fieldLevels({LField::LEVEL1, LField::LEVEL2, LField::LEVEL3})
{
	//At the beginning every field is unused
	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {
			isCoordinateUsed.emplace(std::make_pair(x, y), false);
		}
	}

	vPlayingField = lMaster->getVMaster()->getFactory()->createPlayingField(this);
	vPlayingField->initPlayingField(vPlayingField); //Sets the shared_ptr (need to be done before the fields can be created)
	createFields(); //Create the fields (also places some buildings)
	vPlayingField->buildPlayingField(); //Now build the playing field
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

	if (getField(x, y)->removeBuilding()) {
		vPlayingField->objectRemoved(x, y);
	}
	else {
		//TODO (All) how to handle error checks?
	}

	//todo (L) when?
	calculateEnergyValueCity();
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	//todo (IP) getPlayers(): get current player
	if (lMaster->getPlayer(1)->getMoney() > 50000) {
		getField(x, y)->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

void LPlayingField::createFields()
{
	//Generate the firs positions
	cityPosition = retrieveFreeCoordinates(5, 5);
	std::pair<int, int> firstPowerLineCoordinates = retrieveFreeCoordinates(cityPosition.first, cityPosition.second + 1);
	std::pair<int, int> secondPowerLineCoordinates = retrieveFreeCoordinates(firstPowerLineCoordinates.first + 1, firstPowerLineCoordinates.second);
	std::pair<int, int> firstPowerPlantCoordinates = retrieveFreeCoordinates(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second + 1);

	fieldArray[cityPosition.first][cityPosition.second].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);
	placeBuilding<LCity>(cityPosition.first, cityPosition.second);
	placeGrassAroundPosition(cityPosition, 1);

	fieldArray[firstPowerLineCoordinates.first][firstPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(firstPowerLineCoordinates.first, firstPowerLineCoordinates.second, ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);

	fieldArray[secondPowerLineCoordinates.first][secondPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second, ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);

	fieldArray[firstPowerPlantCoordinates.first][firstPowerPlantCoordinates.second].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);
	placeBuilding<LCoalPowerPlant>(firstPowerPlantCoordinates.first, firstPowerPlantCoordinates.second);
	placeGrassAroundPosition<true>(firstPowerPlantCoordinates, 1);

	//Fill with the requested number of power plants
	const int numberOfPowerPlants = 8;
	for (int i = 0; i < numberOfPowerPlants; i++) {
		std::pair<int, int> newCoordinates = retrieveFreeCoordinates();
		int type = rand() % fieldTypes.size();
		int level = rand() % fieldLevels.size();
		fieldArray[newCoordinates.first][newCoordinates.second].init(fieldTypes[type], fieldLevels[level]);

		placeGrassAroundPosition<true>(newCoordinates, 1);
	}

	//Fill the rest with grass
	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {
			if (isCoordinateUsed[std::make_pair(x, y)]) {
				//Coordinate already assigned
				continue;
			}
			
			int level = rand() % fieldLevels.size();
			std::pair<int, int> coordinates = retrieveFreeCoordinates(x, y);
			fieldArray[coordinates.first][coordinates.second].init(LField::GRASS, fieldLevels[level]);
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
	return x * fieldLength + y;
}

void LPlayingField::calculateEnergyValueCity()
{
	int energyValue = 0;

	std::vector<int> vec = strongConnectedSearch(powerLineGraph, convertIndex(cityPosition.first, cityPosition.second));
	std::pair<int, int> coord;

	for (size_t i = 0; i < vec.size(); i++) {
		coord = convertIndex(vec[i]);
		ILPowerPlant* pP = dynamic_cast<ILPowerPlant*>(getField(coord.first, coord.second)->getBuilding());

		if (pP != nullptr) {
			energyValue += pP->getEnergyValue();
		}
	}

	CASTD<LCity*>(getField(cityPosition.first, cityPosition.second)->getBuilding())->setEnergy(energyValue);
}

void LPlayingField::addBuildingToGraph(const int x, const int y, const int orientation)
{
	if (orientation & ILBuilding::NORTH) {
		if (checkIndex(x - 1, y)) {
			add_edge(convertIndex(x, y), convertIndex(x - 1, y), powerLineGraph);
		}
	}

	if (orientation & ILBuilding::EAST) {
		if (checkIndex(x, y + 1)) {
			add_edge(convertIndex(x, y), convertIndex(x, y + 1), powerLineGraph);
		}
	}

	if (orientation & ILBuilding::SOUTH) {
		if (checkIndex(x + 1, y)) {
			add_edge(convertIndex(x, y), convertIndex(x + 1, y), powerLineGraph);
		}
	}

	if (orientation & ILBuilding::WEST) {
		if (checkIndex(x, y - 1)) {
			add_edge(convertIndex(x, y), convertIndex(x, y - 1), powerLineGraph);
		}
	}
}

std::pair<int, int> LPlayingField::convertIndex(const int idx)
{
	return std::make_pair(idx / fieldLength, idx % fieldLength);
}

template<bool cross = false>
void LPlayingField::placeGrassAroundPosition(const std::pair<int, int>& coordinates, const int space)
{
	for (int rowIdx = -space; rowIdx <= space; rowIdx++) {
		for (int colIdx = -space; colIdx <= space; colIdx++) {
			int x = coordinates.first + rowIdx;
			int y = coordinates.second + colIdx;

			//Don't place something on the base field
			if (rowIdx == 0 && colIdx == 0) {
				continue;
			}
			//Bounds checking
			if (x < 0 || x >= fieldLength || y < 0 || y >= fieldLength) {
				continue;
			}
			//If cross mode is enabled, don't place on diagonals
			if (cross && (x != coordinates.first && y != coordinates.second)) {
				continue;
			}
			//Don't place something on used fields
			if (isCoordinateUsed[std::make_pair(x, y)]) {
				continue;
			}

			int level = rand() % fieldLevels.size();
			std::pair<int, int> newCoordinates = retrieveFreeCoordinates(x, y);
			fieldArray[newCoordinates.first][newCoordinates.second].init(LField::GRASS, fieldLevels[level]);
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

		std::pair<int, int> coordinates(x, y);

		if (!isCoordinateUsed[coordinates]) {
			isCoordinateUsed[coordinates] = true;
			return coordinates;
		}
	}

	ASSERT(true, "No coordinates could be delivered. This should not happen.");
	return{};
}

std::pair<int, int> LPlayingField::retrieveFreeCoordinates(const int x, const int y)
{
	std::pair<int, int> coordinates(x, y);

	ASSERT(x >= 0 && x < fieldLength && y >= 0 && y < fieldLength, "The requested coordinates are out of range");
	ASSERT(!isCoordinateUsed[coordinates], "The coordinates requested are already used.");

	isCoordinateUsed[coordinates] = true;
	return coordinates;
}


NAMESPACE_LOGIC_E
