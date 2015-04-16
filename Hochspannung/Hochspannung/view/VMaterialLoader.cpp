#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


std::map<VMaterialLoader::FieldPair, CMaterial> VMaterialLoader::fieldMaterials;

CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;

void VMaterialLoader::init()
{
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL1)].MakeTextureDiffuse("textures/texture_terrain_water_diffuse.png");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL1)].MakeTextureSpecular("textures/texture_terrain_water_specular.png");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL2)].MakeTextureDiffuse("textures/texture_terrain_water_diffuse.png");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL2)].MakeTextureSpecular("textures/texture_terrain_water_specular.png");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL3)].MakeTextureDiffuse("textures/texture_terrain_water_diffuse.png");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL3)].MakeTextureSpecular("textures/texture_terrain_water_specular.png");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL1)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL2)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL3)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL1)].MakeTextureDiffuse("textures/texture_terrain_base_diffuse.png");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL1)].MakeTextureSpecular("textures/texture_terrain_base_specular.png");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL2)].MakeTextureDiffuse("textures/texture_terrain_base_diffuse.png");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL2)].MakeTextureSpecular("textures/texture_terrain_base_specular.png");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL3)].MakeTextureDiffuse("textures/texture_terrain_base_diffuse.png");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL3)].MakeTextureSpecular("textures/texture_terrain_base_specular.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL1)].MakeTextureDiffuse("textures/texture_terrain_coal_diffuse.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL1)].MakeTextureSpecular("textures/texture_terrain_coal_specular.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL2)].MakeTextureDiffuse("textures/texture_terrain_coal_diffuse.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL2)].MakeTextureSpecular("textures/texture_terrain_coal_specular.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL3)].MakeTextureDiffuse("textures/texture_terrain_coal_diffuse.png");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL3)].MakeTextureSpecular("textures/texture_terrain_coal_specular.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL1)].MakeTextureDiffuse("textures/texture_terrain_mountain_diffuse.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL1)].MakeTextureSpecular("textures/texture_terrain_mountain_specular.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL2)].MakeTextureDiffuse("textures/exture_terrain_mountain_diffuse.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL2)].MakeTextureSpecular("textures/texture_terrain_mountain_specular.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL3)].MakeTextureDiffuse("textures/exture_terrain_mountain_diffuse.png");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL3)].MakeTextureSpecular("textures/texture_terrain_mountain_specular.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL1)].MakeTextureDiffuse("textures/texture_terrain_city_diffuse.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL1)].MakeTextureSpecular("textures/texture_terrain_city_specular.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL2)].MakeTextureDiffuse("textures/texture_terrain_city_diffuse.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL2)].MakeTextureSpecular("textures/texture_terrain_city_specular.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL3)].MakeTextureDiffuse("textures/texture_terrain_city_diffuse.png");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL3)].MakeTextureSpecular("textures/texture_terrain_city_specular.png");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	materialMainMenueHover.Init(CColor(0.87F, 0.73F, 0.27F), CColor(0.87F, 0.73F, 0.27F), CColor(0.87F, 0.73F, 0.27F));
	materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
}


NAMESPACE_VIEW_E
