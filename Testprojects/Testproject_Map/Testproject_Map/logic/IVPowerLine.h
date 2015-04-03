#pragma once

#include "IView.h"

class LPowerLine;

class IVPowerLine : public IView
{
protected:
	LPowerLine* lPowerLine;

public:
	IVPowerLine(LPowerLine* lpowerLine)
		: lPowerLine(lpowerLine)
	{}
	virtual ~IVPowerLine()
	{}

	virtual void initPowerLine(const int x, const int y) = 0;
};
