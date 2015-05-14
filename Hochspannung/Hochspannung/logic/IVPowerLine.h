#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LPowerLine;

class IVPowerLine
{
protected:
	LPowerLine* lPowerLine;

public:
	explicit IVPowerLine(LPowerLine* lpowerLine)
		: lPowerLine(lpowerLine)
	{}
	virtual ~IVPowerLine()
	{}

	virtual void initPowerLine(const std::shared_ptr<IVPowerLine>& objPtr, const int x, const int y, const int orientation) = 0;
	virtual void orientationChanged(const int orientation) = 0;
	virtual void sabotagePowerLineRemoved() = 0;
};

NAMESPACE_LOGIC_E
