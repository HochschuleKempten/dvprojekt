#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LNuclearPowerPlant :
	public ILPowerPlant
{

public:
	LNuclearPowerPlant(LField* lField, const int x, const int y, const int playerId);
	~LNuclearPowerPlant();

	int getEnergyValue() override;

	LIdentifier::LIdentifier getIdentifier() const override
	{
		return LIdentifier::LNuclearPowerPlant;
	};
};

NAMESPACE_LOGIC_E