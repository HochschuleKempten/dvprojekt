#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	LWindmillPowerPlant(LField* lField, const int x, const int y);
	~LWindmillPowerPlant();

	static const int cost = 500;
};

NAMESPACE_LOGIC_E