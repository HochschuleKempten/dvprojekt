#pragma once

#include "VGeneral.h"
#include "../logic/LField.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
private:
	VMaterialLoader() = delete;
	VMaterialLoader(const VMaterialLoader&) = delete;
	VMaterialLoader(const VMaterialLoader&&) = delete;
	VMaterialLoader operator=(const VMaterialLoader&) = delete;
	VMaterialLoader operator=(const VMaterialLoader&&) = delete;
	~VMaterialLoader() = delete;

public:
	static void init();

	using FieldPair = std::pair<LField::FieldType, LField::FieldLevel>;
	static std::map<FieldPair, CMaterial> fieldMaterials;

	static CMaterial materialCoalPowerPlant;
	static CMaterial materialHydroelectricPowerPlant;
	
	//MainMenue
	static CMaterial materialMainMenue;
	static CMaterial materialMainMenueHover;
		//Buttons
	static CMaterial materialButtonMainMenueNeuesSpiel;
	static CMaterial materialButtonMainMenueNeuesSpielHover;
	static CMaterial materialButtonMainMenueOptionen;
	static CMaterial materialButtonMainMenueOptionenHover;
	static CMaterial materialButtonMainMenueCredits;
	static CMaterial materialButtonMainMenueCreditsHover;
	static CMaterial materialButtonMainMenueSpielBeenden;
	static CMaterial materialButtonMainMenueSpielBeendenHover;
	static CMaterial materialButtonMainMenueEinzelspieler;
	static CMaterial materialButtonMainMenueEinzelspielerHover;
	static CMaterial materialButtonMainMenueMehrspieler;
	static CMaterial materialButtonMainMenueMehrspielerHover;

	//Ingame
	static CMaterial materialIngameCraft;
	static CMaterial materialDialogBackground;
	static CMaterial materialIngameBorder;
	static CMaterial materialTopbar;
	static CMaterial materialBottombarBorderTop;
	static CMaterial materialVerticalBorder;
	static CMaterial materialLobbyBigDialog;
	static CMaterial materialBuildingButton;
	static CMaterial materialBuildingButtonHover;

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
	
};


NAMESPACE_VIEW_E
