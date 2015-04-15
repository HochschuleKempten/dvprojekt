#pragma once
#include <memory>
#include "LGeneral.h"

NAMESPACE_LOGIC_B

class LField;

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	static const int costs = 10;
	LField* lField;

public:
	ILBuilding(LField* lField)
		: lField(lField)
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
	virtual void upgrade() 
	{
	};
};

NAMESPACE_LOGIC_E