#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
private:
	VMaterialLoader() = delete;
	VMaterialLoader(const VMaterialLoader&) = delete;
	VMaterialLoader(const VMaterialLoader&&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&&) = delete;
	~VMaterialLoader() = delete;

	static void setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName);

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
