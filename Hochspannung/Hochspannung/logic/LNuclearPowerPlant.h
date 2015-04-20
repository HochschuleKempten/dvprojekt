#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LNuclearPowerPlant :
	public ILPowerPlant
{
public:
	LNuclearPowerPlant(LField* lField, const int x, const int y);
	~LNuclearPowerPlant();
};

NAMESPACE_LOGIC_E