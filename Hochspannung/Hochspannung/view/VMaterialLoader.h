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
};


NAMESPACE_VIEW_E
