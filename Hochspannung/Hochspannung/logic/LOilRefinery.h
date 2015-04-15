#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LOilRefinery :
	public ILPowerPlant
{
public:
	static const int id = 3;

	LOilRefinery(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LOilRefinery();

	int getID();
};

NAMESPACE_LOGIC_E