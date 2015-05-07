#include "LPlayingField.h"
#include "LPlayer.h"
#include "LPowerLine.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LUtility.h"
#include "LCity.h"
#include "LTransformerStation.h"
#include "LCoalPowerPlant.h"
#include "LBalanceLoader.h"
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
	std::vector<int> component(num_vertices(g));
	strong_components(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

	int mainComponent = component[startIdx];
	std::vector<int> vertices;

	for (size_t i = 0; i < component.size(); i++)
	{
		if (component[i] == mainComponent && i != CASTS<size_t>(startIdx))
		{
			vertices.push_back(CASTS<int>(i));
		}
	}

	return vertices;
}

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray([this] (LField& f)
		  {
			  f.setLPlayingField(this);
		  }),
	  powerLineGraph(fieldLength * fieldLength),
	  unusedCoordinates(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  usedCoordinates(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength)),
	  connectedBuildings(fieldLength * fieldLength, LPlayingFieldHasher(fieldLength))
{
	//At the beginning every field is unused
	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			unusedCoordinates.emplace(x, y);
		}
	}

	vPlayingField = lMaster->getVMaster()->getFactory()->createPlayingField(this);
	vPlayingField->initPlayingField(vPlayingField); //Sets the shared_ptr (need to be done before the fields can be created)
}

LPlayingField::~LPlayingField()
{
}

void LPlayingField::showPlayingField()
{
	ASSERT(unusedCoordinates.empty(), "The container for the unused coordinates are not empty (There are field wich are not initialized)");
	ASSERT(usedCoordinates.size() == CASTS<size_t>(fieldLength*fieldLength), "Not every cordinates are in the set for the used coordinates. This is an indication that something in the initialization process went wrong");

	vPlayingField->buildPlayingField(); //Now build the playing field
	initDone = true;
}

bool LPlayingField::isInitDone()
{
	return initDone;
}

std::unordered_map<ILBuilding::Orientation, LField*> LPlayingField::getFieldNeighbors(const int x, const int y)
{
	std::unordered_map<ILBuilding::Orientation, LField*> neighborsMap;

	if (checkIndex(x - 1, y))
	{
		neighborsMap[ILBuilding::Orientation::NORTH] = getField(x - 1, y);
	}

	if (checkIndex(x, y + 1))
	{
		neighborsMap[ILBuilding::Orientation::EAST] = getField(x, y + 1);
	}

	if (checkIndex(x + 1, y))
	{
		neighborsMap[ILBuilding::Orientation::SOUTH] = getField(x + 1, y);
	}

	if (checkIndex(x, y - 1))
	{
		neighborsMap[ILBuilding::Orientation::WEST] = getField(x, y - 1);
	}

	return neighborsMap;
}

