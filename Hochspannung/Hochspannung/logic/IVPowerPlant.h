#pragma once

#include <memory>

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

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) = 0;
};
