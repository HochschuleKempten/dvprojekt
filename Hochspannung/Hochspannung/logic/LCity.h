#pragma once
#include "ILBuilding.h"
#include "IVTickObserver.h"
#include "LBalanceLoader.h"

NAMESPACE_LOGIC_B


class IVCity;

class LCity : public ILBuilding, public IVTickObserver
{
private:
	int populationTotal = LBalanceLoader::getStartPopulation();
	int energy = -1;
	std::shared_ptr<IVCity> vCity;

public:
	LCity(LField* lField, const int x, const int y, const int playerId);
	~LCity();

	virtual void tick(const float fTimeDelta) override;

	void setEnergy(const int energy);
	int getEnergy() const;
	void setPopulationTotal(const int populationTotal);
	int getEnergySurplus();

	virtual LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LCity;
	}
};


NAMESPACE_LOGIC_E
