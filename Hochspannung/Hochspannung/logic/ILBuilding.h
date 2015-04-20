#pragma once
#include "LGeneral.h"

NAMESPACE_LOGIC_B


class LField;

class ILBuilding
{
	//todo (L) Später max. Ausbaustufe und aktuelle, Spielerzuweisung
protected:
	LField* lField;

public:
	ILBuilding(LField* lField)
		: lField(lField)
	{}

	virtual ~ILBuilding()
	{}

	//todo (L) implement this in the buildings that can be upgraded
	virtual void upgrade() 
	{}

	static const int cost = 10;
};


NAMESPACE_LOGIC_E
