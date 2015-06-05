#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"
#include "VIdentifier.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
private:
	VMaterialLoader() = delete;
	VMaterialLoader(const VMaterialLoader&) = delete;
	VMaterialLoader(const VMaterialLoader&&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&) = delete;
	VMaterialLoader& operator=(const VMaterialLoader&&) = delete;
	~VMaterialLoader() = delete;

private:
	static void setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName);

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
	static CMaterial materialBuildingButton;
	static CMaterial materialBuildingButtonHover;

	
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

	//Infofield
	static CMaterial materialInfofieldBackground;

	//Minimap
	static CMaterial materialMinimapBackground;

	//Allgemein
	static CMaterial m_zmAtomgrundGreen;
	static CMaterial m_zmHolz;


	//Buttons
	static CMaterial materialButtonBack;
	static CMaterial materialButtonBackHover;

	static CMaterial materialRed;
	static CMaterial materialBlue;
	static CMaterial materialGreen;
	static CMaterial materialLightGrey;

	//WritingFonts
	static CWritingFont standardFont;
	static CWritingFont GoldFont;
	static CWritingFont errorFont;
	
	//Trassentexturen
	static CMaterial m_zmStrut;
	static CMaterial m_zmIsolator;
	static CMaterial m_zmRing;
	static CMaterial m_zmCable;

	//Windkraftwerktexturen
	static CMaterial m_zmWindGrund;
	static CMaterial m_zmWindRad;
	static CMaterial m_zmWindFluegel1;
	static CMaterial m_zmWindFluegel2;
	static CMaterial m_zmWindFluegel3;

	//Solarkraftwerktexturen
	static CMaterial m_zmSolarzelle;
	static CMaterial m_zmSolarGrund;
	static CMaterial m_zmSolarLOD;

	//Atomkraftwerktexturen
	static CMaterial m_zmAtomGrund;
	static CMaterial m_zmAtomSchranke;
	static CMaterial m_zmAtomZaun;
	static CMaterial m_zmAtomReaktor;

	//Atomkraftwerktexturen
	//TODO (V) clean up


	//Oelkraftwerktexturen
	static CMaterial m_zmOelGrund;
	static CMaterial m_zmOelSchranke;
	static CMaterial m_zmOelZaun;
	static CMaterial m_zmOelGelbstahl;
	static CMaterial m_zmOelGruenstahl;

	//Umspannwerktexturen
	static CMaterial m_zmUmspannBoden;
	static CMaterial m_zmUmspannGrund;
	static CMaterial m_zmUmspannIsolator;
	static CMaterial m_zmUmspannLeitung;

	//Kohlekraftwerktexturen
	static CMaterial m_zmKohleBerg;
	static CMaterial m_zmKohle;
	static CMaterial m_zmKohleHolz;
	static CMaterial m_zmKohleLore;
	static CMaterial m_zmKohleBlack;
	static CMaterial m_zmKohlegrundGrey;

	//Wasserkraftwerktexturen
	static CMaterial m_zmWasser;


	//PlayerColor
	static std::unordered_map<int, CColor> colorPlayers;

	//PlayerFoundations
	static std::unordered_map<int, CMaterial> materialFoundationPlayer;

	//MaterialBuildings
	static CMaterial materialBuilding01;
	static CMaterial materialBuilding02;
	static CMaterial materialBuilding03;
	static CMaterial materialLargeOfficeBuilding;
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

	// Animiert Textur für Sabotage Cooldown Infoanzeige
	static CMaterial materialAnimSabotagePowerPlant;
	static int materialAnimSabotagePowerPlant_x;
	static int materialAnimSabotagePowerPlant_y;

	static CMaterial materialAnimTransformerStationLightning;

public:
	//Rotation adjustments
	static float getRotationPerTick(const VIdentifier::VIdentifier powerPlant, const float fTimeDelta);
	static void init();
};


NAMESPACE_VIEW_E
