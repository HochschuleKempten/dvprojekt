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

void LPlayer::addMoney(const int amount)
{
	money += amount;
	lMaster->getVMaster()->updateMoney(money);
}

void LPlayer::subtractMoney(const int amount)
{
	money -= amount;
	lMaster->getVMaster()->updateMoney(money);
	ASSERT(money >= 0, "The player has not enough money");
}

bool LPlayer::trySabotageAct()
{
	if (sabotageActs > 0)
	{
		sabotageActs--;
		return true;
	}

	else return false;
	DEBUG_OUTPUT("No sabotage Acts left! ");
	

}

NAMESPACE_LOGIC_E
