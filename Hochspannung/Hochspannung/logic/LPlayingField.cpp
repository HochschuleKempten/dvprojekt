#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LUtility.h"
#include "LCity.h"
#include "LTransformerSation.h"
#include "LCoalPowerPlant.h"
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/lookup_edge.hpp>
#include <random>
#include <chrono>

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
	  unusedCoordinates(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  usedCoordinates(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  connectedBuildings(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  fieldTypes({LField::MOUNTAIN, LField::AIR, LField::SOLAR, LField::WATER, LField::COAL, LField::OIL}),
	  fieldLevels({LField::LEVEL1, LField::LEVEL2, LField::LEVEL3})
{
	//At the beginning every field is unused
	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {
			unusedCoordinates.emplace(x, y);
		}
	}

	vPlayingField = lMaster->getVMaster()->getFactory()->createPlayingField(this);
	vPlayingField->initPlayingField(vPlayingField); //Sets the shared_ptr (need to be done before the fields can be created)
	
	//todo (L) call only for host
	createFields(); //Create the fields (also places some buildings)

	ASSERT(unusedCoordinates.empty(), "The container for the unused coordinates are not empty (There are field wich are not initialized)");
	ASSERT(usedCoordinates.size() == fieldLength*fieldLength, "Not every cordinates are in the set for the used coordinates. This is an indication that something in the initialization process went wrong");
	vPlayingField->buildPlayingField(); //Now build the playing field
}

LPlayingField::~LPlayingField()
{
}

std::unordered_map<ILBuilding::Orientation, LField*> LPlayingField::getFieldNeighbors(const int x, const int y)
{
	std::unordered_map<ILBuilding::Orientation, LField*> neighborsMap;

	if (checkIndex(x - 1, y)) {
		neighborsMap[ILBuilding::Orientation::NORTH] = getField(x - 1, y);
	}

	if (checkIndex(x, y + 1)) {
		neighborsMap[ILBuilding::Orientation::EAST] = getField(x, y + 1);
	}

	if (checkIndex(x + 1, y)) {
		neighborsMap[ILBuilding::Orientation::SOUTH] = getField(x + 1, y);
	}

	if (checkIndex(x, y - 1)) {
		neighborsMap[ILBuilding::Orientation::WEST] = getField(x, y - 1);
	}
	
	return neighborsMap;
}

int LPlayingField::linkPowerlines(const int x, const int y)
{
	std::unordered_map<ILBuilding::Orientation, LField*> neighbors = getFieldNeighbors(x, y);
	int oriention = 0;

	for (auto const &iterator : neighbors) {
		//No Building
		if (iterator.second->getBuilding() == nullptr)
		{
			continue;
		}

		//There is a building, so the orientation of the powerline must be set to this building
		//The adjustment of the orientation of the other powerlines is done automatically when inserting the edge to the graph
		oriention |= iterator.first;
	}

	return oriention;
}

void LPlayingField::beginRemoteOperation()
{
	isLocalOperation = false;
}

void LPlayingField::endRemoteOperation()
{
	isLocalOperation = true;
}

bool LPlayingField::checkConnectionBuildings(const std::pair<int, int>& first, const std::pair<int, int>& second)
{
	//Store always the lower idx as first parameter
	//This is necessary, so if I check the connection between 1 and 2 it should be the same as 2 and 1
	int firstIndex = convertIndex(first);
	int secondIndex = convertIndex(second);
	if (firstIndex < secondIndex) {
		std::swap(firstIndex, secondIndex);
	}

	//The idx pair is already in the set, so there is a connection
	if (connectedBuildings.count(std::pair<int, int>(firstIndex, secondIndex)) > 0) {
		return true;
	}

	//The idx is not in the set, so check the connection in the graph
	std::vector<int> buildingsConnectedWithCity = strongConnectedSearch(powerLineGraph, convertIndex(localCityPosition));
	bool connected = std::find(buildingsConnectedWithCity.begin(), buildingsConnectedWithCity.end(), convertIndex(transformerStationPosition)) != buildingsConnectedWithCity.end();

	//The idx are now connected, store them in the set, so that the information can be used later
	if (connected) {
		connectedBuildings.emplace(firstIndex, secondIndex);
	}

	return connected;
}

bool LPlayingField::isTransformstationConnected()
{
	return checkConnectionBuildings(localCityPosition, transformerStationPosition);
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

	//-----network-----
	if (!isLocalOperation)
	{
		lMaster->sendDeleteObject(x, y);
	}
	else
	{
		calculateEnergyValueCity();
	}
	//-----network-----
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	//todo (IP) getPlayers(): get current player
	if (lMaster->getPlayer(LPlayer::Local)->getMoney() > 50000) {

		getField(x, y)->getBuilding()->upgrade();

		if (!isLocalOperation)
		{
			//todo (IP) sendUpgrade
		}
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

void LPlayingField::createFields()
{
	//-----Generate buildings for LOCAL player----

	//todo (L) generate this randomly
	//todo (L) send playerid

	localCityPosition = retrieveFreeCoordinates(5, 5);
	std::pair<int, int> firstPowerLineCoordinates = retrieveFreeCoordinates(localCityPosition.first, localCityPosition.second + 1);
	std::pair<int, int> secondPowerLineCoordinates = retrieveFreeCoordinates(firstPowerLineCoordinates.first + 1, firstPowerLineCoordinates.second);
	std::pair<int, int> firstPowerPlantCoordinates = retrieveFreeCoordinates(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second + 1);
	transformerStationPosition = retrieveFreeCoordinates();

	fieldArray[localCityPosition.first][localCityPosition.second].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);
	placeBuilding<LCity>(localCityPosition.first, localCityPosition.second);
	placeGrassAroundPosition(localCityPosition, 1);

	fieldArray[firstPowerLineCoordinates.first][firstPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(firstPowerLineCoordinates.first, firstPowerLineCoordinates.second);

	fieldArray[secondPowerLineCoordinates.first][secondPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second);

	fieldArray[firstPowerPlantCoordinates.first][firstPowerPlantCoordinates.second].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);
	placeBuilding<LCoalPowerPlant>(firstPowerPlantCoordinates.first, firstPowerPlantCoordinates.second);
	placeGrassAroundPosition<true>(firstPowerPlantCoordinates, 1);

	fieldArray[transformerStationPosition.first][transformerStationPosition.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LTransformerStation>(transformerStationPosition.first, transformerStationPosition.second);
	
	//-----Generate buildings for LOCAL player----


	//-----Generate buildings for REMOTE player----

	beginRemoteOperation();

	remoteCityPosition = retrieveFreeCoordinates(fieldLength - static_cast<int>(fieldLength / 4), fieldLength - static_cast<int>(fieldLength / 4));

	std::pair<int, int> firstRemotePowerLineCoordinates = retrieveFreeCoordinates(remoteCityPosition.first, remoteCityPosition.second + 1);
	std::pair<int, int> secondRemotePowerLineCoordinates = retrieveFreeCoordinates(firstRemotePowerLineCoordinates.first + 1, firstRemotePowerLineCoordinates.second);
	std::pair<int, int> firstRemotePowerPlantCoordinates = retrieveFreeCoordinates(secondRemotePowerLineCoordinates.first, secondRemotePowerLineCoordinates.second + 1);

	fieldArray[remoteCityPosition.first][remoteCityPosition.second].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);
	placeBuilding<LCity>(remoteCityPosition.first, remoteCityPosition.second);
	placeGrassAroundPosition(remoteCityPosition, 1);

	fieldArray[firstRemotePowerLineCoordinates.first][firstRemotePowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(firstRemotePowerLineCoordinates.first, firstRemotePowerLineCoordinates.second, ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);

	fieldArray[secondRemotePowerLineCoordinates.first][secondRemotePowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);
	placeBuilding<LPowerLine>(secondRemotePowerLineCoordinates.first, secondRemotePowerLineCoordinates.second, ILBuilding::NORTH | ILBuilding::EAST | ILBuilding::SOUTH | ILBuilding::WEST);

	fieldArray[firstRemotePowerPlantCoordinates.first][firstRemotePowerPlantCoordinates.second].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);
	placeBuilding<LCoalPowerPlant>(firstRemotePowerPlantCoordinates.first, firstRemotePowerPlantCoordinates.second);
	placeGrassAroundPosition<true>(firstRemotePowerPlantCoordinates, 1);

	endRemoteOperation();
	//-----Generate buildings for REMOTE player----

	//Fill with the requested number of power plants
	std::chrono::system_clock::rep seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 g1(seed1);
	const int numberOfPowerPlants = (fieldLength * fieldLength) / 8;
	for (int i = 0; i < numberOfPowerPlants; i++) {
		std::pair<int, int> newCoordinates = retrieveFreeCoordinates();
		int type = g1() % fieldTypes.size();
		int level = g1() % fieldLevels.size();
		fieldArray[newCoordinates.first][newCoordinates.second].init(fieldTypes[type], fieldLevels[level]);
		DEBUG_OUTPUT("power plant placed " << i << ": " << type << ", " << level << " at " << newCoordinates.first << ":" << newCoordinates.second);

		placeGrassAroundPosition<true>(newCoordinates, 1);
	}

	//Fill the rest with grass
	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {

			if (isCoordinateUsed(std::make_pair(x, y))) {
				//Coordinate already assigned
				continue;
			}
			
			int level = rand() % fieldLevels.size();
			std::pair<int, int> coordinates = retrieveFreeCoordinates(x, y);
			fieldArray[coordinates.first][coordinates.second].init(LField::GRASS, fieldLevels[level]);
		}
	}
}

LField* LPlayingField::getField(const int x, const int y)
{
	return &fieldArray[x][y];
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
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

int LPlayingField::convertIndex(const std::pair<int, int>& coordinates)
{
	return convertIndex(coordinates.first, coordinates.second);
}

int LPlayingField::convertIndex(const int x, const int y)
{
	return x * fieldLength + y;
}

std::pair<int, int> LPlayingField::convertIndex(const int idx)
{
	return std::make_pair(idx / fieldLength, idx % fieldLength);
}

void LPlayingField::calculateEnergyValueCity()
{
	int energyValue = 0;

	std::vector<int> vec = strongConnectedSearch(powerLineGraph, convertIndex(localCityPosition));
	std::pair<int, int> coord;

	for (size_t i = 0; i < vec.size(); i++) {
		coord = convertIndex(vec[i]);
		ILPowerPlant* pP = dynamic_cast<ILPowerPlant*>(getField(coord.first, coord.second)->getBuilding());

		if (pP != nullptr && pP->getPlayerId() == LPlayer::Local)
		{
			energyValue += pP->getEnergyValue();
		}
	}

	getLocalCity()->setEnergy(energyValue);
}

void LPlayingField::addEdgeToGraph(const int xStart, const int yStart, const int xEnd, const int yEnd, const int totalOrientation, const ILBuilding::Orientation checkOrientation)
{
	if (totalOrientation & checkOrientation) {
		//Check if idx is not out of range and if an edge already exists
		if (checkIndex(xEnd, yEnd) && !lookup_edge(convertIndex(xStart, yStart), convertIndex(xEnd, yEnd), powerLineGraph).second) {
			add_edge(convertIndex(xStart, yStart), convertIndex(xEnd, yEnd), powerLineGraph);

			//If the target vertex is a power line adjust the orientation of that powerline and add an edge from the powerline to this building
			LPowerLine* plOther = dynamic_cast<LPowerLine*>(getField(xEnd, yEnd)->getBuilding());
			if (plOther != nullptr) {
				add_edge(convertIndex(xEnd, yEnd), convertIndex(xStart, yStart), powerLineGraph);
				plOther->updatedOrientation(ILBuilding::getOpppositeOrienttion(checkOrientation));
			}
		}
	}
}

void LPlayingField::addBuildingToGraph(const int x, const int y, const int orientation)
{
	addEdgeToGraph(x, y, x - 1, y, orientation, ILBuilding::NORTH);
	addEdgeToGraph(x, y, x, y + 1, orientation, ILBuilding::EAST);
	addEdgeToGraph(x, y, x + 1, y, orientation, ILBuilding::SOUTH);
	addEdgeToGraph(x, y, x, y - 1, orientation, ILBuilding::WEST);

	//DEBUG_EXPRESSION(printGraph());
}

void LPlayingField::printGraph()
{
	std::vector<std::string> names(fieldLength*fieldLength);

	for (int x = 0; x < fieldLength; x++) {
		for (int y = 0; y < fieldLength; y++) {
			std::string name = std::to_string(x) + std::string(", ") + std::to_string(y);
			names[convertIndex(x, y)] = name;
		}
	}

	std::ofstream file;
	file.open("graph.dot");
	write_graphviz(file, powerLineGraph, make_label_writer(&names[0]));

	//Install http://www.graphviz.org/ and run
	//dot -Tpng -o graph.png graph.dot
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
			if (isCoordinateUsed(std::make_pair(x, y))) {
				continue;
			}

			int level = rand() % fieldLevels.size();
			std::pair<int, int> newCoordinates = retrieveFreeCoordinates(x, y);
			fieldArray[newCoordinates.first][newCoordinates.second].init(LField::GRASS, fieldLevels[level]);
		}
	}
}

bool LPlayingField::isCoordinateUsed(const std::pair<int, int>& coordinates) const
{
	return usedCoordinates.count(coordinates) > 0;
}

std::pair<int, int> LPlayingField::retrieveFreeCoordinates()
{
	std::chrono::system_clock::rep seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 g1(seed1);

	//Get new idx from the unused coordinates
	int coordinateIdx = g1() % unusedCoordinates.size();
	auto itUnusedCoordinates = unusedCoordinates.begin();
	
	//Get the random coordinates
	std::advance(itUnusedCoordinates, coordinateIdx);
	std::pair<int, int> coordinates = *itUnusedCoordinates;

	//Adjust sets
	unusedCoordinates.erase(coordinates);
	usedCoordinates.emplace(coordinates);

	return coordinates;
}

std::pair<int, int> LPlayingField::retrieveFreeCoordinates(const int x, const int y)
{
	std::pair<int, int> coordinates(x, y);

	ASSERT(x >= 0 && x < fieldLength && y >= 0 && y < fieldLength, "The requested coordinates are out of range");
	ASSERT(!isCoordinateUsed(coordinates), "The coordinates requested are already used.");

	unusedCoordinates.erase(coordinates);
	usedCoordinates.emplace(coordinates);

	return coordinates;
}


NAMESPACE_LOGIC_E
