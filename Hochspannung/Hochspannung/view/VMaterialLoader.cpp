#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;
CMaterial VMaterialLoader::materialDialogBackground;

void VMaterialLoader::init()
{
	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	//materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	//materialMainMenueHover.Init(CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27));
	materialMainMenue.MakeTextureSprite("textures\\MainMenueNewGame.png");
	materialMainMenueHover.MakeTextureSprite("textures\\MainMenueNewGameHover.png");
	materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
	materialDialogBackground.Init(CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F));
}


NAMESPACE_VIEW_E
