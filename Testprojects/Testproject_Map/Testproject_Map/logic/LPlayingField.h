#pragma once
#include "LField.h"
//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{
private:
	LField * fieldArray;

public:
	LPlayingField(int length); //length = Kantenlšnge des quadratischen Spielfeldes
	~LPlayingField();
};

