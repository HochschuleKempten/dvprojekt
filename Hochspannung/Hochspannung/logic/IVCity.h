#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LCity;

class IVCity
{
protected:
	LCity* lCity;

public:
	inline IVCity(LCity* lCity)
		: lCity(lCity)
	{}
	inline virtual ~IVCity()
	{}

	virtual void initCity(const std::shared_ptr<IVCity>& objPtr, const int x, const int y) = 0;
	virtual void updatePopulation(const int population) = 0;
	virtual void updateEnergy(const int energy) = 0;
};

NAMESPACE_LOGIC_E