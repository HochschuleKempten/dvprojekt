#include "LMaster.h"
#include "LPlayingField.h"
#include "IVMaster.h"
#include "LPlayer.h"

NAMESPACE_LOGIC_B

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(new LPlayer())
{
	vMaster->registerObserver(this);
}

LMaster::~LMaster()
{
	delete lPlayingField;
}

void LMaster::startNewGame()
{
	lPlayingField = new LPlayingField(this);
	lPlayingField->initVPlayingField();
}

void LMaster::tick(const float fTimeDelta)
{

}

LPlayingField* LMaster::getLPlayingField()
{
	return lPlayingField;
}

IVMaster* LMaster::getVMaster()
{
	return vMaster;
}

LPlayer* LMaster::getPlayer()
{
	return lPlayer;
}

NAMESPACE_LOGIC_E