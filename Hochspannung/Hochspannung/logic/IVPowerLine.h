#pragma once

#include <memory>

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

	virtual void initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y) = 0;
};
