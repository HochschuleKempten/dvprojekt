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

	LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LNuclearPowerPlant;
	};
};

NAMESPACE_LOGIC_E