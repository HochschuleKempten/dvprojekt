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
CMaterial VMaterialLoader::materialTopbar;

CMaterial VMaterialLoader::materialRed;
CMaterial VMaterialLoader::materialBlue;
CMaterial VMaterialLoader::materialGreen;

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
CMaterial VMaterialLoader::materialBottombarBorderTop;
CMaterial VMaterialLoader::materialVerticalBorder;
CMaterial VMaterialLoader::materialLobbyBigDialog;
CMaterial VMaterialLoader::materialBuildingButton;
CMaterial VMaterialLoader::materialBuildingButtonHover;

//WritingFont
CWritingFont VMaterialLoader::standardFont;
CWritingFont VMaterialLoader::GoldFont;

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

	materialTopbar.MakeTextureSprite("textures\\topbar.png");
	materialBottombarBorderTop.MakeTextureSprite("textures\\bottombarBorderTopBlue.png");
	materialVerticalBorder.MakeTextureSprite("textures\\VerticalBorder.png");
	materialLobbyBigDialog.MakeTextureSprite("textures\\LobbyBigDialog.png");
	materialBuildingButton.MakeTextureSprite("textures\\BuildingButton.png");
	materialBuildingButtonHover.MakeTextureSprite("textures\\BuildingButtonHover.png");
	
	//Test
	materialRed.MakeTextureSprite("textures\\red_image.jpg");
	materialBlue.MakeTextureSprite("textures\\blue_image.jpg");
	materialGreen.MakeTextureSprite("textures\\green_image.jpg");

	//Writing Font
	standardFont.Init("textures\\FontArialShadow.png", true);
	standardFont.SetTableSize(16, 6);
	GoldFont.Init("textures\\FontArialShadowGold.png", true);
	GoldFont.SetTableSize(16, 6);
}


NAMESPACE_VIEW_E
