#pragma once

class LPlayingField;

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	int costs;
	LPlayingField* lPlayingField;

public:
	ILBuilding(const int costs, LPlayingField* lPlayingField, const int x, const int y)
		:costs(costs),
		lPlayingField(lPlayingField)
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

