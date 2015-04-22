#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer
{
	NON_COPYABLE(LPlayer);

public:
	enum PlayerNumber
	{
		PlayerOne = 0,
		PlayerTwo = 2
	};

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
