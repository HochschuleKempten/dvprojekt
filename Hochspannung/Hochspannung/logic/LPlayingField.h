#pragma once
#include "LGeneral.h"
#include "Array2D.h"
#include "LField.h"
#include <vector>
#include <boost\graph\graph_traits.hpp>
#include <boost\graph\adjacency_list.hpp>

NAMESPACE_LOGIC_B

class LMaster;
class IVPlayingField;

class LPlayingField
{
private:

	//todo (IP) initialize members
	//todo (IP) use namespace
	const int fieldLength = 10; // MUSS durch 5 Teilbar sein!!!!! (@MB: Satzzeichen sind keine Rudeltiere :P) (@IP STFU!!!!! :p ) todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster = nullptr;
	IVPlayingField* vPlayingField = nullptr;
	Array2D<LField> fieldArray;

	using Graph = boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS>;
	Graph powerLineGraph;
	
	//todo (IP) this struct is used in generatePowerLineGraph()
	struct pLine
	{
		bool placed = false;
		std::vector<pLine*> connections;
		int x, y;
	};

private:
	void createFields();

public:
	LPlayingField(LMaster* lMaster);
	~LPlayingField();

	void initVPlayingField();
	LField* getField(const int x, const int y);

	// returns true if building could be placed, else false (building not allowed or building already placed)
	template<typename T, typename... Args>
	bool placeBuilding(const int x, const int y, const Args... arguments)
	{
		//Seems to be the only possibility to restrict the template type. Performs compile time checks and produces compile errors, if the type is wrong
		static_assert(std::is_base_of<ILBuilding, T>::value, "Wrong type. The type T needs to be a derived class from ILBuilding");	

		//return getField(x, y)->setBuilding<T>(x, y, arguments...);

		bool ret = getField(x, y)->setBuilding<T>(x, y, arguments...);
		//generateTree();

		return ret;
	}
	
	
	int getFieldLength();
	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LMaster* getLMaster();

private:
	void generatePowerLineGraph();
	bool checkIndex(const int x, const int y);
	int convertIndex(const int x, const int y);
};

NAMESPACE_LOGIC_E