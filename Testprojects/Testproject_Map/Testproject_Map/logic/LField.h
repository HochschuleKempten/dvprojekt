#pragma once
#include "ILBuilding.h"
class LField
{
private:
	ILBuilding* building;
	bool isPlacingAllowed;


public:
	LField();
	~LField();

	void setBuilding(ILBuilding* building);
	ILBuilding* getBuilding();
	void setIsPlacingAllowed(bool allowed);
	bool getIsPlacingAllowed();
};

