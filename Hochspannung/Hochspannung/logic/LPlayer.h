#pragma once

#include "IVTickObserver.h"
#include "LGeneral.h"
#include "LSabotage.h"
#include "LBalanceLoader.h"


NAMESPACE_LOGIC_B

class ILPowerPlant;
class LPowerLine;
class LMaster;
class LCity;
class LRemoteOperation;

class LPlayer : public IVTickObserver
{
public:
	friend class LRemoteOperation;

	enum PlayerId
	{
		Local = 0x1,
		Remote = 0x2
	};

private:
	LMaster* lMaster = nullptr;
	int money = 0;
	int coolDownCounterRemove = 0;
	int coolDownCounterResource = 0;
	int coolDownCounterDeactivate = 0;
	int sabotageActs = LBalanceLoader::getSabotageActs();
	std::vector<ILPowerPlant*> powerPlants;
	std::vector<ILPowerPlant*> prevConnectedPowerPlants;
	std::vector<LPowerLine*> powerLines;
	LCity* city = nullptr;
	float timeLastCheck = 0;
	PlayerId playerId = Local;
	float ratioRegenerative = 0.0F;

private:
	void checkRegenerativeRatio();
	void checkDisposalValue(const ILBuilding* const building);
	bool sabotageRemove(ILBuilding* lBuilding);
	bool sabotageDeactivate(ILPowerPlant* lPowerPlant);	//TODO (L) Rename ILPowerPlant
	bool sabotageResource(ILPowerPlant* lPowerPlant);

public:
	LPlayer()
	{}
	explicit LPlayer(LMaster* lMaster, const PlayerId playerId);
	virtual ~LPlayer();
	virtual void tick(const float fTimeDelta) override;
	int getMoney() const;
	void addMoney(const int amount);
	void subtractMoney(const int amount);
	bool trySabotageAct(const LSabotage::LSabotage sabotageType);
	void addPowerPlant(ILPowerPlant* powerPlant);
	void removePowerPlant(const ILPowerPlant* const powerPlant);
	void addPowerLine(LPowerLine* powerLine);
	void removePowerLine(const LPowerLine* const powerLine);
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
