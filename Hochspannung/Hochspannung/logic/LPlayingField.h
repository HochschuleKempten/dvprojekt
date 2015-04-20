#pragma once
#include "LGeneral.h"
#include "Array2D.h"
#include "LField.h"
#include "IVPlayingField.h"
#include "LPlayer.h"
#include <boost/graph/adjacency_list.hpp>

NAMESPACE_LOGIC_B

class LMaster;
class LPowerLine;

class LPlayingField
{
private:
	const int fieldLength = 10; // MUSS durch 5 Teilbar sein!!!!! (@MB: Satzzeichen sind keine Rudeltiere :P) (@IP STFU!!!!! :p ) todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster = nullptr;
	std::shared_ptr<IVPlayingField> vPlayingField = nullptr;
	Array2D<LField> fieldArray;

	using Graph = boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS>;
	Graph powerLineGraph;
	bool plVertexConnected = false;
	std::pair<int, int> cityPosition = std::make_pair(-1, -1);
	std::vector<std::pair<int, int>> usedCoordinates;

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
		if (lMaster->getPlayer()->getMoney() < T::cost) {
			vPlayingField->messageBuildingFailed(std::string("Kraftwerk ") + getClassName(T) + std::string(" kann nicht gebaut werden, da nur ") + std::to_string(lMaster->getPlayer()->getMoney()) + std::string(" EUR zur Verfügung stehen, es werden jedoch ") + std::to_string(T::cost) + std::string(" benötigt."));
			return false;
		}

		if (getField(x, y)->setBuilding<T>(x, y, arguments...)) {
			//TODO (L) No method like addBuildingToGraph possible? - (IP) done
			LPowerLine* powerLine = dynamic_cast<LPowerLine*>(getField(x, y)->getBuilding());
			if (powerLine != nullptr)
			{
				addPowerLineToGraph(x, y, powerLine->getPowerLineOrientation());
			}

			//todo (L) when?
			if (cityPosition.first > -1 && cityPosition.second > -1)
			{
				calculateEnergyValueCity();
			}

			lMaster->getPlayer()->substractMoney(T::cost);

			return true;
		}
		else {
			return false;
		}
	}
	
	
	int getFieldLength();
	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LMaster* getLMaster();
	IVPlayingField* getVPlayingField();

	void setVertexConnected(const bool b);
private:
	void createFields();
	//void generatePowerLineGraph();
	bool checkIndex(const int x, const int y);
	int convertIndex(const int x, const int y);
	bool powerlinesConnected(const int start, const int destination);
	void calculateEnergyValueCity();
	std::vector<int> getConnectedPowerLines(const int x, const int y);
	void addPowerLineToGraph(const int x, const int y, const int orientation);
	
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
	 * @return coordinate pair (x,y)
	 */
	std::pair<int, int> retrieveFreeCoordinates(const int x, const int y);
};

NAMESPACE_LOGIC_E
