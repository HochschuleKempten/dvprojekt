#pragma once
#include "ILBuilding.h"

NAMESPACE_LOGIC_B

class IVPowerPlant;

class ILPowerPlant : public ILBuilding
{
protected:
	static const int energyValue = 100;
	std::shared_ptr<IVPowerPlant> vPowerPlant;

public:
	inline ILPowerPlant(LField* lField, std::shared_ptr<IVPowerPlant> vPowerPlant)
		: ILBuilding(lField),
		vPowerPlant(vPowerPlant)
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