#include "VMaterialLoader.h"
#include "../logic/LPlayer.h"
#include "../logic/LUtility.h"

NAMESPACE_VIEW_B

DEBUG_EXPRESSION(bool VMaterialLoader::initDone = false);
DEBUG_EXPRESSION(static const char* const msgAssert = "VMaterialLoader is not initialized");

std::map<VMaterialLoader::FieldPair, CMaterial> VMaterialLoader::fieldMaterials;

//MainMenue
CMaterial VMaterialLoader::materialMainMenueBackground;

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
CMaterial VMaterialLoader::materialLightGrey;
CMaterial VMaterialLoader::materialBlack;
CMaterial VMaterialLoader::materialFossil;
CMaterial VMaterialLoader::materialRegenerative;

//Credits
CMaterial VMaterialLoader::materialCreditsOrganization;
CMaterial VMaterialLoader::materialCreditsIntegration;
CMaterial VMaterialLoader::materialCreditsTextures;
CMaterial VMaterialLoader::materialCreditsNetwork;
CMaterial VMaterialLoader::materialCreditsLogic;
CMaterial VMaterialLoader::materialCreditsUI;
CMaterial VMaterialLoader::materialCreditsModelling;
CMaterial VMaterialLoader::materialCreditsModelling2;
CMaterial VMaterialLoader::materialCreditsVektoriaSplash;


//Infofield
CMaterial VMaterialLoader::materialInfofieldBackground;

//Minimap
CMaterial VMaterialLoader::materialMinimapBackground;

//Lobby Buttons

CMaterial VMaterialLoader::materialButtonLobbyJoinGame;
CMaterial VMaterialLoader::materialButtonLobbyJoinGameHover;
CMaterial VMaterialLoader::materialButtonLobbyHostGame;
CMaterial VMaterialLoader::materialButtonLobbyHostGameHover;
CMaterial VMaterialLoader::materialButtonRefresh;
CMaterial VMaterialLoader::materialButtonRefreshHover;


//Buttons

CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpiel;
CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpielHover;
CMaterial VMaterialLoader::materialButtonMainMenueOptionen;
CMaterial VMaterialLoader::materialButtonMainMenueOptionenHover;
CMaterial VMaterialLoader::materialButtonMainMenueCredits;
CMaterial VMaterialLoader::materialButtonMainMenueCreditsHover;
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeenden; 
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeendenHover;

CMaterial VMaterialLoader::materialButtonGameContinue;
CMaterial VMaterialLoader::materialButtonGameContinueHover;


CMaterial VMaterialLoader::materialButtonBack;
CMaterial VMaterialLoader::materialButtonBackHover;
CMaterial VMaterialLoader::materialBottombarBorderTop;
CMaterial VMaterialLoader::materialVerticalBorder;
CMaterial VMaterialLoader::materialLobbyBigDialog;

CMaterial VMaterialLoader::materialButtonAbort;
CMaterial VMaterialLoader::materialButtonAbortHover;

CMaterial VMaterialLoader::materialButtonOk;
CMaterial VMaterialLoader::materialButtonOkHover;


//Ingame
CMaterial VMaterialLoader::materialIngameMenueDialogBackground;
CMaterial VMaterialLoader::materialErrorBackground;
//Ingame Buttons
CMaterial VMaterialLoader::materialIngameButtonCraftmenu;
CMaterial VMaterialLoader::materialIngameButtonSabotage;
CMaterial VMaterialLoader::materialIngameButtonStatistics;

CMaterial VMaterialLoader::materialIngameButtonCraftmenuHover;
CMaterial VMaterialLoader::materialIngameButtonSabotageHover;
CMaterial VMaterialLoader::materialIngameButtonStatisticsHover;

CMaterial VMaterialLoader::materialIngameButtonCraftmenuActive;
CMaterial VMaterialLoader::materialIngameButtonSabotageActive;
CMaterial VMaterialLoader::materialIngameButtonStatisticsActive;

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

