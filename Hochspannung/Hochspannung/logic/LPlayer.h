#pragma once
#include "IVTickObserver.h"
#include "LGeneral.h"
#include "LSabotage.h"

NAMESPACE_LOGIC_B


class LMaster;

class LPlayer : public IVTickObserver
{
public:
	enum PlayerId
	{
		Local = 0x1,
		Remote = 0x2
	};

private:
	int money = 5700;
	LMaster* lMaster;
	int coolDownCounterPowerLine = 0;
	int coolDownCounterResource = 0;
	int coolDownCounterPowerPlant = 0;

public:
	LPlayer(LMaster* lMaster);
	virtual ~LPlayer();
	virtual void tick(const float fTimeDelta) override;
	int getMoney() const;
	void addMoney(const int amount);
	void subtractMoney(const int amount);
	bool trySabotageAct(const LSabotage::LSabotage sabotageType);
	int sabotageActs = -1;
};


NAMESPACE_LOGIC_E
