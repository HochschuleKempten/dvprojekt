#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LPlayer
{
private:
	int money = 0;

public:
	LPlayer();
	~LPlayer();
	int getMoney();
};

NAMESPACE_LOGIC_E
