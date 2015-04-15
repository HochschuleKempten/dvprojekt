#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LOilRefinery :
	public ILPowerPlant
{
public:
	LOilRefinery(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LOilRefinery();
};

NAMESPACE_LOGIC_E