#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength)
{
	//todo (L) Aufruf hier ist zu kompliziert (zudem kennt LPlayingField jetzt IVFactory);
	//sinnvoller wäre es, wenn vmaster schon die create-Methoden kennt (VFactory komplett weglassen?) und sich dann selbst um die Erzeugung kümmert
	vPlayingField = this->lMaster->getVMaster()->getFactory()->createPlayingField(this);
}

LPlayingField::~LPlayingField()
{
	delete vPlayingField;
}

void LPlayingField::initVPlayingField()
{
	vPlayingField->initPlayingField();
}

LField* LPlayingField::getField(const int x, const int y)
{
	return &fieldArray[x][y];
}

bool LPlayingField::placeBuilding(const int x, const int y)
{
	LField * selectedField = &fieldArray[x][y];

	if (selectedField->isPlacingAllowed())
	{
		//todo (IP) just for testing
		LCoalPowerPlant* tempPlant = new LCoalPowerPlant(100, 20);
		selectedField->setBuilding(tempPlant);

		//todo (IP) LCoalPowerPlant should create it and hold the pointer to it
		IVPowerPlant * vPowerPlant = this->lMaster->getVMaster()->getFactory()->createPowerPlant(tempPlant);
		vPowerPlant->initPowerPlant(x, y);

		return true;
	}

	return false;
}

int LPlayingField::getFieldLength()
{
	return fieldLength;
}
