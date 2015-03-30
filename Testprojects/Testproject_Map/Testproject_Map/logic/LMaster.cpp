#include "LMaster.h"
#include "LPlayingField.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster)
{
}

LMaster::~LMaster()
{
	delete playingField;
}

void LMaster::startNewGame()
{
	playingField = new LPlayingField(this);
	playingField->initVPlayingField();
}
