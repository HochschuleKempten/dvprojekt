#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LNuclearPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 2;

	LNuclearPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LNuclearPowerPlant();

	int getID();
};

NAMESPACE_LOGIC_E