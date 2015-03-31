#include "LMaster.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(lPlayer)
{
}


LMaster::~LMaster()
{
	delete playingField;
}

IVMaster* LMaster::getVMaster()
{
	return vMaster;
}

LPlayingField * LMaster::getLPlayingField()
{
	return playingField;
}

void LMaster::startNewGame()
{
	playingField = new LPlayingField(this);
	playingField->initVPlayingField();
}

LPlayer* LMaster::getPlayer()
{
	return lPlayer;
}