//Sabotage
CMaterial VMaterialLoader::materialSabotageButtonScissors;
CMaterial VMaterialLoader::materialSabotageButtonStrike;
CMaterial VMaterialLoader::materialSabotageButtonHalf;
CMaterial VMaterialLoader::materialSabotageButtonPowerOn;
CMaterial VMaterialLoader::materialSabotageButtonPowerOff;
CMaterial VMaterialLoader::materialSabotageButtonSell;

CMaterial VMaterialLoader::materialSabotageButtonScissorsHover;
CMaterial VMaterialLoader::materialSabotageButtonStrikeHover;
CMaterial VMaterialLoader::materialSabotageButtonHalfHover;
CMaterial VMaterialLoader::materialSabotageButtonPowerOnHover;
CMaterial VMaterialLoader::materialSabotageButtonPowerOffHover;
CMaterial VMaterialLoader::materialSabotageButtonSellHover;

//Icons
CMaterial VMaterialLoader::materialIngameIconPopulation;
CMaterial VMaterialLoader::materialIngameIconMoney;
CMaterial VMaterialLoader::materialIngameIconEnergy;

//WritingFont
CWritingFont VMaterialLoader::standardFont;
CWritingFont VMaterialLoader::GoldFont;
CWritingFont VMaterialLoader::errorFont;

//Wasserkraftwerktexturen
CMaterial VMaterialLoader::m_zmWasser;

//PlayerColor
std::unordered_map<int, CColor> VMaterialLoader::colorPlayers;

//PlayerFoundations
std::unordered_map<int, CMaterial> VMaterialLoader::materialFoundationPlayer;

//Cursor
CMaterial VMaterialLoader::m_zmDefaultCursor;
CMaterial VMaterialLoader::m_zmHammerCursor;

//CraftMenue
CMaterial VMaterialLoader::m_zmCraftMenueBackground;

//MaterialBuilding
CMaterial VMaterialLoader::materialBuilding01;
CMaterial VMaterialLoader::materialBuilding02;
CMaterial VMaterialLoader::materialBuilding03;
CMaterial VMaterialLoader::materialLargeOfficeBuilding;
CMaterial VMaterialLoader::materialAppartments;
CMaterial VMaterialLoader::materialOfficTowerViewingDeck;
CMaterial VMaterialLoader::materialTwistedTower;
CMaterial VMaterialLoader::materialSmallOfficeBuilding;

// MaterialWindowBuildings
CMaterial VMaterialLoader::materialWindowsofBuilding;

//Background
CMaterial VMaterialLoader::materialDefaultBackground;
CMaterial VMaterialLoader::materialWhiteGreyBackground;
CMaterial VMaterialLoader::materialLobbyRunningGamesBackground;
CMaterial VMaterialLoader::materialLobbyGamelistBackground;
CMaterial VMaterialLoader::materialListEntryBackground;
CMaterial VMaterialLoader::materialListEntryHoverBackground;
CMaterial VMaterialLoader::materialTextfieldBackground;
CMaterial VMaterialLoader::materialTextfieldHoverBackground;
CBackground VMaterialLoader::materialIngameBackground;

//Allgemein
CMaterial VMaterialLoader::m_zmAllgemeinGreen;

//Test
CMaterial VMaterialLoader::materialAnimationsVersuch;

//Animierte Texturen
CMaterial VMaterialLoader::materialAnimSabotageBomb;
CMaterial VMaterialLoader::materialAnimLoadingCircle;
CMaterial VMaterialLoader::materialAnimSabotageHalfResource;
CMaterial VMaterialLoader::materialAnimSabotageStrike;
CMaterial VMaterialLoader::materialAnimSabotageCutPowerline;

//Animierte Texturen
CMaterial VMaterialLoader::materialAnimSabotagePowerPlant;
CMaterial VMaterialLoader::materialAnimTransformerStationLightning;
int VMaterialLoader::materialAnimSabotagePowerPlant_x;
int VMaterialLoader::materialAnimSabotagePowerPlant_y;

std::unordered_map<VMaterialLoader::Model, CMaterial> VMaterialLoader::materialsModelsSwitchedOn;
std::unordered_map<VMaterialLoader::Model, CMaterial> VMaterialLoader::materialsModelsSwitchedOff;
CColor VMaterialLoader::colorAmbientOn(0.0f, 0.0f, 0.0f);
CColor VMaterialLoader::colorAmbientOff(-0.2f, -0.2f, -0.2f);

