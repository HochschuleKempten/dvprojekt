#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class ILPowerPlant;

class IVPowerPlant
{
protected:
	ILPowerPlant* lPlant;

public:
	explicit IVPowerPlant(ILPowerPlant* lPlant)
		: lPlant(lPlant)
	{}
	virtual ~IVPowerPlant()
	{}

	virtual void initPowerPlant(const std::shared_ptr<IVPowerPlant>& objPtr, const int x, const int y) = 0;
	virtual void switchedOn() = 0;
	virtual void switchedOff() = 0;
	virtual void sabotageRessourcesReduced() = 0;
	virtual void sabotagePowerPlantSwitchedOff(const int seconds) = 0;
	virtual void sabotagePowerPlantSwitchedOn() = 0;

};

NAMESPACE_LOGIC_E
