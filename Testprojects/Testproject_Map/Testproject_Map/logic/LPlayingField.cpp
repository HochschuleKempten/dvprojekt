#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster),
<<<<<<< HEAD
	vField(lMaster->getVMaster()->getFactory()->createPlayingField(lMaster->getVMaster(), this))//Copy des Pointer auf Master in Member
=======
	vField(lMaster->getVMaster()->getFactory()->createPlayingField(this))
>>>>>>> b3a8c5bc48b13a8dadb2f24fadfbcb0725634b0e
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
}

LField & LPlayingField::getField(int i, int j)
{
	return fieldArray[i*fieldLength + j];
}
