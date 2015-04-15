#pragma once
#include "ILBuilding.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class IVPowerPlant;

class ILPowerPlant : public ILBuilding
{
protected:
	int energyValue;
	std::shared_ptr<IVPowerPlant> vPowerPlant;

public:
	inline ILPowerPlant(const int costs, const int energyValue, LField* lField, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(costs, lField),
		vPowerPlant(vPowerPlant),
		energyValue(energyValue)
	{};

	inline virtual ~ILPowerPlant()
	{
	};

	inline int getEnergyValue() const
	{
		return energyValue;
	};
};

NAMESPACE_LOGIC_E