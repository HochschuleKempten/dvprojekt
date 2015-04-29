#pragma once
#include "LGeneral.h"
#include "Array2D.h"
#include "LField.h"
#include "IVPlayingField.h"
#include "LPlayer.h"
#include "ILBuilding.h"
#include "LCity.h"
#include <boost/graph/adjacency_list.hpp>

NAMESPACE_LOGIC_B


struct LPlayingFieldHasher
{
	int fieldLength;

	explicit LPlayingFieldHasher(const int fieldLength)
		: fieldLength(fieldLength)
	{}

	std::size_t operator()(const std::pair<int, int>& coordinates) const
	{
		return coordinates.first * fieldLength + coordinates.second;
	}
};

class LMaster;
class LPowerLine;

class LPlayingField
{
	NON_COPYABLE(LPlayingField);

private:
	const int fieldLength = 20; // MUSS durch 5 Teilbar sein!!!!! (@MB: Satzzeichen sind keine Rudeltiere :P) (@IP STFU!!!!! :p ) todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster = nullptr;
	std::shared_ptr<IVPlayingField> vPlayingField = nullptr;
	Array2D<LField> fieldArray;

	using Graph = boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS>;
	Graph powerLineGraph;
	std::pair<int, int> cityPosition = std::make_pair(-1, -1);
	std::pair<int, int> transformerStationPosition = std::make_pair(-1, -1);

	/** @brief Stores every unused coordinates. Is empty after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> unusedCoordinates;
	/** @brief Stores every used coordinate. Is full after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> usedCoordinates;
	/** @brief Stores the 1D coordinates for each pair of buildings which are connected */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> connectedBuildings;

	std::vector<LField::FieldType> fieldTypes;
	std::vector<LField::FieldLevel> fieldLevels;

public:
	LPlayingField(LMaster* lMaster);
	~LPlayingField();

	LField* getField(const int x, const int y);

	// returns true if building could be placed, else false (building not allowed or building already placed)
	template<typename T, typename... Args>
	bool placeBuilding(const int x, const int y, const Args... arguments)
	{
		//Seems to be the only possibility to restrict the template type. Performs compile time checks and produces compile errors, if the type is wrong
		static_assert(std::is_base_of<ILBuilding, T>::value, "Wrong type. The type T needs to be a derived class from ILBuilding");	
		
		//Check costs
		//todo (IP) getPlayers(): get current player
		if (lMaster->getPlayer(1)->getMoney() < T::cost) {
			vPlayingField->messageBuildingFailed(std::string("Kraftwerk ") + getClassName(T) + std::string(" kann nicht gebaut werden, da nur ") + std::to_string(lMaster->getPlayer(1)->getMoney()) + std::string(" EUR zur Verfügung stehen, es werden jedoch ") + std::to_string(T::cost) + std::string(" benötigt."));
			return false;
		}

		if (getField(x, y)->setBuilding<T>(x, y, arguments...)) {
			addBuildingToGraph(x, y, getField(x, y)->getBuilding()->getOrientation());

			//todo (L) when?
			if (cityPosition.first > -1 && cityPosition.second > -1)
			{
				calculateEnergyValueCity();
			}

			lMaster->getPlayer(1)->substractMoney(T::cost);
			DEBUG_OUTPUT("Marktplace connected = " << isTransformstationConnected());

			return true;
		}
		else {
			return false;
		}
	}
	
	bool checkConnectionBuildings(const std::pair<int, int>& first, const std::pair<int, int>& second);
	bool isTransformstationConnected();

	int getFieldLength();
	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LMaster* getLMaster();
	IVPlayingField* getVPlayingField();

	const std::pair<int, int>& getCityPosition() const
	{
		return cityPosition;
	}
	LCity* getCity()
	{
		return CASTD<LCity*>(getField(cityPosition.first, cityPosition.second)->getBuilding());
	}

private:
	void createFields();
	bool checkIndex(const int x, const int y);
	int convertIndex(const std::pair<int, int>& coordinates);
	int convertIndex(const int x, const int y);
	std::pair<int, int> convertIndex(const int idx);
	void calculateEnergyValueCity();
	void addBuildingToGraph(const int x, const int y, const int orientation);
	
	/**
	 * @brief Sets grass on every field around the given coordinates.
	 *
	 * @param coordinates base field to place grass around
	 * @param space adjusts the range of grass (number of fields for each side)
	 *
	 * @tparam cross specifies if all fields around should be set to grass or just the even ones (i. e. not the diagonal ones when set to <code>true</code>)
	 */
	template<bool cross = false>
	void placeGrassAroundPosition(const std::pair<int, int>& coordinates, const int space);

	bool isCoordinateUsed(const std::pair<int, int>& coordinates) const;

	/**
	 * @brief Generates new random coordinates which are not used yet.
	 *
	 * @return coordinate pair (x,y)
	 */
	std::pair<int, int> retrieveFreeCoordinates();

	/**
	 * @brief Tries to generate coordinates from the given parameter.
	 *
	 * The coordinates you pass to this function should be unused. Otherwise the assertion fails.
	 * The main purpose of this function is to store the coordinates which you want to use.
	 * 
	 * @param x the first coordinate
	 * @param y the second coordinate
	 *
	 * @return coordinate pair (x,y)
	 */
	std::pair<int, int> retrieveFreeCoordinates(const int x, const int y);
};


NAMESPACE_LOGIC_E
