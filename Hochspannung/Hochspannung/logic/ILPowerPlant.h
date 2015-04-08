#pragma once
#include "ILBuilding.h"

class IVPowerPlant;

class ILPowerPlant : public ILBuilding
{
protected:
	int energyValue;
	std::shared_ptr<IVPowerPlant> vPowerPlant;

public:
	ILPowerPlant(const int costs, const int energyValue, LField* lField, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(costs, lField),
		vPowerPlant(vPowerPlant),
		energyValue(energyValue)
	{};

	virtual ~ILPowerPlant()
	{
	};

	int getEnergyValue() const
	{
		return energyValue;
	};
};