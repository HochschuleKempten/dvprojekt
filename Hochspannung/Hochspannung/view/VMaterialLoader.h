#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"

NAMESPACE_VIEW_B



class VMaterialLoader
{
private:
	inline VMaterialLoader()
	{}
	inline ~VMaterialLoader()
	{}

public:
	static void init();

	using FieldPair = std::pair<LField::FieldType, LField::FieldLevel>;
	static std::map<FieldPair, CMaterial> fieldMaterials;

	static CMaterial materialCoalPowerPlant;
	static CMaterial materialHydroelectricPowerPlant;
	static CMaterial materialMainMenue;
	static CMaterial materialMainMenueHover;
	static CMaterial materialIngameCraft;
};


NAMESPACE_VIEW_E
