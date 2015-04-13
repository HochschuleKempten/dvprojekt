#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
private:
	VMaterialLoader()
	{}
	~VMaterialLoader()
	{}

public:
	static void init();

	static CMaterial materialCoalPowerPlant;
	static CMaterial materialHydroelectricPowerPlant;
	
	//MainMenue
	static CMaterial materialMainMenue;
	static CMaterial materialMainMenueHover;
	//Ingame
	static CMaterial materialIngameCraft;
	static CMaterial materialDialogBackground;
	
};


NAMESPACE_VIEW_E
