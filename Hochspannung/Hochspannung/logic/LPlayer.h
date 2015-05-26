#pragma once

#include "IVTickObserver.h"
#include "LGeneral.h"
#include "LSabotage.h"


NAMESPACE_LOGIC_B

class ILPowerPlant;
class LMaster;
class LCity;

class LPlayer : public IVTickObserver
{
public:
	enum PlayerId
	{
		Local = 0x1,
		Remote = 0x2
	};

private:
	LMaster* lMaster = nullptr;
	int money = 0;
	int coolDownCounterPowerLine = 0;
	int coolDownCounterResource = 0;
	int coolDownCounterPowerPlant = 0;
	int sabotageActs = -1;
	std::vector<ILPowerPlant*> powerPlants;
	LCity* city = nullptr;

public:
	LPlayer()
	{}
	explicit LPlayer(LMaster* lMaster);
	virtual ~LPlayer();
	virtual void tick(const float fTimeDelta) override;
	int getMoney() const;
	void addMoney(const int amount);
	void subtractMoney(const int amount);
	bool trySabotageAct(const LSabotage::LSabotage sabotageType);
	void addPowerPlant(ILPowerPlant* powerPlant);
	void checkPowerPlants();
	LCity* getCity() const
	{
		return city;
	}
	void setCity(LCity* lCity)
	{
		city = lCity;
	}
};


NAMESPACE_LOGIC_E
