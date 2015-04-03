#include "LMaster.h"
#include "LPlayingField.h"
#include "LUI.h"

LMaster::LMaster(IVMaster* vMaster)
	: vMaster(vMaster),
	lPlayer(lPlayer)
{}

LMaster::~LMaster()
{
	delete lPlayingField;
}

void LMaster::startNewGame()
{
	lPlayingField = new LPlayingField(this);
	lPlayingField->initVPlayingField();

	lUi = new LUI(this);
	lUi->initVUi();
}

void LMaster::tick(float fTime, float fTimeDelta)
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
