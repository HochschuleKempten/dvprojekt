#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LSolarPowerPlant :
	public ILPowerPlant
{

public:
	LSolarPowerPlant(LField* lField, const int x, const int y, const int playerId);
	~LSolarPowerPlant();
	
	LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LSolarPowerPlant;
	};
};

NAMESPACE_LOGIC_E