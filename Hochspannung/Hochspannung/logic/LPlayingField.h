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
	const int fieldLength = 6; //todo (IP) temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	Array2D<LField> fieldArray; //todo (IP) beim Erzeugen this übergeben

public:
	LPlayingField(LMaster* lMaster);
	~LPlayingField();

	void initVPlayingField();
	LField* getField(const int x, const int y);

	// returns true if building could be placed, else false (building not allowed or building already placed)
	template<typename T>
	bool placeBuilding(const int x, const int y)
	{
		//Seems to be the only possibility to restrict the template type. Performs compile time checks and produces compile errors, if the type is wrong
		static_assert(std::is_base_of<ILBuilding, T>::value, "Wrong type. The type T needs to be a derived class from ILBuilding");

		return getField(x, y)->setBuilding<T>(x, y);
	}
	
	int getFieldLength();
	void removeBuilding(const int x, const int y);
	void upgradeBuilding(const int x, const int y);
	LMaster* getLMaster();
};
