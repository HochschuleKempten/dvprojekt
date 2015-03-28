#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster),
	vField(lMaster->getVMaster()->getFactory()->createPlayingField(this))
{
	fieldArray = new LField[SIZE*SIZE]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
	this->fieldLength = SIZE;
	vField->init();
}

LPlayingField::LPlayingField(const int length)
{
	fieldArray = new LField[length*length]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
	this->fieldLength = length;
}


LPlayingField::~LPlayingField()
{
	delete[] fieldArray;
	delete vField;
}

LField & LPlayingField::getField(int i, int j)
{
	return fieldArray[i*fieldLength + j];
}
