#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
public:
	enum Model
	{
		COAL_MOUNTAIN,
		COAL_STRUCTURE,
		COAL_WOOD,
		COAL_WAGON,
		COAL_BLACK,
		COAL_GREY,
		POWERLINE_STRUT,
		POWERLINE_ISOLATOR,
		POWERLINE_RING,
		POWERLINE_CABLE,
		TRANSFORMERSTATION_BETON,
		TRANSFORMERSTATION_BETON_LIGHT,
		TRANSFORMERSTATION_ISOLATOR,
		TRANSFORMERSTATION_WIRE,
		SOLAR_FLOOR,
		SOLAR_CELL,
		SOLAR_CELLS_LOD,
		WIND_RAD,
		WIND_FLUEGEL1,
		WIND_FLUEGEL2,
		WIND_FLUEGEL3,
		WATER_HOLZ,
		NUCLEAR_FLOOR,
		NUCLEAR_GATE,
		NUCLEAR_FENCE,
		NUCLEAR_REACTOR,
		OIL_FLOOR,
		OIL_GATE,
		OIL_FENCE,
		OIL_GREEN_RAY,
		OIL_YELLOW_RAY,
		BUILDING_WALLFRAME,
		BUILDING_WINDOW,
		BUILDING_BROWN_WALL
	};

private:
	VMaterialLoader() = delete;
	VMaterialLoader(const VMaterialLoader&) = delete;
	VMaterialLoader(const VMaterialLoader&&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&&) = delete;
	~VMaterialLoader() = delete;

	DEBUG_EXPRESSION(static bool initDone);

	static void setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName);
	static void setPowerPlantMaterialHelper(const Model materialPowerPlant, const std::string& textureName);

private:
	static std::unordered_map<Model, CMaterial> materialsModelsSwitchedOn;
	static std::unordered_map<Model, CMaterial> materialsModelsSwitchedOff;
	static CColor colorAmbientOn;
	static CColor colorAmbientOff;

public:
	//Rotation adjustments
	static float getRotationPerTick(const VIdentifier::VIdentifier powerPlant, const float fTimeDelta);
	static void init();
	static CMaterial* getMaterialModel(const Model materialPowerPlant, const bool switchedOn);

