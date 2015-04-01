#include "LMaster.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(lPlayer)
{
}


LMaster::~LMaster()
{
	delete lPlayingField;
}

IVMaster* LMaster::getVMaster()
{
	return vMaster;
}

LPlayingField * LMaster::getLPlayingField()
{
	return lPlayingField;
}

void LMaster::startNewGame()
{
	lPlayingField = new LPlayingField(this);
	lPlayingField->initVPlayingField();
}

LPlayer* LMaster::getPlayer()
{
	return lPlayer;
}
