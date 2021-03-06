#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LWindmillPowerPlant :
	public ILPowerPlant
{

public:
	LWindmillPowerPlant(LField* lField, const int x, const int y, const int playerId);
	~LWindmillPowerPlant();
	
	LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LWindmillPowerPlant;
	};
};

NAMESPACE_LOGIC_E