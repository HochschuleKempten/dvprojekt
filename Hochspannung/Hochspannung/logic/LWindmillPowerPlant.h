#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LWindmillPowerPlant();
};

NAMESPACE_LOGIC_E