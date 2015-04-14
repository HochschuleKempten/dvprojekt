#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;
CMaterial VMaterialLoader::materialDialogBackground;

//Buttons

CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpiel;
CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpielHover;
CMaterial VMaterialLoader::materialButtonMainMenueOptionen;
CMaterial VMaterialLoader::materialButtonMainMenueOptionenHover;
CMaterial VMaterialLoader::materialButtonMainMenueCredits;
CMaterial VMaterialLoader::materialButtonMainMenueCreditsHover;
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeenden; 
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeendenHover;



void VMaterialLoader::init()
{
	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	//materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	//materialMainMenueHover.Init(CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27));
	//materialMainMenue.MakeTextureSprite("textures\\MainMenueNewGame.png");
	materialMainMenue.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpiel.png");
	materialMainMenueHover.MakeTextureSprite("textures\\MainMenueNewGameHover.png");
	materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
	//materialDialogBackground.Init(CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F));
	
	materialDialogBackground.MakeTextureSprite("textures\\MainMenueBackground.png");
	
	//Buttons
	materialButtonMainMenueNeuesSpiel.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpiel.png");
	materialButtonMainMenueNeuesSpielHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpielHover.png");
	materialButtonMainMenueOptionen.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueOptionen.png");
	materialButtonMainMenueOptionenHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueOptionenHover.png");
	materialButtonMainMenueCredits.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueCredits.png");
	materialButtonMainMenueCreditsHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueCreditsHover.png");
	materialButtonMainMenueSpielBeenden.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueSpielBeenden.png");
	materialButtonMainMenueSpielBeendenHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueSpielBeendenHover.png");

}


NAMESPACE_VIEW_E
