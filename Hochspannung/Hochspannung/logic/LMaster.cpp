#include "LMaster.h"
#include "LPlayingField.h"
#include "IVMaster.h"

NAMESPACE_LOGIC_B


LMaster::LMaster(IVMaster& vMaster)
: vMaster(vMaster), lPlayer{ (*this), (*this) }
{
	vMaster.registerObserver(this);
}

LMaster::~LMaster()
{
	delete lPlayingField;
}

void LMaster::startNewGame()
{
	if (lPlayingField == nullptr) {
		lPlayingField = new LPlayingField(this);
	}
}

void LMaster::gameLost()
{
	vMaster.gameOver();
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
	return &vMaster;
}

LPlayer* LMaster::getPlayers()
{
	return lPlayer;
}


NAMESPACE_LOGIC_E
