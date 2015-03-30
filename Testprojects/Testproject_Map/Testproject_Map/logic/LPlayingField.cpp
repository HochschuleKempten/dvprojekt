#include "LPlayingField.h"

LPlayingField::LPlayingField(LMaster* lMaster)
	: lMaster(lMaster), fieldArray(fieldLength, fieldLength)
{
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
