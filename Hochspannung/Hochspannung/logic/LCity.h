#pragma once
#include "ILBuilding.h"
#include "IVTickObserver.h"

NAMESPACE_LOGIC_B


class IVCity;

class LCity : public ILBuilding, public IVTickObserver
{
private:
	int populationIncrease = 1;	//x peoples per second
	int consumptionCitizen = 1; //x watt per citizen
	int populationTotal = 100;
	int energy = 0;
	std::shared_ptr<IVCity> vCity;

public:
	LCity(LField* lField, const int x, const int y);
	~LCity();

	virtual void tick(const float fTimeDelta) override;

	void setEnergy(const int energy);
	int getEnergy() const;
	void setPopulationTotal(const int populationTotal);
	int getEnergySurplus();

	static const int cost = 0;
};


NAMESPACE_LOGIC_E
