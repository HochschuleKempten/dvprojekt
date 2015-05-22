#include "VMaterialLoader.h"
#include "../logic/LPlayer.h"

NAMESPACE_VIEW_B


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

//Infofield
CMaterial VMaterialLoader::materialInfofieldBackground;

//Minimap
CMaterial VMaterialLoader::materialMinimapBackground;

//Lobby Buttons

CMaterial VMaterialLoader::materialButtonLobbyJoinGame;
CMaterial VMaterialLoader::materialButtonLobbyJoinGameHover;
CMaterial VMaterialLoader::materialButtonLobbyHostGame;
CMaterial VMaterialLoader::materialButtonLobbyHostGameHover;



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

CMaterial VMaterialLoader::materialButtonAbort;
CMaterial VMaterialLoader::materialButtonAbortHover;


//Ingame
CMaterial VMaterialLoader::materialIngameMenueDialogBackground;
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

//Sabotage
CMaterial VMaterialLoader::materialSabotageButtonScissors;
CMaterial VMaterialLoader::materialSabotageButtonStrike;
CMaterial VMaterialLoader::materialSabotageButtonBomb;

CMaterial VMaterialLoader::materialSabotageButtonScissorsHover;
CMaterial VMaterialLoader::materialSabotageButtonStrikeHover;
CMaterial VMaterialLoader::materialSabotageButtonBombHover;

//Icons
CMaterial VMaterialLoader::materialIngameIconPopulation;
CMaterial VMaterialLoader::materialIngameIconMoney;

//WritingFont
CWritingFont VMaterialLoader::standardFont;
CWritingFont VMaterialLoader::GoldFont;

//Trassentexturen
CMaterial VMaterialLoader::m_zmConcrete;
CMaterial VMaterialLoader::m_zmStrut;
CMaterial VMaterialLoader::m_zmIsolator;
CMaterial VMaterialLoader::m_zmRing;
CMaterial VMaterialLoader::m_zmCable;

//Windkraftwerktexturen
CMaterial VMaterialLoader::m_zmWindGrund;
CMaterial VMaterialLoader::m_zmWindrad;

//Solarkraftwerktexturen
CMaterial VMaterialLoader::m_zmSolarzelle;
CMaterial VMaterialLoader::m_zmSolarGrund;
CMaterial VMaterialLoader::m_zmSolarLOD;

//Atomkraftwerktexturen
CMaterial VMaterialLoader::m_zmAtomGrund;
CMaterial VMaterialLoader::m_zmAtomSchranke;
CMaterial VMaterialLoader::m_zmAtomZaun;
CMaterial VMaterialLoader::m_zmAtomReaktor;

//Atomkraftwerktexturen
CMaterial VMaterialLoader::m_zmAtomgrundWhite;
CMaterial VMaterialLoader::m_zmAtomgrundGrey;
CMaterial VMaterialLoader::m_zmSchranke;
CMaterial VMaterialLoader::m_zmAtomgrundGreen;
CMaterial VMaterialLoader::m_zmHolz;

//Oelkraftwerktexturen
CMaterial VMaterialLoader::m_zmOelGrund;
CMaterial VMaterialLoader::m_zmOelSchranke;
CMaterial VMaterialLoader::m_zmOelZaun;
CMaterial VMaterialLoader::m_zmOelGelbstahl;
CMaterial VMaterialLoader::m_zmOelGruenstahl;

//Umspannwerktexturen
CMaterial VMaterialLoader::m_zmUmspannBoden;
CMaterial VMaterialLoader::m_zmUmspannGrund;
CMaterial VMaterialLoader::m_zmUmspannIsolator;
CMaterial VMaterialLoader::m_zmUmspannLeitung;

//Kohlekraftwerktexturen
CMaterial VMaterialLoader::m_zmKohleBerg;
CMaterial VMaterialLoader::m_zmKohle;
CMaterial VMaterialLoader::m_zmKohleHolz;
CMaterial VMaterialLoader::m_zmKohleLore;
CMaterial VMaterialLoader::m_zmKohleBlack;

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

