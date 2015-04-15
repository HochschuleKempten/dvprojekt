#pragma once
#include "ILPowerPlant.h"

#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LCoalPowerPlant : public ILPowerPlant
{
public:
	LCoalPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LCoalPowerPlant();
};

NAMESPACE_LOGIC_E