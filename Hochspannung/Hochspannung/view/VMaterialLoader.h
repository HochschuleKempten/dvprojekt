#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class VMaterialLoader
{
private:
	VMaterialLoader()
	{}
	~VMaterialLoader()
	{}

public:
	static void init();

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

	//Allgemein
		//Buttons
	static CMaterial materialButtonBack;
	static CMaterial materialButtonBackHover;
	
};


NAMESPACE_VIEW_E
