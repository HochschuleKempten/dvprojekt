#pragma once
#include "Array2D.h"
#include "LField.h"
#include "LCoalPowerPlant.h"
#include "LHydroelectricPowerPlant.h"

class LMaster;
class IVPlayingField;

class LPlayingField
{

private:
	const int fieldLength = 3; //todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	// (FL) Vorschlag: Groesse wird vom Spieler beim erstellen des Spiels angegebeben ueber Parameter wie Mapgroesse
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	Array2D<LField> fieldArray;

public:
	LPlayingField(LMaster* lMaster);
	~LPlayingField();

	void initVPlayingField();
	LField* getField(const int x, const int y);
	// returns true if building could be placed, else false (building not allowed or building already placed)

	template<typename T>
	void placeBuilding(const int x, const int y)
	{
		//todo (IP) just for testing, parameter needs to be added (which building has to be build?)
		//TODO (L) maybe it is better when the field creates the building, just do some checks here
		ILBuilding* tempPlant = new T(100, 20, this, x, y);
		getField(x, y)->setBuilding(tempPlant);
	}

	//todo (IP) add parameter that specifies the building which has to be placed
	int getFieldLength();
	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LMaster* getLMaster();
};
