#pragma once
#include "ILBuilding.h"

class ILPowerPlant :
	public ILBuilding
{
protected:
	int energyValue;

public:
	ILPowerPlant(int costs, int energyValue) :
		ILBuilding(costs),
		energyValue(energyValue)
	{
	};

	virtual ~ILPowerPlant()
	{
	};

	int getEnergyValue()
	{
		return energyValue;
	};
};