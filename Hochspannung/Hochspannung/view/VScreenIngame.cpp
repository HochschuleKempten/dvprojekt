#include "VScreenIngame.h"
#include "VMaster.h"
#include "VText.h"
NAMESPACE_VIEW_B

VScreenIngame::VScreenIngame()
{
}
VScreenIngame::VScreenIngame(CFrame* frame, CRoot* root, CScene* scene, CPlacement* camplacement)
{
	m_viewport = new CViewport();
	//Standard Init
	m_scene = scene;
	m_zpCamera = camplacement;
	m_zc.Init();
	m_viewport->InitFull(&m_zc);
	
	//Minimap
	m_CamMiniMap.Init();
	
	m_scene->AddPlacement(&m_zpMinimapCam);
	m_zpMinimapCam.AddCamera(&m_CamMiniMap);
	
	m_CamMiniMap.SetOrthoOn();
	m_CamMiniMap.SetFov(1.5);
	m_zpMinimapCam.TranslateZ(10);
	m_zpMinimapCam.Scale(50);
	m_zpMinimapCam.RotateXDelta(0);
	m_minimap.Init(&m_CamMiniMap, CFloatRect(0.8, 0.765, 0.195, 0.23));
	
	frame->AddViewport(m_viewport);
	frame->AddViewport(&m_minimap);
	
	//Scene "3D-World"
	root->AddScene(scene);
	m_zb.InitFull("textures/black_image.jpg");
	m_viewport->AddBackground(&m_zb);
	
	m_scene->AddPlacement(m_zpCamera);
	m_zpCamera->AddCamera(&m_zc);

	m_zpCamera->TranslateZ(50.0);
	m_zpCamera->RotateXDelta(0.15 * PI);
	m_zpCamera->RotateZDelta(0.15);

	m_scene->AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
		CColor(1.0f, 1.0f, 1.0f));

	
	
	

	//Bottom Bar

	/*m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport->AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);*/

	
	
	/********************************************************TOP AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.2, 0.0, 0.6, 0.05),&VMaterialLoader::materialTopbar, "Topbar");
	getContainer("Topbar")->addText(CFloatRect(0.05, 0.2, 0.2, 0.7), &VMaterialLoader::standardFont, "Bevoelkerung:", "population");
	getContainer("Topbar")->addText(CFloatRect(0.251, 0.2, 0.2, 0.65), &VMaterialLoader::standardFont, "0000", "popValue");
	getContainer("Topbar")->addText(CFloatRect(0.55, 0.2, 0.2, 0.65), &VMaterialLoader::GoldFont, "Geld:", "money");
	getContainer("Topbar")->addText(CFloatRect(0.751, 0.2, 0.2, 0.65), &VMaterialLoader::GoldFont, "0000", "moneyValue");


	/********************************************************BOTTOM AREA*************************************************************/
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0, 0.75F, 1.0F, 0.25F), "BottomBar");
	
	getContainer("BottomBar")->addOverlay(CFloatRect(0.0, 0.0, 1, 0.05), &VMaterialLoader::materialBottombarBorderTop, false,"BottomTopBorder");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.0, 0.95, 1, 0.05), &VMaterialLoader::materialBottombarBorderTop, false, "BottomBottomBorder");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.0, 0.05, 0.01, 0.95), &VMaterialLoader::materialVerticalBorder, false, "BottomLeftBorder");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.21, 0.05, 0.01, 0.95), &VMaterialLoader::materialVerticalBorder, false, "BottomMenueInfofeldBorder");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.73, 0.05, 0.01, 0.95), &VMaterialLoader::materialVerticalBorder, false, "BottomMenueSeperatorMenueEnergy");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.79, 0.05, 0.01, 0.95), &VMaterialLoader::materialVerticalBorder, false, "BottomMenueSeperatorEnergyMinimap");
	getContainer("BottomBar")->addOverlay(CFloatRect(0.99, 0.05, 0.01, 0.95), &VMaterialLoader::materialVerticalBorder, false, "BottomMenueLeftBorder");

	//Baumenü Register
	
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::Register, CFloatRect(0.22, 0.05F, 0.51F, 0.90F), "Register");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonCraftmenu,
		&VMaterialLoader::materialIngameButtonCraftmenuHover, &VMaterialLoader::materialRed, SWITCH_TO_REGISTER_BUILDING, "TabBuilding");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonSabotage,
		&VMaterialLoader::materialIngameButtonSabotageHover, &VMaterialLoader::materialGreen, SWITCH_TO_REGISTER_SABOTAGE, "TabSabotage");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonStatistics,
		&VMaterialLoader::materialIngameButtonStatisticsHover, &VMaterialLoader::materialBlue, SWITCH_TO_REGISTER_STATISTICS, "TabStatistics");

	
	//CraftMenu
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.025, 0.075, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonWindmill, &VMaterialLoader::materialCraftmenuButtonWindmillHover, SELECT_BUILDING_WINDMILL, "windmill");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.275, 0.075, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, &VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover, SELECT_BUILDING_HYDROPOWERPLANT, "hydroPowerPlant");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.525, 0.075, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, &VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover, SELECT_BUILDING_SOLARPOWERPLANT, "solarPowerPlant");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.025, 0.525, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, &VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover, SELECT_BUILDING_NUCLEARPOWERPLANT, "nuclearPowerPlant");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.275, 0.525, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, &VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover, SELECT_BUILDING_COALPOWERPLANT, "coalPowerPlant");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.525, 0.525, 0.2, 0.4), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, &VMaterialLoader::materialCraftmenuButtonOilPowerplantHover, SELECT_BUILDING_OILPOWERPLANT, "oilPowerPlant");
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.775, 0.525, 0.20, 0.4), &VMaterialLoader::materialCraftmenuButtonPowerline, &VMaterialLoader::materialCraftmenuButtonPowerlineHover, SELECT_BUILDING_POWERLINE, "powerLine");

	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
	dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabStatistics")->switchOff();


	/********************************************************Infofield AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.01, 0.05F, 0.20F, 1.0F), &VMaterialLoader::materialBlue, "Infofield");
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.01, 0.3, 0.80, 0.1), &VMaterialLoader::standardFont, "Infofeld", "infoText");
	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText")->setLayer(0.2);
	getContainer("BottomBar")->getContainer("Infofield")->setLayer(0.2);
	
	
	/***********************************************************Dialog******************************************************************/
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.10, 0.30, 0.55),&VMaterialLoader::materialDialogBackground, "DialogBox");
	

	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.10, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING,"MenueButtonContinue");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.27, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME,"MenueButtonQuit");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.44, 0.80, 0.15), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "MenueButtonBack");
	

	/********************************************************Energy AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.74, 0.03F, 0.05F, 1.0F), &VMaterialLoader::materialGreen, "Energy");
	getContainer("BottomBar")->getContainer("Energy")->addOverlay(CFloatRect(0.5, 0.4, 0.5, 0.6), &VMaterialLoader::materialRed, false, "NeededEnergy");
	getContainer("BottomBar")->getContainer("Energy")->setLayer(0.3);


	m_viewport->SwitchOff();
getContainer("DialogBox")->switchOff();

}

VScreenIngame::~VScreenIngame()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;
}

void VScreenIngame::onNotify(Event events)
{
	switch (events)
	{
	case SWITCH_TO_REGISTER_BUILDING:
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->switchOn();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
		break;
	case SWITCH_TO_REGISTER_SABOTAGE:
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->switchOff();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabSabotage")->switchOn();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
		break;
	case SWITCH_TO_REGISTER_STATISTICS:
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->switchOff();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
		dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabStatistics")->switchOn();
		break;
	default:
		notify(events);
		break;
	}
}


void VScreenIngame::switchOn()
{
	m_viewport->SwitchOn();
	//m_minimap.SwitchOn();
	m_scene->SwitchOn();
	
	m_isOn = true;
}
void VScreenIngame::switchOff()
{
	m_viewport->SwitchOff();
	m_minimap.SwitchOff();
	m_scene->SwitchOff();
	m_isOn = false;
}

void VScreenIngame::checkShortcut(CDeviceKeyboard* keyboard)
{
	

	if (!keyboard->KeyPressed(DIK_ESCAPE))
	{
		bK = false;
	}
	if (keyboard->KeyPressed(DIK_ESCAPE) && bK == false)
	{
		if (!getContainer("DialogBox")->isOn())
		{
			getContainer("DialogBox")->switchOn();
		}
		else
		{
			getContainer("DialogBox")->switchOff();
		}
		bK = true;
	}
	
}

	void VScreenIngame::checkSpecialEvent(CDeviceCursor* cursor)
	{/*
		static string hover = "Hover Windmill";
		static string standard = "infofeld";
		float curPosX;
		float curPosY;
		cursor->GetFractional(curPosX, curPosY);
		if (dynamic_cast<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("windmill")->checkHover(curPosX, curPosY))
		{
			
			updateInfofeld(hover);
		}
		else
			updateInfofeld(standard);*/
	}

	void VScreenIngame::updateMoney(const int wert)
	{
		dynamic_cast<VText*>(getContainer("Topbar")->getGuiObject("moneyValue"))->updateText(std::to_string(wert));
	}

	void VScreenIngame::updatePopulation(const int wert)
	{
		dynamic_cast<VText*>(getContainer("Topbar")->getGuiObject("popValue"))->updateText(std::to_string(wert));
	}

	void VScreenIngame::updateInfofeld(string& neuerText)
	{
		dynamic_cast<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText"))->updateText(neuerText);
	}

	CFloatRect VScreenIngame::getTopSpace()
	{
		return getContainer("Topbar")->getRectangle();
	}

	CFloatRect VScreenIngame::getBottomSpace()
	{
		return getContainer("BottomBar")->getRectangle();
	}

	NAMESPACE_VIEW_E