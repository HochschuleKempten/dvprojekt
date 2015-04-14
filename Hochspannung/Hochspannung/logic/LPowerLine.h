#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{	
public:
	static const int id = 4;

	// set orientation of the powerline with the bitwise operator (|) (example: PowerLineOrientation::NORTH|PowerLineOrientation::EAST)
	LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y, const int orientation);
	~LPowerLine();

	int getID();
};

