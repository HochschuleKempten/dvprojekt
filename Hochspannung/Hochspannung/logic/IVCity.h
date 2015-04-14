#pragma once

#include <memory>

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
};
