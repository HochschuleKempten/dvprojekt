#include "LPlayingField.h"


LPlayingField::LPlayingField(int length)
{
	fieldArray = new LField[length*length]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
	this->fieldLength = length;
}


LPlayingField::~LPlayingField()
{
	delete[] fieldArray;
}

LField & LPlayingField::getField(int i, int j)
{
	return fieldArray[i*fieldLength + j];
}
