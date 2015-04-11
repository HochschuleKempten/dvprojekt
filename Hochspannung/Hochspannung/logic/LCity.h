#pragma once
class LCity
{ //todo (IP)  create this
private:
	int energy = 0;

public:
	LCity();
	~LCity();

	void addEnergy(const int energy);
	void removeEnergy(const int energy);
	int getEnergy();
};

