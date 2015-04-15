#pragma once
#include "ILPowerPlant.h"

NAMESPACE_LOGIC_B


class LHydroelectricPowerPlant :
	public ILPowerPlant
{
public:
	LHydroelectricPowerPlant(LField* lField, const int x, const int y);
	~LHydroelectricPowerPlant();
};


NAMESPACE_LOGIC_E
