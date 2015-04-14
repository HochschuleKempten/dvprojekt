#pragma once

#include "Array2D.h"
#include "LField.h"
#include <vector>
#include <boost\graph\graph_traits.hpp>
#include <boost\graph\adjacency_list.hpp>

using namespace boost;

class LMaster;
class IVPlayingField;

class LPlayingField
{
private:
	const int fieldLength = 10; // MUSS durch 5 Teilbar sein!!!!! (@MB: Satzzeichen sind keine Rudeltiere :P) (@IP STFU!!!!! :p ) todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	Array2D<LField> fieldArray;

	//bidirectional = directed graph with access to both out and in-edges
	using Graph = adjacency_list < vecS, vecS, bidirectionalS >;
	Graph* powerLineGraph;
	
	//todo (IP) this struct is used in generatePowerLineGraph()
	struct pl
	{
		bool placed = false;
		std::vector<pl*> connections;
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
};
