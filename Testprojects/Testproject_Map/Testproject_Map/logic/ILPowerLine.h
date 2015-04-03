#pragma once
#include "ILBuilding.h"

class IVPowerLine;
class LPlayingField;

class ILPowerLine : public ILBuilding
{
protected:

	int energyValue;
	IVPowerLine* vPowerLine;

public:
	ILPowerLine(const int costs, const int energyValue, LPlayingField* lPlayingField, const int x, const int y, IVPowerLine* vPowerLine)
		: ILBuilding(costs, lPlayingField, x, y),
		vPowerLine(vPowerLine),
		energyValue(energyValue)
	{};

	virtual ~ILPowerLine()
	{
	};

	int getEnergyValue() const
	{
		return energyValue;
	};


};