#pragma once
#include "LField.h"

class LPlayingField
{
private:
	LField * fieldArray;

public:
	LPlayingField(int length); //length = Kantenl�nge des quadratischen Spielfeldes
	~LPlayingField();
};

