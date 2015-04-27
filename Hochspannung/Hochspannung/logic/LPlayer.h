#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer
{
public:
	enum PlayerNumber
	{
		PlayerOne = 0,
		PlayerTwo = 2
	};

private:
	int money = 5700;
	LMaster* lMaster;

public:
	LPlayer(LMaster* lMaster);
	~LPlayer();
	int getMoney() const;
	void addMoney(const int amount);
	void substractMoney(const int amount);
};


NAMESPACE_LOGIC_E
