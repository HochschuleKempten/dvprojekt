#pragma once
#include "ILPowerPlant.h"

#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LHydroelectricPowerPlant :
	public ILPowerPlant
{
public:
	LHydroelectricPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LHydroelectricPowerPlant();
};

NAMESPACE_LOGIC_E