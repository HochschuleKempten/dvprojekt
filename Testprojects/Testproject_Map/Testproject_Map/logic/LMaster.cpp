#include "LMaster.h"
#include "LPlayingField.h"

LMaster::LMaster(IVMaster* master)
	: master(master), playingField(new LPlayingField(SIZE))
{
}

LMaster::~LMaster()
{
	delete playingField;
}
