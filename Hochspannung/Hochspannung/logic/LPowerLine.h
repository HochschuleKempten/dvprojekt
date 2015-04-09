#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{
public:
	const static int id = 4;

	LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y);
	~LPowerLine();
};

