#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{
public:
	LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LPowerLine();
};

