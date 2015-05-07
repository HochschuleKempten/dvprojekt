#pragma once
#include "ILPowerPlant.h"

NAMESPACE_LOGIC_B


class LHydroelectricPowerPlant :
	public ILPowerPlant
{

public:
	LHydroelectricPowerPlant(LField* lField, const int x, const int y, const int playerId);
	~LHydroelectricPowerPlant();

	LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LHydroelectricPowerPlant;
	};
};


NAMESPACE_LOGIC_E