public:
	using FieldPair = std::pair<LField::FieldType, LField::FieldLevel>;
	static std::map<FieldPair, CMaterial> fieldMaterials;

	static CMaterial materialCoalPowerPlant;
	static CMaterial materialHydroelectricPowerPlant;

	//MainMenue
	static CMaterial materialMainMenue;
	static CMaterial materialMainMenueHover;
	static CMaterial materialMainMenueBackground;

	//Buttons
	static CMaterial materialButtonMainMenueNeuesSpiel;
	static CMaterial materialButtonMainMenueNeuesSpielHover;
	static CMaterial materialButtonMainMenueOptionen;
	static CMaterial materialButtonMainMenueOptionenHover;
	static CMaterial materialButtonMainMenueCredits;
	static CMaterial materialButtonMainMenueCreditsHover;
	static CMaterial materialButtonMainMenueSpielBeenden;
	static CMaterial materialButtonMainMenueSpielBeendenHover;
	static CMaterial materialButtonLobbyJoinGame;
	static CMaterial materialButtonLobbyJoinGameHover;
	static CMaterial materialButtonLobbyHostGame;
	static CMaterial materialButtonLobbyHostGameHover;
	static CMaterial materialButtonAbort;
	static CMaterial materialButtonAbortHover;
	static CMaterial materialButtonRefresh;
	static CMaterial materialButtonRefreshHover;
	static CMaterial materialButtonGameContinue;
	static CMaterial materialButtonGameContinueHover;

	//Ingame
	static CMaterial materialIngameCraft;
	static CMaterial materialIngameBorder;
	static CMaterial materialTopbar;
	static CMaterial materialBottombarBorderTop;
	static CMaterial materialVerticalBorder;
	static CMaterial materialLobbyBigDialog;

	//Credits
	static CMaterial materialCreditsOrganization;
	static CMaterial materialCreditsIntegration;
	static CMaterial materialCreditsTextures;
	static CMaterial materialCreditsNetwork;
	static CMaterial materialCreditsLogic;
	static CMaterial materialCreditsUI;
	static CMaterial materialCreditsModelling;
	static CMaterial materialCreditsModelling2;
	static CMaterial materialCreditsVektoriaSplash;

	//Backgrounds
	static CMaterial materialDialogBackground;
	static CMaterial materialIngameMenueDialogBackground;
	static CMaterial materialDefaultBackground;
	static CMaterial materialWhiteGreyBackground;
	static CMaterial materialLobbyRunningGamesBackground;
	static CMaterial materialLobbyGamelistBackground;
	static CMaterial materialListEntryBackground;
	static CMaterial materialListEntryHoverBackground;
	static CMaterial materialTextfieldBackground;
	static CMaterial materialTextfieldHoverBackground;
	static CMaterial materialErrorBackground;
	static CBackground materialIngameBackground;

	//Icons
	static CMaterial materialIngameIconPopulation;
	static CMaterial materialIngameIconMoney;
	static CMaterial materialIngameIconEnergy;
	

	//Buttons
	static CMaterial materialIngameButtonCraftmenu;
	static CMaterial materialIngameButtonSabotage;
	static CMaterial materialIngameButtonStatistics;
	static CMaterial materialIngameButtonCraftmenuHover;
	static CMaterial materialIngameButtonSabotageHover;
	static CMaterial materialIngameButtonStatisticsHover;
	static CMaterial materialIngameButtonCraftmenuActive;
	static CMaterial materialIngameButtonSabotageActive;
	static CMaterial materialIngameButtonStatisticsActive;

	//Craftmenu
	static CMaterial materialCraftmenuButtonWindmill;
	static CMaterial materialCraftmenuButtonHydroPowerplant;
	static CMaterial materialCraftmenuButtonSolarPowerplant;
	static CMaterial materialCraftmenuButtonCoalPowerplant;
	static CMaterial materialCraftmenuButtonOilPowerplant;
	static CMaterial materialCraftmenuButtonNuclearPowerplant;
	static CMaterial materialCraftmenuButtonPowerline;
	static CMaterial materialCraftmenuButtonWindmillHover;
	static CMaterial materialCraftmenuButtonHydroPowerplantHover;
	static CMaterial materialCraftmenuButtonSolarPowerplantHover;
	static CMaterial materialCraftmenuButtonCoalPowerplantHover;
	static CMaterial materialCraftmenuButtonOilPowerplantHover;
	static CMaterial materialCraftmenuButtonNuclearPowerplantHover;
	static CMaterial materialCraftmenuButtonPowerlineHover;
	
	//Sabotage
	static CMaterial materialSabotageButtonScissors;
	static CMaterial materialSabotageButtonStrike;
	static CMaterial materialSabotageButtonHalf;
	static CMaterial materialSabotageButtonPowerOn;
	static CMaterial materialSabotageButtonPowerOff;
	static CMaterial materialSabotageButtonSell;

	static CMaterial materialSabotageButtonScissorsHover;
	static CMaterial materialSabotageButtonStrikeHover;
	static CMaterial materialSabotageButtonHalfHover;
	static CMaterial materialSabotageButtonPowerOnHover;
	static CMaterial materialSabotageButtonPowerOffHover;
	static CMaterial materialSabotageButtonSellHover;

	//Statistics
	static CMaterial VMaterialLoader::materialFossile;
	static CMaterial VMaterialLoader::materialLeaf;
	static CMaterial VMaterialLoader::materialBattery;
	static CMaterial VMaterialLoader::materialLeaffossileOwn;
	static CMaterial VMaterialLoader::materialLeaffossileEnemy;

	//Infofield
	static CMaterial materialInfofieldBackground;

	//Minimap
	static CMaterial materialMinimapBackground;

	//Allgemein
	static CMaterial m_zmAllgemeinGreen;

	//Buttons
	static CMaterial materialButtonBack;
	static CMaterial materialButtonBackHover;

	static CMaterial materialButtonOk;
	static CMaterial materialButtonOkHover;

	static CMaterial materialRed;
	static CMaterial materialBlue;
	static CMaterial materialGreen;
	static CMaterial materialLightGrey;
	static CMaterial materialBlack;
	static CMaterial materialFossil;
	static CMaterial materialRegenerative;

	//WritingFonts
	static CWritingFont standardFont;
	static CWritingFont GoldFont;
	static CWritingFont errorFont;

	//Wasserkraftwerk
	static CMaterial m_zmWasser;

	//PlayerColor
	static std::unordered_map<int, CColor> colorPlayers;

	//PlayerFoundations
	static std::unordered_map<int, CMaterial> materialFoundationPlayer;

	//MaterialBuildings
	static CMaterial materialBuilding01;
	static CMaterial materialBuilding03;
	static CMaterial materialAppartments;
	static CMaterial materialOfficTowerViewingDeck;
	static CMaterial materialTwistedTower;
	static CMaterial materialSmallOfficeBuilding;

	// MaterialWindowBuildings
	static CMaterial materialWindowsofBuilding;

	//Cursor
	static CMaterial m_zmDefaultCursor;
	static CMaterial m_zmHammerCursor;

	//CraftMenue
	static CMaterial m_zmCraftMenueBackground;

	//Test
	static CMaterial materialAnimationsVersuch;

	//Animierte Texturen
	static CMaterial materialAnimSabotageBomb;
	static CMaterial materialAnimLoadingCircle;
	static CMaterial materialAnimSabotageHalfResource;
	static CMaterial materialAnimSabotageStrike;
	static CMaterial materialAnimSabotageCutPowerline;
	static CMaterial materialAnimSmokeFast;
	static CMaterial materialAnimSmokeSlow;


	// Animiert Textur für Sabotage Cooldown Infoanzeige
	static CMaterial materialAnimSabotagePowerPlant;
	static int materialAnimSabotagePowerPlant_x;
	static int materialAnimSabotagePowerPlant_y;

	static CMaterial materialAnimTransformerStationLightning;
};


NAMESPACE_VIEW_E
