#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LWindmillPowerPlant :
	public ILPowerPlant
{
public:
	static const int id = 6;

	LWindmillPowerPlant(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LWindmillPowerPlant();

	int getID();
};

NAMESPACE_LOGIC_E