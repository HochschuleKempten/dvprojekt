#pragma once
#include "ILBuilding.h"
#include "IVPowerPlant.h"
#include "LMaster.h"
#include "IVMaster.h"
#include "IVFactory.h"
#include "LPlayingField.h"

class ILPowerPlant:
	public ILBuilding
{
protected:
	int energyValue;
	IVPowerPlant* vPowerPlant;

public:
	ILPowerPlant(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y)
		:ILBuilding(costs, lPlayingField, x, y),
		energyValue(energyValue)
	{
		vPowerPlant = this->lPlayingField->getLMaster()->getVMaster()->getFactory()->createPowerPlant(this);
		vPowerPlant->initPowerPlant(x, y);
	};

	virtual ~ILPowerPlant()
	{
	};

	int getEnergyValue()
	{
		return energyValue;
	};
};