//Test
CMaterial VMaterialLoader::materialAnimationsVersuch;

//Animierte Texturen
CMaterial VMaterialLoader::materialAnimSabotageBomb;

void VMaterialLoader::setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName)
{
	std::string textureDiffuse = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_diffuse.png");
	std::string textureSpecular = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_specular.png");
	std::string textureBump = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_bump.png");
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureBump(const_cast<char*>(textureBump.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureBump(const_cast<char*>(textureBump.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureBump(const_cast<char*>(textureBump.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].SetTextureSpecularBlack();
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].SetTextureSpecularBlack();
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].SetTextureSpecularBlack();
	//fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	//fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	//fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
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
	materialButtonAbort.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort.png");
	materialButtonAbortHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort_hover.png");

	//MainMenue Background
	materialMainMenueBackground.MakeTextureSprite("textures/gui/background/wasserkraftwerk.png");

	//Lobby Buttons
	materialButtonLobbyJoinGame.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGame.png");
	materialButtonLobbyJoinGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGameHover.png");
	materialButtonLobbyHostGame.MakeTextureSprite("textures/gui/Buttons/ButtonHostGame.png");
	materialButtonLobbyHostGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonHostGameHover.png");
		

	//Interface - Background
	materialTopbar.MakeTextureSprite("textures\\topbar.png");
	materialBottombarBorderTop.MakeTextureSprite("textures\\bottombarBorderTopBlue.png");
	materialVerticalBorder.MakeTextureSprite("textures\\VerticalBorder.png");
	materialLobbyBigDialog.MakeTextureSprite("textures\\LobbyBigDialog.png");
	materialBuildingButton.MakeTextureSprite("textures\\BuildingButton.png");
	materialBuildingButtonHover.MakeTextureSprite("textures\\BuildingButtonHover.png");
	materialIngameMenueDialogBackground.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_MenueDialog_Background.png");
	materialWhiteGreyBackground.MakeTextureSprite("textures/gui/background/gui_background_whitegrey.png");

	//Interface - Selection Buttons
	materialIngameButtonCraftmenu.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu.png");
	materialIngameButtonCraftmenuHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu_hover.png");
	materialIngameButtonSabotage.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage.png");
	materialIngameButtonSabotageHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage_hover.png");
	materialIngameButtonStatistics.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics.png");
	materialIngameButtonStatisticsHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics_hover.png");

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
	materialSabotageButtonBomb.MakeTextureSprite("Textures/gui/Buttons/gui_ingame_bomb.png");
	
	materialSabotageButtonScissorsHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_scissorsHover.png");
	materialSabotageButtonStrikeHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_strikeHover.png");
	materialSabotageButtonBombHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_bombHover.png");

	//Test
	materialRed.MakeTextureSprite("textures\\red_image.jpg");
	materialBlue.MakeTextureSprite("textures\\blue_image.jpg");
	materialGreen.MakeTextureSprite("textures\\green_image.jpg");
	materialLightGrey.MakeTextureSprite("textures\\lightgrey_image.png");

	materialAnimationsVersuch.MakeTextureSprite("textures/fonts/FontArialShadow.png");
	materialAnimationsVersuch.SetAni(16, 16, 0.5);

	//Fonts
	//standardFont.Init("textures/fonts/FontArialShadow.png",false);
	//standardFont.SetTableSize(16, 16);
	standardFont.Init("textures/fonts/SystematicJ.png", false);
	standardFont.SetTableSize(16,16);
	GoldFont.Init("textures/fonts/FontArialShadowGold.png", false);
	GoldFont.SetTableSize(16, 16);
	standardFont.SetTransparencyOn();
	GoldFont.SetTransparencyOn();
	//Building - Trasse
	m_zmConcrete.MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse.png");
	m_zmConcrete.MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	m_zmConcrete.MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");

	m_zmStrut.MakeTextureDiffuse("textures/buildings/strommast_diffuse.png");
	m_zmIsolator.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmRing.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmCable.MakeTextureDiffuse("textures\\white_image.jpg");

	//Windkraftwerktexturen
	m_zmWindGrund.MakeTextureDiffuse("textures\\Powerplants\\Beton.png");
	m_zmWindrad.MakeTextureDiffuse("textures\\Powerplants\\Metall_Fassade.jpg");
	m_zmWindGrund.SetTextureSpecularAsDiffuse();

	//Solarkraftwerktexturen
	m_zmSolarGrund.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmSolarzelle.MakeTextureDiffuse("textures\\buildings\\SolarPanel_diffuse.jpg");
	m_zmSolarzelle.MakeTextureBump("textures\\buildings\\SolarPanel_bump.jpg");
	m_zmSolarLOD.MakeTextureDiffuse("textures\\SolarLOD.jpg");

	//Atomkraftwerktexturen
	m_zmAtomGrund.MakeTextureDiffuse("textures\\Powerplants\\Beton.png");
	m_zmAtomSchranke.MakeTextureDiffuse("textures\\Powerplants\\Schranke.jpg");
	m_zmAtomZaun.MakeTextureDiffuse("textures\\Powerplants\\Holz.jpg");
	m_zmAtomReaktor.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmAtomGrund.SetTextureSpecularAsDiffuse();
	m_zmAtomSchranke.SetTextureSpecularAsDiffuse();
	m_zmAtomZaun.SetTextureSpecularAsDiffuse();

	//Atomkraftwerktexturen
	m_zmAtomgrundWhite.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmAtomgrundGrey.MakeTextureDiffuse("Textures\\grey_image.jpg");
	m_zmSchranke.MakeTextureDiffuse("Textures\\schranke.jpg");
	m_zmAtomgrundGreen.MakeTextureDiffuse("Textures\\green_image.jpg");
	m_zmHolz.MakeTextureDiffuse("Textures\\Holz.JPG");

	//Oelkraftwerktexturen
	m_zmOelGrund.MakeTextureDiffuse("textures\\Powerplants\\Beton.png");
	m_zmOelSchranke.MakeTextureDiffuse("textures\\Powerplants\\Schranke.jpg");
	m_zmOelZaun.MakeTextureDiffuse("textures\\Powerplants\\Holz.jpg");
	m_zmOelGelbstahl.MakeTextureDiffuse("textures\\Powerplants\\Gelbstahl.png");
	m_zmOelGruenstahl.MakeTextureDiffuse("textures\\Powerplants\\Gruenstahl.png");
	m_zmOelGrund.SetTextureSpecularAsDiffuse();
	m_zmAtomSchranke.SetTextureSpecularAsDiffuse();
	m_zmAtomZaun.SetTextureSpecularAsDiffuse();

	//Umspannwerktexturen
	m_zmUmspannBoden.MakeTextureDiffuse("textures\\Powerplants\\Beton.png");
	m_zmUmspannGrund.MakeTextureDiffuse("textures\\Powerplants\\Gruenstahl.png");
	m_zmUmspannIsolator.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmUmspannLeitung.MakeTextureDiffuse("textures\\Powerplants\\Grau.jpg");
	m_zmUmspannBoden.SetTextureSpecularAsDiffuse();

	//Kohlekraftwerktexturen
	m_zmKohle.MakeTextureDiffuse("Textures\\kohle_image.jpg");
	m_zmKohleBerg.MakeTextureDiffuse("Textures\\berg_image.jpg");
	m_zmKohleHolz.MakeTextureDiffuse("Textures\\holz_image.jpg");
	m_zmKohleLore.MakeTextureDiffuse("Textures\\lore_image.jpg");
	m_zmKohleBlack.MakeTextureDiffuse("Textures\\black_image.jpg");
	m_zmKohleBerg.SetTextureSpecularAsDiffuse();
	
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

	//Cursor
	m_zmDefaultCursor.MakeTextureSprite("textures\\gui\\default_zeiger.png");
	m_zmHammerCursor.MakeTextureSprite("textures\\gui\\Hammer.png");
	m_zmDefaultCursor.SetTransparencyOn();
	m_zmHammerCursor.SetTransparencyOn();

	//CraftMenue
	m_zmCraftMenueBackground.MakeTextureSprite("textures/gui/background/gui_ingame_baumenu.png");

	//Infofield
	materialInfofieldBackground.MakeTextureSprite("textures/gui/background/gui_ingame_infofield.png");

	//Minimap
	materialMinimapBackground.MakeTextureSprite("textures/gui/background/gui_ingame_minimap.png");

	//Icons
	materialIngameIconPopulation.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_Icon_Population.png");
	materialIngameIconMoney.MakeTextureSprite("textures/gui/interface/texture_gui_ingame_Icon_Money.png");

	//Default Background
	materialDefaultBackground.MakeTextureSprite("textures/gui/interface/texture_gui_background_lightgrey.png");

	//CityBuildings

	materialBuilding01.MakeTextureDiffuse("textures\\buildings\\Hauswand_3.png");
	materialBuilding01.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialBuilding01.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialBuilding02.MakeTextureDiffuse("textures\\buildings\\texture_concrete_diffuse.png");
	materialBuilding02.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialBuilding02.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialBuilding03.MakeTextureDiffuse("textures\\buildings\\Hauswand_4.png");
	materialBuilding03.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialBuilding03.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");
	
	materialAppartments.MakeTextureDiffuse("textures\\buildings\\Hauswand_2.png");
	materialAppartments.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialAppartments.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialLargeOfficeBuilding.MakeTextureDiffuse("textures\\buildings\\Hauswand_2.png");
	materialLargeOfficeBuilding.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialBuilding03.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialOfficTowerViewingDeck.MakeTextureDiffuse("textures\\buildings\\Hauswand_1.png");
	materialOfficTowerViewingDeck.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialOfficTowerViewingDeck.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialSmallOfficeBuilding.MakeTextureDiffuse("textures\\buildings\\Hauswand_4.png");
	materialSmallOfficeBuilding.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialSmallOfficeBuilding.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");

	materialTwistedTower.MakeTextureDiffuse("textures\\buildings\\texture_concrete_diffuse.png");
	materialTwistedTower.MakeTextureBump("textures\\buildings\\texture_concrete_normal.png");
	materialTwistedTower.MakeTextureSpecular("textures\\buildings\\texture_concrete_specular.png");
	

	//Animierte Texturen
	materialAnimSabotageBomb.MakeTextureSprite("textures/gui/animiert/Bombe.png");
	materialAnimSabotageBomb.SetAni(8, 2, 1);
	//materialAnimSabotageBomb.MakeTextureSprite("textures/fonts/FontArialShadow.png");
	//materialAnimSabotageBomb.SetAni(16, 16, 1);

	//Background
	materialLobbyRunningGamesBackground.MakeTextureSprite("textures/gui/background/gui_lobby_RunningGamesBackround.png");
	materialLobbyGamelistBackground.MakeTextureSprite("textures/gui/background/ListView.png");
	materialListEntryBackground.MakeTextureSprite("textures/gui/background/gui_ListEntry.png");
	materialListEntryHoverBackground.MakeTextureSprite("textures/gui/background/gui_ListEntryHover.png");
}

//Rotation adjustments
float VMaterialLoader::getRotationPerTick(const VIdentifier::VIdentifier powerPlant, const float fTimeDelta)
{
	switch (powerPlant)
	{
		//case VIdentifier::VCoalPowerPlant: break;
		//case VIdentifier::VHydroelectricPowerPlant: break;
		case VIdentifier::VWindmillPowerPlant: return CASTS<float>((2.0 * M_PI / 2.0) * fTimeDelta);	//Number of seconds per rotation
		case VIdentifier::VSolarPowerPlant: return CASTS<float>((2.0 * M_PI / 4.0) * fTimeDelta);
		case VIdentifier::VOilRefinery: return CASTS<float>((2.0 * M_PI / 8.0) * fTimeDelta);
		//case VIdentifier::VNuclearPowerPlant: break;
		default:
			ASSERT("No Rotation for this power plant available");
			return 1.0;
	}
}

NAMESPACE_VIEW_E