int LPlayingField::linkPowerlines(const int x, const int y)
{
	std::unordered_map<ILBuilding::Orientation, LField*> neighbors = getFieldNeighbors(x, y);
	int oriention = 0;

	for (auto const& iterator : neighbors)
	{
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

void LPlayingField::initField(const int x, const int y, const LField::FieldType fieldType, const LField::FieldLevel fieldLevel)
{
	std::pair<int, int> coordinates = retrieveFreeCoordinates(x, y);
	fieldArray[coordinates.first][coordinates.second].init(fieldType, fieldLevel);
}

void LPlayingField::recheckConnectedBuildings()
{
	//http://stackoverflow.com/questions/800955/remove-if-equivalent-for-stdmap
	for (auto it = connectedBuildings.begin(); it != connectedBuildings.end(); /* No incrementation here */)
	{
		std::vector<int> buildingsConnectedWithCity = strongConnectedSearch(powerLineGraph, it->first);
		bool connected = std::find(buildingsConnectedWithCity.begin(), buildingsConnectedWithCity.end(), it->second) != buildingsConnectedWithCity.end();

		if (!connected)
		{
			//Remove all buildings which are not connected anymore
			it = connectedBuildings.erase(it); //The function returns the iterator following the last removed element
		}
		else
		{
			++it;
		}
	}
}

bool LPlayingField::checkConnectionBuildings(const std::pair<int, int>& first, const std::pair<int, int>& second)
{
	//Store always the lower idx as first parameter
	//This is necessary, so if I check the connection between 1 and 2 it should be the same as 2 and 1
	int idxFirst = convertIndex(first);
	int idxSecond = convertIndex(second);
	if (idxFirst < idxSecond)
	{
		std::swap(idxFirst, idxSecond);
	}

	//The idx pair is already in the set, so there is a connection
	if (connectedBuildings.count(std::make_pair(idxFirst, idxSecond)) > 0)
	{
		return true;
	}

	//The idx is not in the set, so check the connection in the graph
	//Search from the first index and check if from this point the second index can be reached
	std::vector<int> buildingsConnectedWithCity = strongConnectedSearch(powerLineGraph, idxFirst);
	bool connected = std::find(buildingsConnectedWithCity.begin(), buildingsConnectedWithCity.end(), idxSecond) != buildingsConnectedWithCity.end();

	//The idx are now connected, store them in the set, so that the information can be used later
	if (connected)
	{
		connectedBuildings.emplace(idxFirst, idxSecond);
	}

	return connected;
}

bool LPlayingField::isTransformstationConnected()
{
	return checkConnectionBuildings(localCityPosition, transformerStationPosition);
}

void LPlayingField::removeBuilding(const int x, const int y)
{
	int playerId = getField(x, y)->getBuilding() != nullptr ? getField(x, y)->getBuilding()->getPlayerId() : -1;

	if (getField(x, y)->removeBuilding())
	{
		vPlayingField->objectRemoved(x, y);

		if (playerId == LPlayer::Local)
		{
			//remove all outgoing edges
			powerLineGraph.m_vertices[convertIndex(x, y)].m_out_edges.clear();
			calculateEnergyValueCity();
			recheckConnectedBuildings();
		}

		if (!isLocalOperation)
		{		
			lMaster->sendDeleteObject(x, y);			
		}
		
	}
	else
	{
		//TODO (All) how to handle error checks?
	}
}

void LPlayingField::upgradeBuilding(const int x, const int y)
{
	if (lMaster->getPlayer(LPlayer::Local)->getMoney() > 50000)
	{
		getField(x, y)->getBuilding()->upgrade();
	}
	// ToDo (FL) Discuss case player doesn't have enough money
}

bool LPlayingField::hasFriendlyNeighbor(int x, const int y)
{
	std::unordered_map<ILBuilding::Orientation, LField*> neighbors = this->getFieldNeighbors(x, y);
	for (std::unordered_map<ILBuilding::Orientation, LField*>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
	{
		if (it->second->getBuilding() != nullptr && (it->second->getBuilding()->getPlayerId() == LPlayer::Local))
		{
			return true;
		}
	}

	return false;
}

void LPlayingField::createFields()
{
	//-----Generate buildings for LOCAL player----

	//todo (L) generate this randomly

	localCityPosition = retrieveFreeCoordinates(5, 5);
	std::pair<int, int> firstPowerLineCoordinates = retrieveFreeCoordinates(localCityPosition.first, localCityPosition.second + 1);
	std::pair<int, int> secondPowerLineCoordinates = retrieveFreeCoordinates(firstPowerLineCoordinates.first + 1, firstPowerLineCoordinates.second);
	std::pair<int, int> firstPowerPlantCoordinates = retrieveFreeCoordinates(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second + 1);
	transformerStationPosition = retrieveFreeCoordinates();

	//--
	fieldArray[localCityPosition.first][localCityPosition.second].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);

	placeBuilding<LCity>(localCityPosition.first, localCityPosition.second, LPlayer::Local);

	placeGrassAroundPosition(localCityPosition, 1);
	//--

	//--
	fieldArray[firstPowerLineCoordinates.first][firstPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);

	placeBuilding<LPowerLine>(firstPowerLineCoordinates.first, firstPowerLineCoordinates.second, LPlayer::Local);
	//--

	//--
	fieldArray[secondPowerLineCoordinates.first][secondPowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);

	placeBuilding<LPowerLine>(secondPowerLineCoordinates.first, secondPowerLineCoordinates.second, LPlayer::Local);
	//--

	//--
	fieldArray[firstPowerPlantCoordinates.first][firstPowerPlantCoordinates.second].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);

	placeBuilding<LCoalPowerPlant>(firstPowerPlantCoordinates.first, firstPowerPlantCoordinates.second, LPlayer::Local);

	placeGrassAroundPosition<true>(firstPowerPlantCoordinates, 1);
	//--

	//--
	fieldArray[transformerStationPosition.first][transformerStationPosition.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);

	placeBuilding<LTransformerStation>(transformerStationPosition.first, transformerStationPosition.second, LPlayer::Local | LPlayer::External); //Transformerstation belongs to no player
	//--

	//-----Generate buildings for LOCAL player----


	//-----Generate buildings for REMOTE player----

	remoteCityPosition = retrieveFreeCoordinates(fieldLength - static_cast<int>(fieldLength / 4), fieldLength - static_cast<int>(fieldLength / 4));

	std::pair<int, int> firstRemotePowerLineCoordinates = retrieveFreeCoordinates(remoteCityPosition.first, remoteCityPosition.second + 1);
	std::pair<int, int> secondRemotePowerLineCoordinates = retrieveFreeCoordinates(firstRemotePowerLineCoordinates.first + 1, firstRemotePowerLineCoordinates.second);
	std::pair<int, int> firstRemotePowerPlantCoordinates = retrieveFreeCoordinates(secondRemotePowerLineCoordinates.first, secondRemotePowerLineCoordinates.second + 1);

	//--
	fieldArray[remoteCityPosition.first][remoteCityPosition.second].init(LField::FieldType::CITY, LField::FieldLevel::LEVEL1);

	placeBuilding<LCity>(remoteCityPosition.first, remoteCityPosition.second, LPlayer::External);
	placeGrassAroundPosition(remoteCityPosition, 1);
	//--

	//--
	fieldArray[firstRemotePowerLineCoordinates.first][firstRemotePowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);

	placeBuilding<LPowerLine>(firstRemotePowerLineCoordinates.first, firstRemotePowerLineCoordinates.second, LPlayer::External);
	//--

	//--
	fieldArray[secondRemotePowerLineCoordinates.first][secondRemotePowerLineCoordinates.second].init(LField::FieldType::GRASS, LField::FieldLevel::LEVEL1);

	placeBuilding<LPowerLine>(secondRemotePowerLineCoordinates.first, secondRemotePowerLineCoordinates.second, LPlayer::External);
	//--

	//--
	fieldArray[firstRemotePowerPlantCoordinates.first][firstRemotePowerPlantCoordinates.second].init(LField::FieldType::COAL, LField::FieldLevel::LEVEL1);

	placeBuilding<LCoalPowerPlant>(firstRemotePowerPlantCoordinates.first, firstRemotePowerPlantCoordinates.second, LPlayer::External);
	placeGrassAroundPosition<true>(firstRemotePowerPlantCoordinates, 1);
	//--

	//-----Generate buildings for REMOTE player----

	const int numberOfPowerPlants = (fieldLength * fieldLength) / 8;
	const std::unordered_map<LField::FieldType, double> fieldTypes = LBalanceLoader::getFieldTypeRatio();
	const std::unordered_map<LField::FieldLevel, double> fieldLevels = LBalanceLoader::getFieldLevelFactor();

	std::chrono::system_clock::rep seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 g1(seed1);

	//Fill with the requested number of power plants
	for (const auto& fieldPair : fieldTypes)
	{
		const int currentNumberPowerPlants = CASTS<int>(numberOfPowerPlants * fieldPair.second);

		for (int i = 0; i < currentNumberPowerPlants; i++)
		{
			std::pair<int, int> newCoordinates = retrieveFreeCoordinates();
			auto itFieldLevel = fieldLevels.begin();
			std::advance(itFieldLevel, g1() % fieldLevels.size());

			fieldArray[newCoordinates.first][newCoordinates.second].init(fieldPair.first, itFieldLevel->first);
			DEBUG_OUTPUT("power plant placed " << i << ": " << fieldPair.first << ", " << itFieldLevel->first << " at " << newCoordinates.first << ":" << newCoordinates.second);

			placeGrassAroundPosition<true>(newCoordinates, 1);
		}
	}

	//Fill the rest with grass
	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			if (isCoordinateUsed(std::make_pair(x, y)))
			{
				//Coordinate already assigned
				continue;
			}

			std::pair<int, int> coordinates = retrieveFreeCoordinates(x, y);
			auto itFieldLevel = fieldLevels.begin();
			std::advance(itFieldLevel, g1() % fieldLevels.size());
			fieldArray[coordinates.first][coordinates.second].init(LField::GRASS, itFieldLevel->first);

		}
	}

	//-----network-----
	for (int x = 0; x < fieldLength; x++)
	{
		std::vector<Network::FieldTransfer> row;

		for (int y = 0; y < fieldLength; y++)
		{
			LField* field = getField(x, y);

			Network::FieldTransfer fieldTransfer;
			fieldTransfer.iObjectID = field->getBuildingId();
			fieldTransfer.iPlayerID = field->getBuilding() != nullptr ? field->getBuilding()->getPlayerId() : -1;
			fieldTransfer.iFieldLevel = field->getFieldLevel();
			fieldTransfer.iFieldType = field->getFieldType();

			row.push_back(fieldTransfer);
		}

		lMaster->sendSetMapRow(x, row);
	}

	lMaster->sendSetObject(-1, -1, -1, std::to_string(-66)); //host finished creating the field
	//-----network-----
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

	for (size_t i = 0; i < vec.size(); i++)
	{
		coord = convertIndex(vec[i]);
		ILPowerPlant* pP = dynamic_cast<ILPowerPlant*>(getField(coord.first, coord.second)->getBuilding());

		if (pP != nullptr && pP->getPlayerId() == LPlayer::Local)
		{
			energyValue += LBalanceLoader::getProducedEnergy(pP->getIdentifier());
		}
	}

	getLocalCity()->setEnergy(energyValue);
}

