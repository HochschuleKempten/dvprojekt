#pragma once
#include "ILPowerLine.h"

class LPowerLine :
	public ILPowerLine
{
public:
	LPowerLine(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y);
	~LPowerLine();
};

