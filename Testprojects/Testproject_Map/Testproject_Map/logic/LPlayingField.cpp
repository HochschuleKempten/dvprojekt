#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster)
{
	fieldArray = new LField[fieldLength*fieldLength]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);
}

LPlayingField::~LPlayingField()
{
	delete[] fieldArray;
	delete vPlayingField;
}

void LPlayingField::initVPlayingField()
{
	vPlayingField->init();
}

LField * LPlayingField::getField(int i, int j)
{
	return &(fieldArray[i*fieldLength + j]);
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
}
