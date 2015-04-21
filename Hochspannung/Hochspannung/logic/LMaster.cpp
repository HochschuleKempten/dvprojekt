#include "LMaster.h"
#include "LPlayingField.h"
#include "IVMaster.h"

NAMESPACE_LOGIC_B


LMaster::LMaster(IVMaster& vMaster)
: vMaster(vMaster), lPlayer(new LPlayer[2]{(*this), (*this)})
{
	vMaster.registerObserver(this);
}

LMaster::~LMaster()
{
	delete lPlayingField;
	delete [] lPlayer;
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

LPlayer* LMaster::getPlayer(const int idxPlayer)
{
	ASSERT(idxPlayer >= 0 && idxPlayer <= 1, "Wrong idx for player");
	return &lPlayer[idxPlayer];
}


NAMESPACE_LOGIC_E
