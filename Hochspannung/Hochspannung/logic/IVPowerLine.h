#pragma once

class LPowerLine;

class IVPowerLine
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
