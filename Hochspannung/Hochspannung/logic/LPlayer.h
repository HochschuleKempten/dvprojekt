#pragma once
#include "LGeneral.h"
#include "LUtility.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer
{
private:
	int money = 2700;
	LMaster& lMaster;

public:
	LPlayer(LMaster& lMaster);
	~LPlayer();
	int getMoney() const;
	void substractMoney(const int amount);
};


NAMESPACE_LOGIC_E
