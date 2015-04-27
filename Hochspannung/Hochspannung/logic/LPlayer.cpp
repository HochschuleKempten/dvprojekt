#include "LPlayer.h"
#include "LMaster.h"
#include "IVMaster.h"

NAMESPACE_LOGIC_B


LPlayer::LPlayer(LMaster* lMaster)
	: lMaster(lMaster)
{
}

LPlayer::~LPlayer()
{
}

int LPlayer::getMoney() const
{
	return money;
}

void LPlayer::addMoney(int amount)
{
	money += amount;
}

void LPlayer::substractMoney(const int amount)
{
	money -= amount;
	lMaster->getVMaster()->updateMoney(money);
	ASSERT(money >= 0, "The player has not enough money");
}


NAMESPACE_LOGIC_E
