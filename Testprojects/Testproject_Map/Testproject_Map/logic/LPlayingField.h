#pragma once
#include "LField.h"

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{
private:
	LField * fieldArray;
	int fieldLength;

public:
	LPlayingField(int length); //length = Kantenl�nge des quadratischen Spielfeldes
	~LPlayingField();

	LField & getField(int i, int j);
};

