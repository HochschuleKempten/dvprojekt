#pragma once

class ILBuilding
{
	//todo (L) Sp�ter max. Ausbaustufe und aktuelle, Spielerzuweisung
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
};

