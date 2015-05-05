#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer
{
public:
	enum PlayerId
	{
		Local = 0x1,
		External = 0x2
	};

private:
	int money = 5700;
	LMaster* lMaster;

public:
	LPlayer(LMaster* lMaster);
	~LPlayer();
	int getMoney() const;
	void addMoney(const int amount);
	void subtractMoney(const int amount);
};


NAMESPACE_LOGIC_E