void VMaterialLoader::setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName)
{
	std::string textureDiffuse = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_diffuse.png");
	std::string textureSpecular = std::string("textures/terrain/texture_terrain_base_specular.png");// +textureName + std::string("_specular.png");
	std::string textureBump = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_bump.png");
	std::string textureEnvironmental = std::string("textures/buildings/texture_skymap.png");
	std::string textureGlow = std::string("textures/terrain/texture_terrain_base_glow.png");
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureDiffuse(&textureDiffuse[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureDiffuse(&textureDiffuse[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureDiffuse(&textureDiffuse[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureBump(&textureBump[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureBump(&textureBump[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureBump(&textureBump[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureSpecular(&textureSpecular[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureSpecular(&textureSpecular[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureSpecular(&textureSpecular[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].SetDiffuseSharpness(2.5f);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].SetDiffuseSharpness(2.5f);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].SetDiffuseSharpness(2.5f);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureEnvironment(&textureEnvironmental[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureEnvironment(&textureEnvironmental[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureEnvironment(&textureEnvironmental[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureGlow(&textureGlow[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureGlow(&textureGlow[0]);
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureGlow(&textureGlow[0]);
}

void VMaterialLoader::setPowerPlantMaterialHelper(const Model materialPowerPlant, const std::string& textureName)
{
	//Define every texture type and its corresponding vectoria calls
	const std::unordered_map<std::string, std::function<void(std::string&)>> textureTypes =
	{
		{ "diffuse", [materialPowerPlant] (std::string& path)
			{
				ASSERT(materialsModelsSwitchedOn.count(materialPowerPlant) == 0, "Can't initialize Material " << materialPowerPlant << " twice");
				ASSERT(materialsModelsSwitchedOff.count(materialPowerPlant) == 0, "Can't initialize Material " << materialPowerPlant << " twice");

				materialsModelsSwitchedOn[materialPowerPlant].MakeTextureDiffuse(&path[0]);
				materialsModelsSwitchedOn[materialPowerPlant].SetColorAmbient(colorAmbientOn);

				materialsModelsSwitchedOff[materialPowerPlant].MakeTextureDiffuse(&path[0]);
				materialsModelsSwitchedOff[materialPowerPlant].SetColorAmbient(colorAmbientOff);
			}
		},
		{
			"bump", [materialPowerPlant] (std::string& path)
			{
				materialsModelsSwitchedOn[materialPowerPlant].MakeTextureBump(&path[0]);
				materialsModelsSwitchedOff[materialPowerPlant].MakeTextureBump(&path[0]);
			}
		},
		{
			"specular", [materialPowerPlant] (std::string& path)
			{
				materialsModelsSwitchedOn[materialPowerPlant].MakeTextureSpecular(&path[0]);
				materialsModelsSwitchedOff[materialPowerPlant].MakeTextureSpecular(&path[0]);
			}
		},
		{
			"glow", [materialPowerPlant] (std::string& path)
			{
				materialsModelsSwitchedOn[materialPowerPlant].MakeTextureGlow(&path[0]);
				materialsModelsSwitchedOff[materialPowerPlant].MakeTextureGlow(&path[0]);
			}
		}
	};
	
	std::string fileExtension = getFileExtension(textureName);
	std::string basePath = textureName.substr(0, textureName.size() - fileExtension.size() - 1);

	std::fstream file;
	std::string path;
	
	//Try every texture type
	for (auto type : textureTypes)
	{
		//Check models folder (it is assumed that root textures have no type suffix (e. g. no _diffuse)
		path = "textures/models/" + basePath + "_" + type.first + "." + fileExtension;
		file.open(path, std::ios::in);
		if (file.is_open())		//Check if file exists
		{
			type.second(path);
			file.close();
		}
		file.clear();
	}

	//Check texture root folder
	path = "textures/" + basePath + "." + fileExtension;
	file.open(path, std::ios::in);
	if (file.is_open())		//Check if file exists
	{
		textureTypes.at("diffuse")(path);
		file.close();
	}
	file.clear();
}

CMaterial* VMaterialLoader::getMaterialModel(const Model materialPowerPlant, const bool switchedOn)
{
	ASSERT(initDone, msgAssert);
	ASSERT(materialsModelsSwitchedOn.count(materialPowerPlant) > 0, "Requested material is not available");

	if (switchedOn)
	{
		return &materialsModelsSwitchedOn[materialPowerPlant];
	}
	else
	{
		return &materialsModelsSwitchedOff[materialPowerPlant];
	}
}

void VMaterialLoader::init()
{
	setPowerPlantMaterialHelper(COAL_MOUNTAIN, "mountain.png");
	setPowerPlantMaterialHelper(COAL_STRUCTURE, "kohle_image.jpg");
	setPowerPlantMaterialHelper(COAL_WOOD, "holz_image.jpg");
	setPowerPlantMaterialHelper(COAL_WAGON, "lore_image.jpg");
	setPowerPlantMaterialHelper(COAL_BLACK, "black_image.jpg");
	setPowerPlantMaterialHelper(COAL_GREY, "grey_image.jpg");
	setPowerPlantMaterialHelper(POWERLINE_STRUT, "strommast.png");
	setPowerPlantMaterialHelper(POWERLINE_ISOLATOR, "black_image.jpg");
	setPowerPlantMaterialHelper(POWERLINE_RING, "black_image.jpg");
	setPowerPlantMaterialHelper(POWERLINE_CABLE, "strommast_cable.png");
	setPowerPlantMaterialHelper(TRANSFORMERSTATION_BETON, "Beton.png");
	setPowerPlantMaterialHelper(TRANSFORMERSTATION_BETON_LIGHT, "Beton_light.png");
	setPowerPlantMaterialHelper(TRANSFORMERSTATION_ISOLATOR, "black_image.jpg");
	setPowerPlantMaterialHelper(TRANSFORMERSTATION_WIRE, "grey_image.jpg");
	setPowerPlantMaterialHelper(SOLAR_FLOOR, "white_image.jpg");
	setPowerPlantMaterialHelper(SOLAR_CELL, "SolarPanel.jpg");
	setPowerPlantMaterialHelper(SOLAR_CELLS_LOD, "SolarLOD.jpg");
	setPowerPlantMaterialHelper(WIND_RAD, "Metall_Fassade.jpg" );
	setPowerPlantMaterialHelper(WIND_FLUEGEL1,"Windradfluegel.png");
	setPowerPlantMaterialHelper(WIND_FLUEGEL2,"Windradfluegel.png");
	setPowerPlantMaterialHelper(WIND_FLUEGEL3, "Windradfluegel.png");
	setPowerPlantMaterialHelper(WATER_HOLZ, "Holz.jpg");
	setPowerPlantMaterialHelper(BUILDING_WALLFRAME, "../buildings/texture_concrete.png");
	setPowerPlantMaterialHelper(NUCLEAR_FLOOR, "Beton.png");
	setPowerPlantMaterialHelper(NUCLEAR_GATE, "Schranke.jpg");
	setPowerPlantMaterialHelper(NUCLEAR_FENCE, "Holz.jpg");
	setPowerPlantMaterialHelper(NUCLEAR_REACTOR, "reactor.png");
	setPowerPlantMaterialHelper(OIL_FLOOR, "Beton.png");
	setPowerPlantMaterialHelper(OIL_GATE, "Schranke.jpg");
	setPowerPlantMaterialHelper(OIL_FENCE, "Holz.jpg");
	setPowerPlantMaterialHelper(OIL_GREEN_RAY, "Gelbstahl.png");
	setPowerPlantMaterialHelper(OIL_YELLOW_RAY, "Gruenstahl.png");
	
	materialsModelsSwitchedOn[TRANSFORMERSTATION_BETON].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[TRANSFORMERSTATION_BETON].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[BUILDING_WINDOW].MakeTextureEnvironment("textures/buildings/texture_skymap.png");
	materialsModelsSwitchedOff[BUILDING_WINDOW].MakeTextureEnvironment("textures/buildings/texture_skymap.png");
	materialsModelsSwitchedOn[BUILDING_WINDOW].MakeTextureSpecular("textures/buildings/texture_window_specular.png");
	materialsModelsSwitchedOff[BUILDING_WINDOW].MakeTextureSpecular("textures/buildings/texture_window_specular.png");
	materialsModelsSwitchedOn[NUCLEAR_FLOOR].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[NUCLEAR_FLOOR].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[NUCLEAR_GATE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[NUCLEAR_GATE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[NUCLEAR_FENCE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[NUCLEAR_FENCE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[OIL_FLOOR].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[OIL_FLOOR].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[OIL_GATE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[OIL_GATE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOn[OIL_FENCE].SetTextureSpecularAsDiffuse();
	materialsModelsSwitchedOff[OIL_FENCE].SetTextureSpecularAsDiffuse();
	
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
	materialButtonAbort.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort.png");
	materialButtonAbortHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort_hover.png");

	materialButtonOk.MakeTextureSprite("textures/gui/Buttons/ButtonOK.png");
	materialButtonOkHover.MakeTextureSprite("textures/gui/Buttons/ButtonOKHover.png");

	materialButtonGameContinue.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_continue.png");
	materialButtonGameContinueHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_continue_hover.png");

	materialButtonMainMenueNeuesSpiel.SetTransparencyOn();
	materialButtonMainMenueNeuesSpielHover.SetTransparencyOn();

	//MainMenue Background
	materialMainMenueBackground.MakeTextureSprite("textures/gui/background/wasserkraftwerk.png");

	//Lobby Buttons
	materialButtonLobbyJoinGame.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGame.png");
	materialButtonLobbyJoinGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGameHover.png");
	materialButtonLobbyHostGame.MakeTextureSprite("textures/gui/Buttons/ButtonHostGame.png");
	materialButtonLobbyHostGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonHostGameHover.png");
	materialButtonRefresh.MakeTextureSprite("textures/gui/Buttons/gui_lobby_refresh.png");
	materialButtonRefreshHover.MakeTextureSprite("textures/gui/Buttons/gui_lobby_refreshHover.png");
		

	//Interface - Background
	materialTopbar.MakeTextureSprite("textures\\topbar.png");
	materialBottombarBorderTop.MakeTextureSprite("textures\\bottombarBorderTopBlue.png");
	materialVerticalBorder.MakeTextureSprite("textures\\VerticalBorder.png");
	materialLobbyBigDialog.MakeTextureSprite("textures\\LobbyBigDialog.png");
	materialIngameMenueDialogBackground.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_MenueDialog_Background.png");
	materialWhiteGreyBackground.MakeTextureSprite("textures/gui/background/gui_background_whitegrey.png");

	materialTopbar.SetTransparencyOn();

	//Interface - Selection Buttons
	materialIngameButtonCraftmenu.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu.png");
	materialIngameButtonCraftmenuHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu_hover.png");
	materialIngameButtonCraftmenuActive.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu_active.png");
	materialIngameButtonSabotage.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage.png");
	materialIngameButtonSabotageHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage_hover.png");
	materialIngameButtonSabotageActive.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage_active.png");
	materialIngameButtonStatistics.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics.png");
	materialIngameButtonStatisticsHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics_hover.png");
	materialIngameButtonStatisticsActive.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics_active.png");

	//Interface - Panel_Building
	materialCraftmenuButtonWindmill.MakeTextureSprite("textures/gui/Buttons/gui_ingame_airPowerPlant.png");
	materialCraftmenuButtonHydroPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_hydroPowerPlant.png");
	materialCraftmenuButtonSolarPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_solarPowerPlant.png");
	materialCraftmenuButtonCoalPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_coalPowerPlant.png");
	materialCraftmenuButtonOilPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_oilPowerPlant.png");
	materialCraftmenuButtonNuclearPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_nuclearPowerPlant.png");
	materialCraftmenuButtonPowerline.MakeTextureSprite("textures/gui/Buttons/gui_ingame_powerLine.png");

	materialCraftmenuButtonWindmillHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_airPowerPlantHover.png");
	materialCraftmenuButtonHydroPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_hydroPowerPlantHover.png");
	materialCraftmenuButtonSolarPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_solarPowerPlantHover.png");
	materialCraftmenuButtonCoalPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_coalPowerPlantHover.png");
	materialCraftmenuButtonOilPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_oilPowerPlantHover.png");
	materialCraftmenuButtonNuclearPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_nuclearPowerPlantHover.png");
	materialCraftmenuButtonPowerlineHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_powerLineHover.png");

	//Sabotage
	materialSabotageButtonScissors.MakeTextureSprite("textures/gui/Buttons/gui_ingame_scissors.png");
	materialSabotageButtonStrike.MakeTextureSprite("textures/gui/Buttons/gui_ingame_strike.png");
	materialSabotageButtonHalf.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_half.png");
	materialSabotageButtonPowerOn.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_poweron.png");
	materialSabotageButtonPowerOff.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_poweroff.png");
	materialSabotageButtonSell.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_sell.png");
	
	
	materialSabotageButtonScissorsHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_scissorsHover.png");
	materialSabotageButtonStrikeHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_strikeHover.png");
	materialSabotageButtonHalfHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_halfHover.png");
	materialSabotageButtonPowerOnHover.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_poweronhover.png");
	materialSabotageButtonPowerOffHover.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_poweroffhover.png");
	materialSabotageButtonSellHover.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_sellhover.png");

	//Test
	materialRed.MakeTextureSprite("textures\\red_image.jpg");
	materialBlue.MakeTextureSprite("textures\\blue_image.jpg");
	materialGreen.MakeTextureSprite("textures\\green_image.jpg");
	materialLightGrey.MakeTextureSprite("textures\\lightgrey_image.png");
	materialBlack.MakeTextureSprite("textures\\black_image.jpg");
	materialFossil.MakeTextureSprite("textures\\fossil_stats.png");
	materialRegenerative.MakeTextureSprite("textures\\regenerative_stats.png");

	materialAnimationsVersuch.MakeTextureSprite("textures/fonts/FontArialShadow.png");
	materialAnimationsVersuch.SetAni(16, 16, 0.5);

	//Fonts
	//standardFont.Init("textures/fonts/FontArialShadow.png",false);
	//standardFont.SetTableSize(16, 16);
	//standardFont.Init("textures/fonts/OCRStandardBevel.png", true);
	standardFont.Init("textures/fonts/OCRBlueBevel.png", true);
	
	standardFont.SetTableSize(16,16);
	/*GoldFont.Init("textures/fonts/FontArialShadowGold.png", false);
	GoldFont.SetTableSize(16, 16);*/

	GoldFont.Init("textures/fonts/OCRGold.png", true);
	GoldFont.SetTableSize(16, 16);

	errorFont.Init("textures/fonts/OCRError.png", true);
	errorFont.SetTableSize(16, 16);

	//Atomkraftwerktexturen
	m_zmAllgemeinGreen.MakeTextureDiffuse("Textures\\green_image.jpg");
	
	//Wasserkraftwerktexturen
	m_zmWasser.MakeTextureSprite("Textures\\animations\\Water.png");
	m_zmWasser.SetAni(80, 2, 160.0 / 16.0);
	
	//Building - Foundation
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Remote), std::make_tuple(196.0f / 255.0f, 51.0f / 255.0f, 66.0f / 255.0f));
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Local), std::make_tuple(222.0f / 255.0f, 186.0f / 255.0f, 69.0f / 255.0f));
	//Local player
	materialFoundationPlayer[LPlayer::Local].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_local.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");
	//Opponent
	materialFoundationPlayer[LPlayer::Remote].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_opponent.png");
	materialFoundationPlayer[LPlayer::Remote].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::Remote].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");

	materialFoundationPlayer[LPlayer::Local | LPlayer::Remote].MakeTextureDiffuse("textures/powerpants/Beton_light.png");
	materialFoundationPlayer[LPlayer::Local | LPlayer::Remote].MakeTextureBump("textures/powerpants/Beton_light_bump.png");

	//Cursor
	m_zmDefaultCursor.MakeTextureSprite("textures\\gui\\default_zeiger.png");
	m_zmHammerCursor.MakeTextureSprite("textures\\gui\\Hammer.png");
	m_zmDefaultCursor.SetTransparencyOn();
	m_zmHammerCursor.SetTransparencyOn();

	//CraftMenue
	m_zmCraftMenueBackground.MakeTextureSprite("textures/gui/background/gui_ingame_baumenu.png");

	//Infofield
	materialInfofieldBackground.MakeTextureSprite("textures/gui/background/gui_ingame_infofield.png");
	materialInfofieldBackground.SetTransparencyOn();
	//Minimap
	materialMinimapBackground.MakeTextureSprite("textures/gui/background/gui_ingame_minimap.png");

	materialMinimapBackground.SetTransparencyOn();
	//Icons
	materialIngameIconPopulation.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_Icon_Population.png");
	materialIngameIconMoney.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_Icon_Money.png");
	materialIngameIconEnergy.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_Icon_Energy.png");

	materialIngameIconPopulation.SetTransparencyOn();
	materialIngameIconMoney.SetTransparencyOn();
	materialIngameIconEnergy.SetTransparencyOn();
	//Default Background
	materialDefaultBackground.MakeTextureSprite("textures/gui/background/texture_gui_background_grey.png");
	materialDefaultBackground.SetTransparencyOn();
	//CityBuildings
	materialBuilding01.MakeTextureDiffuse("textures\\buildings\\Hauswand_3.png");
	materialBuilding01.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialBuilding01.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialBuilding02.MakeTextureDiffuse("textures\\buildings\\texture_concrete_diffuse.png");
	materialBuilding02.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialBuilding02.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialBuilding03.MakeTextureDiffuse("textures\\buildings\\Hauswand_4.png");
	materialBuilding03.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialBuilding03.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");
	
	materialAppartments.MakeTextureDiffuse("textures\\buildings\\Hauswand_2.png");
	materialAppartments.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialAppartments.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialLargeOfficeBuilding.MakeTextureDiffuse("textures\\buildings\\Hauswand_2.png");
	materialLargeOfficeBuilding.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialBuilding03.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialOfficTowerViewingDeck.MakeTextureDiffuse("textures\\buildings\\Hauswand_1.png");
	materialOfficTowerViewingDeck.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialOfficTowerViewingDeck.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialSmallOfficeBuilding.MakeTextureDiffuse("textures\\buildings\\Hauswand_4.png");
	materialSmallOfficeBuilding.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialSmallOfficeBuilding.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialTwistedTower.MakeTextureDiffuse("textures\\buildings\\texture_concrete_diffuse.png");
	materialTwistedTower.MakeTextureBump("textures\\buildings\\texture_concrete_bump.png");
	materialTwistedTower.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialWindowsofBuilding.MakeTextureEnvironment("textures/buildings/texture_skymap.png");
	materialWindowsofBuilding.MakeTextureSpecular("textures/buildings/texture_window_specular.png");
	

	//Animierte Texturen
	materialAnimSabotageBomb.MakeTextureSprite("textures/gui/animiert/Bombe.png");
	materialAnimSabotageBomb.SetAni(9, 2, 1);
	//materialAnimSabotageBomb.MakeTextureSprite("textures/fonts/FontArialShadow.png");
	//materialAnimSabotageBomb.SetAni(16, 16, 1);

	materialAnimLoadingCircle.MakeTextureSprite("textures/gui/animiert/LoadingCircle.png");
	materialAnimLoadingCircle.SetAni(25, 2, 10);

	materialAnimLoadingCircle.SetTransparencyOn();

	materialAnimSabotageHalfResource.MakeTextureSprite("textures/gui/animiert/ResourceHalf.png");
	materialAnimSabotageHalfResource.SetAni(60, 2, 1);

	materialAnimSabotageStrike.MakeTextureSprite("textures/gui/animiert/Strike.png");
	materialAnimSabotageStrike.SetAni(45, 2, 1);

	materialAnimSabotageCutPowerline.MakeTextureSprite("textures/gui/animiert/CutPowerLine.png");
	materialAnimSabotageCutPowerline.SetAni(30, 2, 1);

	materialAnimSabotagePowerPlant.MakeTextureSprite("textures/animations/Strike.png");
	materialAnimSabotagePowerPlant_x = 60;
	materialAnimSabotagePowerPlant_y = 2;
	
	materialAnimTransformerStationLightning.MakeTextureSprite("textures/animations/Lightning.png");
	materialAnimTransformerStationLightning.SetAni(15, 2, 30.0f / 5.0f);

	//Background
	materialLobbyRunningGamesBackground.MakeTextureSprite("textures/gui/background/gui_lobby_RunningGamesBackround.png");
	materialLobbyGamelistBackground.MakeTextureSprite("textures/gui/background/ListView.png");
	materialListEntryBackground.MakeTextureSprite("textures/gui/background/gui_ListEntry.png");
	materialListEntryHoverBackground.MakeTextureSprite("textures/gui/background/gui_ListEntryHover.png");
	materialTextfieldBackground.MakeTextureSprite("textures/gui/background/gui_textfield_background.png");
	materialTextfieldHoverBackground.MakeTextureSprite("textures/gui/background/gui_textfield_backgroundHover.png");
	materialErrorBackground.MakeTextureSprite("textures/gui/background/gui_error_background.png");
	materialIngameBackground.InitFull("textures/background.png");

	materialLobbyRunningGamesBackground.SetTransparencyOn();

	//Credits

	materialCreditsOrganization.MakeTextureSprite("textures/gui/Credits/Organisation.png");
	materialCreditsIntegration.MakeTextureSprite("textures/gui/Credits/Integration.png");
	materialCreditsTextures.MakeTextureSprite("textures/gui/Credits/TexturenSound.png");
	materialCreditsNetwork.MakeTextureSprite("textures/gui/Credits/Netzwerk.png");
	materialCreditsLogic.MakeTextureSprite("textures/gui/Credits/Spiellogik.png");
	materialCreditsUI.MakeTextureSprite("textures/gui/Credits/UI.png");
	materialCreditsModelling.MakeTextureSprite("textures/gui/Credits/Modellierung.png");
	materialCreditsModelling2.MakeTextureSprite("textures/gui/Credits/Modellierung2.png");
	materialCreditsVektoriaSplash.MakeTextureSprite("textures/gui/Credits/VektoriaSplash.png");

	materialCreditsOrganization.SetTransparencyOn();
	materialCreditsIntegration.SetTransparencyOn();
	materialCreditsTextures.SetTransparencyOn();
	materialCreditsNetwork.SetTransparencyOn();
	materialCreditsLogic.SetTransparencyOn();
	materialCreditsUI.SetTransparencyOn();
	materialCreditsModelling.SetTransparencyOn();
	materialCreditsModelling2.SetTransparencyOn();
	materialCreditsVektoriaSplash.SetTransparencyOn();

	DEBUG_EXPRESSION(initDone = true);
}

//Rotation adjustments
float VMaterialLoader::getRotationPerTick(const VIdentifier::VIdentifier powerPlant, const float fTimeDelta)
{
	ASSERT(initDone, msgAssert);

	switch (powerPlant)
	{
		case VIdentifier::VCoalPowerPlant: return CASTS<float>((2.0 * M_PI / 8.0) * fTimeDelta);	//Number of seconds per rotation
		case VIdentifier::VHydroelectricPowerPlant: return CASTS<float>((2.0 * M_PI / 8.0) * fTimeDelta);
		case VIdentifier::VWindmillPowerPlant: return CASTS<float>((2.0 * M_PI / 2.0) * fTimeDelta);
		case VIdentifier::VSolarPowerPlant: return CASTS<float>((2.0 * M_PI / 8.0) * fTimeDelta);
		case VIdentifier::VOilRefinery: return CASTS<float>((2.0 * M_PI / 8.0) * fTimeDelta);
		//case VIdentifier::VNuclearPowerPlant: break;
		default:
			ASSERT("No Rotation for this power plant available");
			return 1.0;
	}
}

NAMESPACE_VIEW_E
