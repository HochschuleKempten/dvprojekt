#pragma once
#include "ILBuilding.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class IVPowerLine;
class LPlayingField;

class ILPowerLine : public ILBuilding
{
protected:
	int orientation;
	std::shared_ptr<IVPowerLine> vPowerLine;

public:
	ILPowerLine(LField* lField, const int orientation, const int playerId, const std::shared_ptr<IVPowerLine>& vPowerLine)
		: ILBuilding(lField, playerId),
		orientation(orientation),
		vPowerLine(vPowerLine)
	{}

	virtual ~ILPowerLine() override
	{}

	virtual int getOrientation() const override
	{
		return orientation;
	}

	int getPowerLineOrientation()
	{
		return orientation;
	}

};


NAMESPACE_LOGIC_E
