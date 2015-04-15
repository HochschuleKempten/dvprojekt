#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LSolarPowerPlant :
	public ILPowerPlant
{
public:
	LSolarPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LSolarPowerPlant();
};

NAMESPACE_LOGIC_E