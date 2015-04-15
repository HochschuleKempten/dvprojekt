#pragma once
#include "ILBuilding.h"
#include <memory>

NAMESPACE_LOGIC_B


class IVCity;

class LCity : public ILBuilding
{
private:
	int energy = 0;
	std::shared_ptr<IVCity> vCity;

public:
	LCity(LField* lField, const int x, const int y);
	~LCity();

	void addEnergy(const int energy);
	void removeEnergy(const int energy);
	int getEnergy();
};

NAMESPACE_LOGIC_E
