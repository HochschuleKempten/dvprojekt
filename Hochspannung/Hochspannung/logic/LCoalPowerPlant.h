#pragma once

#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LCoalPowerPlant : public ILPowerPlant
{
public:
	LCoalPowerPlant(LField* lField, const int x, const int y, const int playerId);
	~LCoalPowerPlant();

	int getEnergyValue() override;

	LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LCoalPowerPlant;
	};

};


NAMESPACE_LOGIC_E
