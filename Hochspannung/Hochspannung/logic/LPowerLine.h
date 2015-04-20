#pragma once
#include "ILPowerLine.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LPowerLine :
	public ILPowerLine
{	
public:
	// set orientation of the powerline with the bitwise operator (|) (example: PowerLineOrientation::NORTH|PowerLineOrientation::EAST)
	LPowerLine(LField* lField, const int x, const int y, const int orientation);
	~LPowerLine();
};

NAMESPACE_LOGIC_E