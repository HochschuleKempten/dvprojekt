#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


std::map<std::pair<LField::FieldType, LField::FieldLevel>, CMaterial> VMaterialLoader::fieldMaterials;

CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;

void VMaterialLoader::init()
{
	fieldMaterials[std::pair<LField::FieldType, LField::FieldLevel>(LField::WATER, LField::LEVEL1)].MakeTextureDiffuse("textures/blue_image.jpg");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	materialMainMenueHover.Init(CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27));
	materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
}


NAMESPACE_VIEW_E
