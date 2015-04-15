#pragma once
#include "ILBuilding.h"
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class IVPowerLine;
class LPlayingField;

class ILPowerLine : public ILBuilding
{
public:
	enum PowerLineOrientation
	{
		NORTH = 0x1,
		EAST = 0x2,
		SOUTH = 0x4,
		WEST = 0x8
	};

protected:
	int orientation;
	std::shared_ptr<IVPowerLine> vPowerLine;

public:
	ILPowerLine(const int orientation, LField* lField, const std::shared_ptr<IVPowerLine>& vPowerLine)
		: ILBuilding(lField),
		vPowerLine(vPowerLine),
		orientation(orientation)
	{};

	virtual ~ILPowerLine()
	{
	};

	int getPowerLineOrientation()
	{
		return orientation;
	};

};

NAMESPACE_LOGIC_E