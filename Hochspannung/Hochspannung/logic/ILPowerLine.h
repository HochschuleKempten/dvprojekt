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
	ILPowerLine(const int costs, const int energyValue, LField* lField, IVPowerLine* vPowerLine)
		: ILBuilding(costs, lField),
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