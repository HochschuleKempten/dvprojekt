#pragma once

#include "LGeneral.h"
#include "Array2D.h"
#include "LField.h"
#include "IVPlayingField.h"
#include "LPlayer.h"
#include "ILBuilding.h"
#include "LCity.h"
#include "LTransformerStation.h"
#include <boost/graph/adjacency_list.hpp>
#include "LPowerLine.h"
#include "LIdentifier.h"
#include "LBalanceLoader.h"
#include "LMessageLoader.h"
#include "LMaster.h"

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
class LRemoteOperation;
class ILPowerPlant;

class LPlayingField
{
	NON_COPYABLE(LPlayingField);
	friend class LMaster;
	friend class LRemoteOperation;

private:
	const int fieldLength = LBalanceLoader::getFieldLength();
	LMaster* lMaster = nullptr;
	std::shared_ptr<IVPlayingField> vPlayingField = nullptr;
	DynArray2D<LField> fieldArray;

	using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
	Graph powerLineGraph;

	LTransformerStation* transformerStation = nullptr;

	/** @brief Stores every unused coordinates. Is empty after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> unusedCoordinates;
	/** @brief Stores every used coordinate. Is full after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> usedCoordinates;
	/** @brief Stores the 1D coordinates for each pair of buildings which are connected */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> connectedBuildings;

	int localOperation = 0;
	bool initDone = false;
	bool cityConnectionsRecalculate = true;
	bool isCheckInProgress = false;
	bool firstConnected = false; //true if local player already reached the transformer station

private:
	template <typename T>
	struct placeBuildingHelper
	{
		LPlayingField* playingField;

		explicit placeBuildingHelper(LPlayingField* playingField)
			: playingField(playingField)
		{}

		template <typename... Args>
		bool operator()(const int x, const int y, const Args ... arguments)
		{
			return playingField->getField(x, y)->setBuilding<T>(arguments...);
		}
	};

	template <>
	struct placeBuildingHelper<LPowerLine>
	{
		LPlayingField* playingField;

		explicit placeBuildingHelper(LPlayingField* playingField)
			: playingField(playingField)
		{}

		template <typename... Args>
		bool operator()(const int x, const int y, const Args ... arguments)
		{
			int orientation = playingField->linkPowerlines(x, y, arguments...);

			return playingField->getField(x, y)->setBuilding<LPowerLine>(orientation, arguments...);
		}
	};

	template<typename T>
	void setSpecialBuildings(const int x, const int y, const int playerId)
	{
		if (std::is_base_of<ILPowerPlant, T>::value)
		{
			lMaster->getPlayer(playerId)->addPowerPlant(CASTD<ILPowerPlant*>(getField(x, y)->getBuilding()));
		}
	}
	template<>
	void setSpecialBuildings<LPowerLine>(const int x, const int y, const int playerId)
	{
		lMaster->getPlayer(playerId)->addPowerLine(CASTD<LPowerLine*>(getField(x, y)->getBuilding()));
	}
	template<>
	void setSpecialBuildings<LCity>(const int x, const int y, const int playerId)
	{
		lMaster->getPlayer(playerId)->setCity(CASTD<LCity*>(getField(x, y)->getBuilding()));
	}
	template<>
	void setSpecialBuildings<LTransformerStation>(const int x, const int y, const int /*playerId*/)
	{
		transformerStation = CASTD<LTransformerStation*>(getField(x, y)->getBuilding());
	}

