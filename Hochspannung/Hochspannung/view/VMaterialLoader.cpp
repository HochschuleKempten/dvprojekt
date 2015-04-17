#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


std::map<VMaterialLoader::FieldPair, CMaterial> VMaterialLoader::fieldMaterials;

CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;

void VMaterialLoader::setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName)
{
	std::string textureDiffuse = std::string("textures/texture_terrain_") + textureName + std::string("_diffuse.png");
	std::string textureSpecular = std::string("textures/texture_terrain_") + textureName + std::string("_specular.png");
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
}

void VMaterialLoader::init()
{
	setFieldMaterialHelper(LField::WATER, "water");
	setFieldMaterialHelper(LField::AIR, "air");
	setFieldMaterialHelper(LField::SOLAR, "solar");
	setFieldMaterialHelper(LField::COAL, "coal");
	setFieldMaterialHelper(LField::GRASS, "base");
	setFieldMaterialHelper(LField::MOUNTAIN, "mountain");
	setFieldMaterialHelper(LField::CITY, "city");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	materialMainMenueHover.Init(CColor(0.87F, 0.73F, 0.27F), CColor(0.87F, 0.73F, 0.27F), CColor(0.87F, 0.73F, 0.27F));
	materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
}


NAMESPACE_VIEW_E
