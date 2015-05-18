#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"
#include "../logic/LPlayer.h"

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

	static void setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName);

public:
	static void init();

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

	//Ingame
	static CMaterial materialIngameCraft;
	static CMaterial materialIngameBorder;
	static CMaterial materialTopbar;
	static CMaterial materialBottombarBorderTop;
	static CMaterial materialVerticalBorder;
	static CMaterial materialLobbyBigDialog;
	static CMaterial materialBuildingButton;
	static CMaterial materialBuildingButtonHover;


	//Backgrounds
	static CMaterial materialDialogBackground;
	static CMaterial materialIngameMenueDialogBackground;
	static CMaterial materialDefaultBackground;
	static CMaterial materialWhiteGreyBackground;

	//Icons
	static CMaterial materialIngameIconPopulation;
	static CMaterial materialIngameIconMoney;

	//Buttons
	static CMaterial materialIngameButtonCraftmenu;
	static CMaterial materialIngameButtonSabotage;
	static CMaterial materialIngameButtonStatistics;
	static CMaterial materialIngameButtonCraftmenuHover;
	static CMaterial materialIngameButtonSabotageHover;
	static CMaterial materialIngameButtonStatisticsHover;
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
	
	//Infofield
	static CMaterial materialInfofieldBackground;

	//Minimap
	static CMaterial materialMinimapBackground;

	//Allgemein
	//Buttons
	static CMaterial materialButtonBack;
	static CMaterial materialButtonBackHover;

	static CMaterial materialRed;
	static CMaterial materialBlue;
	static CMaterial materialGreen;

	//WritingFonts
	static CWritingFont standardFont;
	static CWritingFont GoldFont;
	
	//Trassentexturen
	static CMaterial m_zmConcrete;
	static CMaterial m_zmStrut;
	static CMaterial m_zmIsolator;
	static CMaterial m_zmRing;
	static CMaterial m_zmCable;

	//Solarkraftwerktexturen
	static CMaterial m_zmSolarzelle;
	static CMaterial m_zmSolarGrund;
	static CMaterial m_zmSolarLOD;

	//Atomkraftwerktexturen
	static CMaterial m_zmAtomgrundWhite;
	static CMaterial m_zmAtomgrundGrey;
	static CMaterial m_zmSchranke;
	static CMaterial m_zmAtomgrundGreen;
	static CMaterial m_zmHolz;


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
};


NAMESPACE_VIEW_E
