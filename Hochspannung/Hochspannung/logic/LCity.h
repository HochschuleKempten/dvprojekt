#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B
class IVCity;

class LCity
{ //todo (IP) create this
private:
	int energy = 0;
	IVCity* vCity = nullptr;

public:
	LCity();
	~LCity();

	void addEnergy(const int energy);
	void removeEnergy(const int energy);
	int getEnergy();
};

NAMESPACE_LOGIC_E