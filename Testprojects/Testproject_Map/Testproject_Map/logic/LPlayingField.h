#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"

#define SIZE 1000

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	LMaster* lMaster;
	IVPlayingField* vField;
	LField * fieldArray;
	int fieldLength;

public:
	LPlayingField(LMaster* lMaster); 
	LPlayingField(const int length); //length = Kantenl�nge des quadratischen Spielfeldes
	~LPlayingField();

	LField & getField(const int i, const int j);
};
