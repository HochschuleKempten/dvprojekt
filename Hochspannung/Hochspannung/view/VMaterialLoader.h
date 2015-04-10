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
	static CMaterial materialMainMenue;
	static CMaterial materialMainMenueHover;
	static CMaterial materialIngameCraft;
};


NAMESPACE_VIEW_E
