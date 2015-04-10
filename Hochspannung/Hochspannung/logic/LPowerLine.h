#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{	
public:
	static const int id = 4;

	LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y, PowerLineOrientation orientation);
	~LPowerLine();
};

