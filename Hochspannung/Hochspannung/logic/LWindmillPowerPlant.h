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
	
	LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LWindmillPowerPlant;
	};
};

NAMESPACE_LOGIC_E