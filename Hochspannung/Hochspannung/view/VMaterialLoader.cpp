#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


std::map<VMaterialLoader::FieldPair, CMaterial> VMaterialLoader::fieldMaterials;

CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;
CMaterial VMaterialLoader::materialDialogBackground;
CMaterial VMaterialLoader::materialIngameBorder;

//Buttons

CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpiel;
CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpielHover;
CMaterial VMaterialLoader::materialButtonMainMenueOptionen;
CMaterial VMaterialLoader::materialButtonMainMenueOptionenHover;
CMaterial VMaterialLoader::materialButtonMainMenueCredits;
CMaterial VMaterialLoader::materialButtonMainMenueCreditsHover;
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeenden; 
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeendenHover;

CMaterial VMaterialLoader::materialButtonMainMenueEinzelspieler;
CMaterial VMaterialLoader::materialButtonMainMenueEinzelspielerHover;
CMaterial VMaterialLoader::materialButtonMainMenueMehrspieler;
CMaterial VMaterialLoader::materialButtonMainMenueMehrspielerHover;

CMaterial VMaterialLoader::materialButtonBack;
CMaterial VMaterialLoader::materialButtonBackHover;

void VMaterialLoader::init()
{
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL1)].MakeTextureDiffuse("textures/blue_image.jpg");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL2)].MakeTextureDiffuse("textures/blue_image.jpg");
	fieldMaterials[FieldPair(LField::WATER, LField::LEVEL3)].MakeTextureDiffuse("textures/blue_image.jpg");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL1)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL2)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::OIL, LField::LEVEL3)].MakeTextureDiffuse("textures/black_image.jpg");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL1)].MakeTextureDiffuse("textures/green_image.jpg");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL2)].MakeTextureDiffuse("textures/green_image.jpg");
	fieldMaterials[FieldPair(LField::GRASS, LField::LEVEL3)].MakeTextureDiffuse("textures/green_image.jpg");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL1)].MakeTextureDiffuse("textures/white_image.jpg");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL2)].MakeTextureDiffuse("textures/white_image.jpg");
	fieldMaterials[FieldPair(LField::COAL, LField::LEVEL3)].MakeTextureDiffuse("textures/white_image.jpg");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL1)].MakeTextureDiffuse("textures/VektoriaLogo_400x400.bmp");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL2)].MakeTextureDiffuse("textures/VektoriaLogo_400x400.bmp");
	fieldMaterials[FieldPair(LField::MOUNTAIN, LField::LEVEL3)].MakeTextureDiffuse("textures/VektoriaLogo_400x400.bmp");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL1)].MakeTextureDiffuse("textures/_original.jpg");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL2)].MakeTextureDiffuse("textures/_original.jpg");
	fieldMaterials[FieldPair(LField::CITY, LField::LEVEL3)].MakeTextureDiffuse("textures/_original.jpg");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	//materialMainMenue.Init(CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F), CColor(0.2F, 0.58F, 0.77F));
	//materialMainMenueHover.Init(CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27), CColor(0.87, 0.73, 0.27));
	//materialMainMenue.MakeTextureSprite("textures\\MainMenueNewGame.png");
	//materialMainMenue.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpiel.png");
	//materialMainMenueHover.MakeTextureSprite("textures\\MainMenueNewGameHover.png");
	//materialIngameCraft.Init(CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F), CColor(0.2F, 0.80F, 0.77F));
	//materialDialogBackground.Init(CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F), CColor(0.18F, 0.49F, 0.69F));
	
	materialDialogBackground.MakeTextureSprite("textures\\MainMenueBackground.png");
	materialIngameBorder.Init(CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68));

	//Buttons
	materialButtonMainMenueNeuesSpiel.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpiel.png");
	materialButtonMainMenueNeuesSpielHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueNeuesSpielHover.png");
	materialButtonMainMenueOptionen.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueOptionen.png");
	materialButtonMainMenueOptionenHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueOptionenHover.png");
	materialButtonMainMenueCredits.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueCredits.png");
	materialButtonMainMenueCreditsHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueCreditsHover.png");
	materialButtonMainMenueSpielBeenden.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueSpielBeenden.png");
	materialButtonMainMenueSpielBeendenHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueSpielBeendenHover.png");
	
	materialButtonMainMenueEinzelspieler.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueEinzelspieler.png");
	materialButtonMainMenueEinzelspielerHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueEinzelspielerHover.png");
	materialButtonMainMenueMehrspieler.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueMehrspieler.png");
	materialButtonMainMenueMehrspielerHover.MakeTextureSprite("textures\\Buttons\\ButtonMainMenueMehrspielerHover.png");

	materialButtonBack.MakeTextureSprite("textures\\Buttons\\ButtonBack.png");
	materialButtonBackHover.MakeTextureSprite("textures\\Buttons\\ButtonBackHover.png");

}


NAMESPACE_VIEW_E