void LPlayingField::addBuildingToGraph(const int x, const int y, const int orientation)
{
	auto addEdgeToGraph = [this, x, y, orientation] (const int xEnd, const int yEnd, const ILBuilding::Orientation checkOrientation)
		{
			if (orientation & checkOrientation)
			{
				//Check if idx is not out of range and if an edge already exists
				if (checkIndex(xEnd, yEnd) && !lookup_edge(convertIndex(x, y), convertIndex(xEnd, yEnd), powerLineGraph).second)
				{
					add_edge(convertIndex(x, y), convertIndex(xEnd, yEnd), powerLineGraph);

					//If the target vertex is a power line adjust the orientation of that powerline and add an edge from the powerline to this building
					LPowerLine* plOther = dynamic_cast<LPowerLine*>(getField(xEnd, yEnd)->getBuilding());
					if (plOther != nullptr)
					{
						add_edge(convertIndex(xEnd, yEnd), convertIndex(x, y), powerLineGraph);
						plOther->updatedOrientation(ILBuilding::getOpppositeOrienttion(checkOrientation));
					}
				}
			}
		};

	addEdgeToGraph(x, y + 1, ILBuilding::EAST);
	addEdgeToGraph(x - 1, y, ILBuilding::NORTH);
	addEdgeToGraph(x + 1, y, ILBuilding::SOUTH);
	addEdgeToGraph(x, y - 1, ILBuilding::WEST);

	//DEBUG_EXPRESSION(printGraph());
}

