#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster)
{
	fieldArray = new LField[fieldLength*fieldLength]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
	
	//todo: Aufruf hier ist zu kompliziert (zudem kennt LPlayingField jetzt IVFactory);
	//sinnvoller wäre es, wenn vmaster schon die create-Methoden kennt (VFactory komplett weglassen?) und sich dann selbst um die Erzeugung kümmert
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
