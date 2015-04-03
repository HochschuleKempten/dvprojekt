#include "LMaster.h"
#include "LPlayingField.h"
#include "LUI.h"
#include "IVMaster.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(lPlayer),
	lUi(this)
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
