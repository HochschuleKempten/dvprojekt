#pragma once
#include "ILBuilding.h"
#include "IVPowerPlant.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"

class ILPowerPlant:
	public ILBuilding
{
protected:
	int energyValue;
	IVPowerPlant* vPowerPlant;

public:
	ILPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y, IVPowerPlant* vPowerPlant)
		:ILBuilding(costs, lPlayingField, x, y),
		vPowerPlant(vPowerPlant),
		energyValue(energyValue)
	{};

	virtual ~ILPowerPlant()
	{
	};

	int getEnergyValue()
	{
		return energyValue;
	};
};