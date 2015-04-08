#pragma once
#include <memory>

class LField;

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	int costs;
	LField* lField;

public:
	ILBuilding(const int costs, LField* lField)
		:costs(costs),
		lField(lField)
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

