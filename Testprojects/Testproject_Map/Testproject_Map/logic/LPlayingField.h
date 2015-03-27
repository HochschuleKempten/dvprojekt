#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"

#define SIZE 1000

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	LMaster* lMaster;
	IVPlayingField* vField;
	LField * fieldArray;
	int fieldLength;

public:
	LPlayingField(LMaster* lMaster)
		: lMaster(lMaster), vField(lMaster->getVMaster()->getFactory()->createPlayingField(lMaster->getVMaster(), this))
	{
		fieldArray = new LField[SIZE*SIZE]; //dynamischer Aufbau des 2D Feldarrays als Aneinanderreihung
		this->fieldLength = SIZE;
		vField->init();
	}
 
	LPlayingField(const int length); //length = Kantenlänge des quadratischen Spielfeldes
	~LPlayingField();

	LField & getField(const int i, const int j);
};
