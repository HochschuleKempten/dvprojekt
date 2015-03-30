#pragma once
#include "ILBuilding.h"
class LField
{
private:
	ILBuilding* building;
	bool placingAllowed;

public:
	// initializes this field with isPlacingAllowed = true!
	LField();
	~LField();

	bool setBuilding(ILBuilding* building);
	ILBuilding* getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool isPlacingAllowed();
};

