#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{	
public:
	enum PowerLineOrientation
	{
		NORTH = 0x0,
		EAST = 0x1,
		SOUTH = 0x2,
		WEST = 0x4
	};

	static const int id = 4;

	LPowerLine(const int costs, const int energyValue, LField* lField, const int x, const int y, PowerLineOrientation orientation);
	~LPowerLine();

private:
	PowerLineOrientation orientation;
};

