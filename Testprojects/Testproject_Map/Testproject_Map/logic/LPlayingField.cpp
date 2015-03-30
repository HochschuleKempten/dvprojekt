#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength)
{
	//todo: Aufruf hier ist zu kompliziert (zudem kennt LPlayingField jetzt IVFactory);
	//sinnvoller wäre es, wenn vmaster schon die create-Methoden kennt (VFactory komplett weglassen?) und sich dann selbst um die Erzeugung kümmert
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);
}

LPlayingField::~LPlayingField()
{
	delete vPlayingField;
}

void LPlayingField::initVPlayingField()
{
	vPlayingField->init();
}

LField* LPlayingField::getField(const int i, const int j)
{
	return &fieldArray[i][j];
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
}
