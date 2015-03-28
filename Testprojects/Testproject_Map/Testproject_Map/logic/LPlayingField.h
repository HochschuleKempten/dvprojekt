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
	IVPlayingField* vPlayingField;
	LField * fieldArray;
	int fieldLength;

public:
	LPlayingField(LMaster* lMaster); 
	LPlayingField(const int length); //length = Kantenlänge des quadratischen Spielfeldes
	~LPlayingField();

	void initVPlayingField();
	LField * getField(const int i, const int j);
};
