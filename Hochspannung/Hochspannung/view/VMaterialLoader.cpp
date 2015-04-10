#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;

void VMaterialLoader::init()
{
	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
}


NAMESPACE_VIEW_E
