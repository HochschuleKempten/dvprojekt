#pragma once
#include "ILPowerPlant.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LOilRefinery :
	public ILPowerPlant
{

public:
	LOilRefinery(LField* lField, const int x, const int y, const int playerId);
	~LOilRefinery();

	LIdentifier::LIdentifier getIdentifier() override
	{
		return LIdentifier::LOilRefinery;
	};
};

NAMESPACE_LOGIC_E