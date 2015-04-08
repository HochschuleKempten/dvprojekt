#pragma once

class ILPowerPlant;

class IVPowerPlant
{
protected:
	ILPowerPlant* lPlant;

public:
	IVPowerPlant(ILPowerPlant* lPlant)
		: lPlant(lPlant)
	{}
	virtual ~IVPowerPlant()
	{}

	virtual void initPowerPlant(const int x, const int y) = 0;
};
