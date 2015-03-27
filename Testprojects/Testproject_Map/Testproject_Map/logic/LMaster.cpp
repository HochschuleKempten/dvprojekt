#include "LMaster.h"
#include "LPlayingField.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster), playingField(new LPlayingField(this))
{
}

LMaster::~LMaster()
{
	delete playingField;
}
