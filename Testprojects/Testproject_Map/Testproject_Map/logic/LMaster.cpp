#include "LMaster.h"


LMaster::LMaster()
{
	playingField = new LPlayingField(SIZE);
}


LMaster::~LMaster()
{
	delete playingField;
}
