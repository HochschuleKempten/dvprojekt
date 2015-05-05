#pragma once
#include "LGeneral.h"
#include "Array2D.h"
#include "LField.h"
#include "IVPlayingField.h"
#include "LPlayer.h"
#include "ILBuilding.h"
#include "LCity.h"
#include <boost/graph/adjacency_list.hpp>
#include "LPowerLine.h"
#include "LIdentifier.h"


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
	std::pair<int, int> localCityPosition = std::make_pair(-1, -1);
	std::pair<int, int> remoteCityPosition = std::make_pair(-1, -1);
	std::pair<int, int> transformerStationPosition = std::make_pair(-1, -1);

	/** @brief Stores every unused coordinates. Is empty after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> unusedCoordinates;
	/** @brief Stores every used coordinate. Is full after correct initialization */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> usedCoordinates;
	/** @brief Stores the 1D coordinates for each pair of buildings which are connected */
	std::unordered_set<std::pair<int, int>, LPlayingFieldHasher> connectedBuildings;

	std::vector<LField::FieldType> fieldTypes;
	std::vector<LField::FieldLevel> fieldLevels;

	bool isLocalOperation = true;

private:
	template<typename T>
	struct placeBuildingHelper
	{
		LPlayingField* playingField;
		explicit placeBuildingHelper(LPlayingField* playingField)
			: playingField(playingField) {}

		template<typename... Args>
		bool operator()(const int x, const int y, const Args... arguments)
		{
			return playingField->getField(x, y)->setBuilding<T>(x, y, arguments...);
		}
	};

	template<>
	struct placeBuildingHelper<LPowerLine>
	{
		LPlayingField* playingField;
		explicit placeBuildingHelper(LPlayingField* playingField)
			: playingField(playingField)
		{}

		template<typename... Args>
		bool operator()(const int x, const int y, const Args... arguments)
		{
			int orientation = playingField->linkPowerlines(x, y);
			return playingField->getField(x, y)->setBuilding<LPowerLine>(x, y, orientation, arguments...);
		}
	};

	void createFields();
	void sendFieldInformation(const int x, const int y); //helper method
	bool checkIndex(const int x, const int y);
	int convertIndex(const std::pair<int, int>& coordinates);
	int convertIndex(const int x, const int y);
	std::pair<int, int> convertIndex(const int idx);
	void calculateEnergyValueCity();
	void addBuildingToGraph(const int x, const int y, const int orientation);
	void printGraph();

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

public:
	explicit LPlayingField(LMaster* lMaster);
	~LPlayingField();

	// returns true if building could be placed, else false (building not allowed or building already placed)
	template<typename T, typename... Args>
	bool placeBuilding(const int x, const int y, const int playerId, const Args... arguments)
	{
		//Seems to be the only possibility to restrict the template type. Performs compile time checks and produces compile errors, if the type is wrong
		static_assert(std::is_base_of<ILBuilding, T>::value, "Wrong type. The type T needs to be a derived class from ILBuilding");	
		
		//Check costs
		if (playerId == LPlayer::Local && lMaster->getPlayer(LPlayer::Local)->getMoney() < T::cost)
		{
			vPlayingField->messageBuildingFailed(std::string("Kraftwerk ") + getClassName(T) + std::string(" kann nicht gebaut werden, da nur ") + std::to_string(lMaster->getPlayer(LPlayer::Local)->getMoney()) + std::string(" EUR zur Verfügung stehen, es werden jedoch ") + std::to_string(T::cost) + std::string(" benötigt."));
			return false;
		}

		if (placeBuildingHelper<T>(this)(x, y, arguments...)) {

			if (playerId == LPlayer::Local)
			{
				addBuildingToGraph(x, y, getField(x, y)->getBuilding()->getOrientation());

				//subtract money only if the local player placed the building
				lMaster->getPlayer(LPlayer::Local)->subtractMoney(T::cost);

				if (localCityPosition.first > -1 && localCityPosition.second > -1)
				{
					calculateEnergyValueCity();
				}
			}

			//assign player id
			getField(x, y)->getBuilding()->setPlayerId(playerId);


			//-----network-----

			if (!isLocalOperation)
			{
				int objectIdentifier = 0;

					std::string buildingType = getClassName(T);

					if (buildingType == "LCoalPowerPlant")
					{
						objectIdentifier = LIdentifier::LCoalPowerPlant;
					}
					else if (buildingType == "LHydroelectricPowerPlant")
					{
						objectIdentifier = LIdentifier::LHydroelectricPowerPlant;
					}
					else if (buildingType == "LNuclearPowerPlant")
					{
						objectIdentifier = LIdentifier::LNuclearPowerPlant;
					}
					else if (buildingType == "LOilRefinery")
					{
						objectIdentifier = LIdentifier::LOilRefinery;
					}
					else if (buildingType == "LSolarPowerPlant")
					{
						objectIdentifier = LIdentifier::LSolarPowerPlant;
					}
					else if (buildingType == "LWindmillPowerPlant")
					{
						objectIdentifier = LIdentifier::LWindmillPowerPlant;
					}
					else if (buildingType == "LCity")
					{
						objectIdentifier = LIdentifier::LCity;
					}
					else if (buildingType == "LPowerLine")
					{
						objectIdentifier = LIdentifier::LPowerLine;
					}
					else if (buildingType == "LTransformerStation")
					{
						objectIdentifier = LIdentifier::LTransformerStation;
					}
				
				lMaster->sendSetObject(objectIdentifier, x, y, std::to_string(playerId));
			}

			//-----network-----

			DEBUG_OUTPUT("Marketplace connected = " << isTransformstationConnected());

			return true;
		}
		else
		{
			return false;
		}
	}

	std::unordered_map<ILBuilding::Orientation, LField* >getFieldNeighbors(const int x, const int y);

	int linkPowerlines(const int x, const int y);

	void beginRemoteOperation();
	void endRemoteOperation();

	bool checkConnectionBuildings(const std::pair<int, int>& first, const std::pair<int, int>& second);
	bool isTransformstationConnected();

	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LField* getField(const int x, const int y);
	int getFieldLength();
	LMaster* getLMaster();
	IVPlayingField* getVPlayingField();

	const std::pair<int, int>& getCityPosition() const
	{
		return localCityPosition;
	}

	LCity* getLocalCity()
	{
		return CASTD<LCity*>(getField(localCityPosition.first, localCityPosition.second)->getBuilding());
	}
};


NAMESPACE_LOGIC_E
