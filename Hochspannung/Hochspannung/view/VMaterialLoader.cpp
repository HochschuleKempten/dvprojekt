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


CMaterial VMaterialLoader::materialButtonBack;
CMaterial VMaterialLoader::materialButtonBackHover;
CMaterial VMaterialLoader::materialBottombarBorderTop;
CMaterial VMaterialLoader::materialVerticalBorder;
CMaterial VMaterialLoader::materialLobbyBigDialog;
CMaterial VMaterialLoader::materialBuildingButton;
CMaterial VMaterialLoader::materialBuildingButtonHover;

//Ingame Buttons
CMaterial VMaterialLoader::materialIngameButtonCraftmenu;
CMaterial VMaterialLoader::materialIngameButtonSabotage;
CMaterial VMaterialLoader::materialIngameButtonStatistics;

CMaterial VMaterialLoader::materialIngameButtonCraftmenuHover;
CMaterial VMaterialLoader::materialIngameButtonSabotageHover;
CMaterial VMaterialLoader::materialIngameButtonStatisticsHover;
//Craftmenu
CMaterial VMaterialLoader::materialCraftmenuButtonWindmill;
CMaterial VMaterialLoader::materialCraftmenuButtonHydroPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonSolarPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonCoalPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonOilPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonNuclearPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonPowerline;

CMaterial VMaterialLoader::materialCraftmenuButtonWindmillHover;
CMaterial VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonOilPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonPowerlineHover;

//WritingFont
CWritingFont VMaterialLoader::standardFont;
CWritingFont VMaterialLoader::GoldFont;

//Trassentexturen
CMaterial VMaterialLoader::m_zmConcrete;
CMaterial VMaterialLoader::m_zmStrut;
CMaterial VMaterialLoader::m_zmIsolator;
CMaterial VMaterialLoader::m_zmRing;
CMaterial VMaterialLoader::m_zmCable;

//Solarkraftwerktexturen
CMaterial VMaterialLoader::m_zmSolarzelle;
CMaterial VMaterialLoader::m_zmSolarGrund;

//PlayerColor
std::unordered_map<LPlayer::PlayerId, CColor> VMaterialLoader::colorPlayers;

//PlayerFoundations
std::unordered_map<LPlayer::PlayerId, CMaterial> VMaterialLoader::materialFoundationPlayer;

void VMaterialLoader::setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName)
{
	std::string textureDiffuse = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_diffuse.png");
	std::string textureSpecular = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_specular.png");
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
	setFieldMaterialHelper(LField::OIL, "oil");
	setFieldMaterialHelper(LField::NUCLEAR, "atom");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");

	materialDialogBackground.MakeTextureSprite("textures\\MainMenueBackground.png");
	materialIngameBorder.Init(CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68));

	//Main menu - Buttons
	materialButtonMainMenueNeuesSpiel.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_newgame.png");
	materialButtonMainMenueNeuesSpielHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_newgame_hover.png");
	materialButtonMainMenueOptionen.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_options.png");
	materialButtonMainMenueOptionenHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_options_hover.png");
	materialButtonMainMenueCredits.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_credits.png");
	materialButtonMainMenueCreditsHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_credits_hover.png");
	materialButtonMainMenueSpielBeenden.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_exit.png");
	materialButtonMainMenueSpielBeendenHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_exit_hover.png");
	materialButtonBack.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_back.png");
	materialButtonBackHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_back_hover.png");

	//Interface - Background
	materialTopbar.MakeTextureSprite("textures\\topbar.png");
	materialBottombarBorderTop.MakeTextureSprite("textures\\bottombarBorderTopBlue.png");
	materialVerticalBorder.MakeTextureSprite("textures\\VerticalBorder.png");
	materialLobbyBigDialog.MakeTextureSprite("textures\\LobbyBigDialog.png");
	materialBuildingButton.MakeTextureSprite("textures\\BuildingButton.png");
	materialBuildingButtonHover.MakeTextureSprite("textures\\BuildingButtonHover.png");

	//Interface - Selection Buttons
	materialIngameButtonCraftmenu.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu.png");
	materialIngameButtonCraftmenuHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu_hover.png");
	materialIngameButtonSabotage.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage.png");
	materialIngameButtonSabotageHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage_hover.png");
	materialIngameButtonStatistics.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics.png");
	materialIngameButtonStatisticsHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics_hover.png");

	//Interface - Panel_Building
	materialCraftmenuButtonWindmill.MakeTextureSprite("textures\\Buttons\\BuildingButtonWindmill.png");
	materialCraftmenuButtonHydroPowerplant.MakeTextureSprite("textures\\Buttons\\BuildingButtonHydroPowerplant.png");
	materialCraftmenuButtonSolarPowerplant.MakeTextureSprite("textures\\Buttons\\BuildingButtonSolarPowerplant.png");
	materialCraftmenuButtonCoalPowerplant.MakeTextureSprite("textures\\Buttons\\BuildingButtonCoalPowerplant.png");
	materialCraftmenuButtonOilPowerplant.MakeTextureSprite("textures\\Buttons\\BuildingButtonOilPowerplant.png");
	materialCraftmenuButtonNuclearPowerplant.MakeTextureSprite("textures\\Buttons\\BuildingButtonNuclearPowerplant.png");
	materialCraftmenuButtonPowerline.MakeTextureSprite("textures\\Buttons\\BuildingButtonPowerline.png");

	materialCraftmenuButtonWindmillHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonWindmillHover.png");
	materialCraftmenuButtonHydroPowerplantHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonHydroPowerplantHover.png");
	materialCraftmenuButtonSolarPowerplantHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonSolarPowerplantHover.png");
	materialCraftmenuButtonCoalPowerplantHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonCoalPowerplantHover.png");
	materialCraftmenuButtonOilPowerplantHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonOilPowerplantHover.png");
	materialCraftmenuButtonNuclearPowerplantHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonNuclearPowerplantHover.png");
	materialCraftmenuButtonPowerlineHover.MakeTextureSprite("textures\\Buttons\\BuildingButtonPowerlineHover.png");

	//Test
	materialRed.MakeTextureSprite("textures\\red_image.jpg");
	materialBlue.MakeTextureSprite("textures\\blue_image.jpg");
	materialGreen.MakeTextureSprite("textures\\green_image.jpg");

	//Fonts
	standardFont.Init("textures/fonts/FontArialShadow.png", true);
	standardFont.SetTableSize(16, 6);
	GoldFont.Init("textures/fonts/FontArialShadowGold.png", true);
	GoldFont.SetTableSize(16, 6);

	//Building - Trasse
	m_zmConcrete.MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse.png");
	m_zmConcrete.MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	m_zmConcrete.MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");

	m_zmStrut.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmIsolator.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmRing.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmCable.MakeTextureDiffuse("textures\\white_image.jpg");

	//Solarkraftwerktexturen
	m_zmSolarGrund.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmSolarzelle.MakeTextureDiffuse("textures\\black_image.jpg");
	
	//Building - Foundation
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Local), std::make_tuple(196.0f / 255.0f, 51.0f / 255.0f, 66.0f / 255.0f));
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::External), std::make_tuple(222.0f / 255.0f, 186.0f / 255.0f, 69.0f / 255.0f));
	//Local player
	materialFoundationPlayer[LPlayer::Local].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_local.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");
	//Opponent
	materialFoundationPlayer[LPlayer::External].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_opponent.png");
	materialFoundationPlayer[LPlayer::External].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::External].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");
}


NAMESPACE_VIEW_E
