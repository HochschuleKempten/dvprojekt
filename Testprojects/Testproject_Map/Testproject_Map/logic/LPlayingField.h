#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"
#include "Array2D.h"
#include "LCoalPowerPlant.h"
#include "IVPowerPlant.h"

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	const int fieldLength = 3; //todo temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	Array2D<LField> fieldArray;

public:
	LPlayingField(LMaster* lMaster);  
	~LPlayingField();

	void initVPlayingField();
	LField* getField(const int x, const int y);
	// returns true if building could be placed, else false (building not allowed or building already placed)
	bool placeBuilding(const int x, const int y); //todo(IP) add parameter that specifies the building which has to be placed
	int getFieldLength();
};