void LPlayingField::printGraph()
{
	std::vector<std::string> names(fieldLength * fieldLength);

	for (int x = 0; x < fieldLength; x++)
	{
		for (int y = 0; y < fieldLength; y++)
		{
			names[convertIndex(x, y)] = std::to_string(x) + std::string(", ") + std::to_string(y);
		}
	}

	std::ofstream file;
	file.open("graph.dot");
	if (file.is_open())
	{
		write_graphviz(file, powerLineGraph, make_label_writer(&names[0]));
	}

	//Install graphviz from http://www.graphviz.org/ and run
	//dot -Tpng -o graph.png graph.dot
	//See http://blog.milania.de/index.php?/archives/13-Boost-Graphen-mit-Hilfe-von-Graphviz-anzeigen.html for more information
}

template <bool cross>
void LPlayingField::placeGrassAroundPosition(const std::pair<int, int>& coordinates, const int space)
{
	const std::unordered_map<LField::FieldLevel, double> fieldLevels = LBalanceLoader::getFieldLevelFactor();
	std::chrono::system_clock::rep seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 g1(seed1);

	for (int rowIdx = -space; rowIdx <= space; rowIdx++)
	{
		for (int colIdx = -space; colIdx <= space; colIdx++)
		{
			int x = coordinates.first + rowIdx;
			int y = coordinates.second + colIdx;

			//Don't place something on the base field
			if (rowIdx == 0 && colIdx == 0)
			{
				continue;
			}
			//Bounds checking
			if (x < 0 || x >= fieldLength || y < 0 || y >= fieldLength)
			{
				continue;
			}
			//If cross mode is enabled, don't place on diagonals
			if (cross && (x != coordinates.first && y != coordinates.second))
			{
				continue;
			}
			//Don't place something on used fields
			if (isCoordinateUsed(std::make_pair(x, y)))
			{
				continue;
			}

			std::pair<int, int> newCoordinates = retrieveFreeCoordinates(x, y);
			auto itFieldLevel = fieldLevels.begin();
			std::advance(itFieldLevel, g1() % fieldLevels.size());

			fieldArray[newCoordinates.first][newCoordinates.second].init(LField::GRASS, itFieldLevel->first);
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
	std::mt19937_64 g1(seed1);

	//Get new idx from the unused coordinates
	size_t coordinateIdx = g1() % unusedCoordinates.size();
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
