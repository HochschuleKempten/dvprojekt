#pragma once
#include "LField.h"

class LPlayingField
{
private:
	LField * fieldArray;

public:
	LPlayingField(int length); //length = Kantenlšnge des quadratischen Spielfeldes
	~LPlayingField();
};