	// returns true if building could be placed, else false (building not allowed or building already placed)
	template <typename T, typename... Args>
	bool placeBuilding(const int x, const int y, const int playerId, const Args ... arguments)
	{
		//Seems to be the only possibility to restrict the template type. Performs compile time checks and produces compile errors, if the type is wrong
		static_assert(std::is_base_of<ILBuilding, T>::value, "Wrong type. The type T needs to be a derived class from ILBuilding");

		//Check costs
		if (playerId & LPlayer::Local && lMaster->getPlayer(LPlayer::Local)->getMoney() < LBalanceLoader::getCost<T>())
		{
			LMessageLoader::emitMessage(LMessageLoader::BUILD_NO_MONEY, { LMessageLoader::getNameForBuildingType<T>(), std::to_string(lMaster->getPlayer(LPlayer::Local)->getMoney()), std::to_string(LBalanceLoader::getCost<T>()) });
			return false;
		}

		bool buildingPlaced = false;
		
		if (playerId & LPlayer::Local) {
			if ((hasFriendlyNeighbor(x, y) || !isInitDone()) && placeBuildingHelper<T>(this)(x, y, playerId, arguments...)) {
				buildingPlaced = true;

				addBuildingToGraph(x, y, getField(x, y)->getBuilding()->getOrientation());

				//subtract money only if the local player placed the building
				lMaster->getPlayer(LPlayer::Local)->subtractMoney(LBalanceLoader::getCost<T>());
				getField(x, y)->getBuilding()->addValue(LBalanceLoader::getCost<T>());
			}
		}
		else if (playerId & LPlayer::Remote && placeBuildingHelper<T>(this)(x, y, playerId, arguments...))
		{
			buildingPlaced = true;
		}
		
		if (buildingPlaced) {
			setSpecialBuildings<T>(x, y, playerId);
			adjustOrientationsAround(x, y, getField(x, y)->getBuilding()->getOrientation());

			if (playerId == LPlayer::Local)
			{
				recalculateCityConnections();
			}

			//-----network-----
			if (!isLocalOperation())
			{
				lMaster->sendSetObject(LIdentifier::getIdentifierForType<T>(), x, y, std::to_string(playerId));
			}
			//-----network-----

			return true;
		}

		return false;
	}
	bool removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);

	void beginRemoteOperation();
	void endRemoteOperation();

	bool hasFriendlyNeighbor(const int x, const int y);
	void addBuildingToGraph(const int x, const int y, const int orientation);
	//Adds orientations
	void adjustOrientationsAround(const int x, const int y, const int orientation);
	//Removes orientations
	void adjustOrientationsAround(const int x, const int y);
	void printGraph();

	/**
	* @brief Sets grass on every field around the given coordinates.
	*
	* @param coordinates base field to place grass around
	* @param space adjusts the range of grass (number of fields for each side)
	*
	* @tparam cross specifies if all fields around should be set to grass or just the even ones (i. e. not the diagonal ones when set to <code>true</code>)
	*/
	template <bool cross = false>
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

public:
	explicit LPlayingField(LMaster* lMaster);
	~LPlayingField();

	void initField(const int x, const int y, const LField::FieldType fieldType, const LField::FieldLevel fieldLevel);
	int linkPowerlines(const int x, const int y, const int playerId);

	void createFields();
	void showPlayingField();

	/**
	 * @brief Checks if the connection between the buildings still exists (from the stored values).
	 */
	void recheckConnectedBuildings();
	bool checkConnectionBuildings(const ILBuilding* b1, const ILBuilding* b2);
	bool isTransformstationConnected();

	void calculateEnergyValueCity();
	std::vector<int> getCityConnections();

	void recalculateCityConnections();

	bool checkIndex(const int x, const int y);
	int convertIndex(const std::pair<int, int>& coordinates);
	int convertIndex(const int x, const int y);
	std::pair<int, int> convertIndex(const int idx);
	bool isInitDone() const;
	bool isLocalOperation() const
	{
		return localOperation == 0;
	}

	bool isFirstConnected() const
	{
		return firstConnected;
	}

	void setFirstConnected()
	{
		firstConnected = true;
	}

	std::unordered_map<ILBuilding::Orientation, LField*> getFieldNeighbors(const int x, const int y);
	LField* getField(const int x, const int y);
	LField* getField(const std::pair<int, int>& coordinates);
	int getFieldLength();
	LMaster* getLMaster();
	IVPlayingField* getVPlayingField();
};


NAMESPACE_LOGIC_E
