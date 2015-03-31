#pragma once

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
private:
	int costs;

public:
	ILBuilding(int costs) :
		costs(costs)
	{
	};

	virtual ~ILBuilding()
	{
	};

	int getCosts()
	{
		return costs;
	};

	//todo (L) implement this in the buildings that can be upgraded
	void upgrade()
	{
	};
};

