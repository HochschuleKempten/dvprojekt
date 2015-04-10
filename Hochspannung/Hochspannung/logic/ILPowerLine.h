#pragma once
#include "ILBuilding.h"

class IVPowerLine;
class LPlayingField;

class ILPowerLine : public ILBuilding
{
public:
	enum PowerLineOrientation
	{
		NORTH = 0x0,
		EAST = 0x1,
		SOUTH = 0x2,
		WEST = 0x4
	};

protected:
	PowerLineOrientation orientation;
	int energyValue;
	std::shared_ptr<IVPowerLine> vPowerLine;

public:

	ILPowerLine(const int costs, const int energyValue, PowerLineOrientation orientation, LField* lField, IVPowerLine* vPowerLine)
		: ILBuilding(costs, lField),
		vPowerLine(vPowerLine),
		energyValue(energyValue),
		orientation(orientation)
	{};

	virtual ~ILPowerLine()
	{
	};

	int getEnergyValue() const
	{
		return energyValue;
	};

	PowerLineOrientation getPowerLineOrientation()
	{
		return orientation;
	}

};