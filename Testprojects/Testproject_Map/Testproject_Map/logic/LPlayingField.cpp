#include "LPlayingField.h"

LPlayingField::LPlayingField()
{
}

LPlayingField::LPlayingField(const int length)
{
	fieldArray = new LField[length*length]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
}


LPlayingField::~LPlayingField()
{
	delete[] fieldArray;
}
