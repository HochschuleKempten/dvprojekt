#pragma once
#include "ILBuilding.h"
class LPowerLine :
	public ILBuilding
{
public:
	LPowerLine(int costs);
	~LPowerLine();
};

