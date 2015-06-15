#include "VScreenIngame.h"
#include "vMaster.h"
#include "VPlayingField.h"
#include "VText.h"
#include "../logic/LWindmillPowerPlant.h"
#include "../logic/LPowerLine.h"
#include "../logic/LCoalPowerPlant.h"
#include "../logic/LHydroelectricPowerPlant.h"
#include "../logic/LOilRefinery.h"
#include "../logic/LSolarPowerPlant.h"
#include "../logic/LNuclearPowerPlant.h"
#include "../logic/LPlayer.h"
#include "../logic/LBalanceLoader.h"
#include "VSoundLoader.h"
#include "VPowerLine.h"
#include "IViewPowerPlant.h"
#include <thread>

NAMESPACE_VIEW_B


VScreenIngame::VScreenIngame(VUI* vUi)
	: IViewScreen(vUi)
{
	m_viewport = new CViewport();
	
	m_zc.Init();
	m_viewport->AddBackground(&VMaterialLoader::materialIngameBackground);
	m_viewport->InitFull(&m_zc);

	//Detailled model view
	m_zmbackgroundModels.InitFull(&VMaterialLoader::materialLobbyRunningGamesBackground);
	m_CamModels.Init();
	m_zpModels.AddCamera(&m_CamModels);
	m_sceneModels.AddPlacement(&m_zpModels);
	m_zpModels.TranslateZ(10.0f);
	m_zpModels.RotateXDelta(-0.5f);

	//Init models
	modelPowerline.Init(VModelPowerLine::NORTH | VModelPowerLine::EAST | VModelPowerLine::SOUTH | VModelPowerLine::WEST);
	models.emplace(VIdentifier::VWindmillPowerPlant, &modelWindmill);
	models.emplace(VIdentifier::VSolarPowerPlant, &modelSolar);
	models.emplace(VIdentifier::VNuclearPowerPlant, &modelNuclear);
	models.emplace(VIdentifier::VOilRefinery, &modelOil);
	models.emplace(VIdentifier::VPowerLine, &modelPowerline);
	models.emplace(VIdentifier::VHydroelectricPowerPlant, &modelHydroelectric);

	models[VIdentifier::VNuclearPowerPlant]->getPlacementMain()->TranslateZ(10);
	models[VIdentifier::VNuclearPowerPlant]->getPlacementMain()->TranslateYDelta(5);

	models[VIdentifier::VPowerLine]->getPlacementMain()->TranslateZ(12.0F);
	models[VIdentifier::VPowerLine]->getPlacementMain()->TranslateY(2.5F);

	CHVector vector=models[VIdentifier::VNuclearPowerPlant]->getPlacementMain()->GetTranslation();

	CHVector vector2 = m_zpModels.GetTranslation();

	models[VIdentifier::VSolarPowerPlant]->getPlacementMain()->TranslateZ(5.0F);
	models[VIdentifier::VSolarPowerPlant]->getPlacementMain()->TranslateYDelta(2.5F);

	for (const std::pair<VIdentifier::VIdentifier, IViewModel*>& p : models)
	{
		p.second->initViewModel(nullptr);
	}


	//m_zl.Init(CHVector(0.1F, -0.3F, 0.7F),
	//          CColor(0.7F, 0.7F, 0.7F));


	m_zl.Init(CHVector(0.0F, 0.35F, 0.7F),
			  CColor(0.1F, 0.1F, 0.1F));

	m_zlSpot.Init(CColor(0.6f, 0.6f, 0.6f), 0.01f, 0.07f, 0.75f);	//last param = light intensity
	m_zlSpot.SetMaxDistance(2500);
	m_zlSpot.SetMinDistance(40);
	m_zlSpot.SetSoftShadowOn();
	m_zlSpot.SetShadowMapResolution(8192, 8192);
	m_zlSpot.SetRadius(16000);

	m_zpSpot.TranslateZ(900.0f);
	m_zpSpot.TranslateXDelta(700.0f);
	m_zpSpot.TranslateYDelta(-200.0f);
	m_PointingSpot.Init(-3.5f, -5.5f, 0.0f, 1.0f);	//Adjust center of the spot light
	m_zpSpot.SetPointing(&m_PointingSpot);
	m_zpSpot.AddSpotLight(&m_zlSpot);

	m_scene.AddPlacement(&m_zpSpot);
	m_scene.AddParallelLight(&m_zl);
	m_scene.AddPlacement(&m_zpCamera);

	vUi->m_zf.AddViewport(m_viewport);
	vUi->m_zr.AddScene(&m_scene);
	vUi->m_zr.AddScene(&m_sceneModels);

	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.TranslateZ(60.0F);

	m_zpCamera.RotateXDelta(0.20F * PI);

	//m_zpCamera.RotateXDelta(0.40F * PI);


	VSoundLoader::init(&m_scene);
	VSoundLoader::playBackgroundMusicIngame();

	// initialize statistics constants and string mappings for power plants
	m_powerPlantsNameMapping[BUILDING_HYDROPOWERPLANT] = "countHydro";
	m_powerPlantsNameMapping[BUILDING_SOLARPOWERPLANT] = "countSolar";
	m_powerPlantsNameMapping[BUILDING_NUCLEARPOWERPLANT] = "countNuclear";
	m_powerPlantsNameMapping[BUILDING_COALPOWERPLANT] = "countCoal";
	m_powerPlantsNameMapping[BUILDING_OILPOWERPLANT] = "countOil";
	m_powerPlantsNameMapping[BUILDING_WINDMILL] = "countWind";
	m_powerPlantsNameMapping[BUILDING_POWERLINE] = "countPowerline";

	
	/********************************************************TOP AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.1F, 0.0F, 0.8F, 0.05F), &VMaterialLoader::materialTopbar, "Topbar", 0.3F);

	m_vtTopbar = getContainer("Topbar");
	getContainer("Topbar")->addOverlay(CFloatRect(0.05F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconPopulation, "TopPopulationIcon", 0.1F);
	getContainer("Topbar")->addText(CFloatRect(0.151F, 0.2F, 0.2F, 0.6F), &VMaterialLoader::standardFont, "0000", "popValue", 0.1F);

	getContainer("Topbar")->addOverlay(CFloatRect(0.35F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconMoney, "TopMoneyIcon", 0.1F);
	getContainer("Topbar")->addText(CFloatRect(0.451F, 0.2F, 0.2F, 0.6F), &VMaterialLoader::GoldFont, "0000", "moneyValue", 0.1F);

	getContainer("Topbar")->addText(CFloatRect(0.751F, 0.2F, 0.2F, 0.6F), &VMaterialLoader::standardFont, "0000", "energyOverload", 0.1F);
	/********************************************************TOP MESSAGE AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.1F, 0.1F, 0.8F, 0.13F), &VMaterialLoader::materialErrorBackground, "MessageArea", 0.3F);
	getContainer("MessageArea")->addText(CFloatRect(0.1F,0.1F,0.8F,0.3F), &VMaterialLoader::errorFont, "Aktion hier nicht moeglich KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK", "Messagebox", 0.1F,VText::TextMode::CENTERED);
	getContainer("MessageArea")->addText(CFloatRect(0.1F, 0.5F, 0.8F, 0.3F), &VMaterialLoader::errorFont, "Weil das und das passiert ist KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK", "Messagebox2", 0.1F, VText::TextMode::CENTERED);
	
	getContainer("MessageArea")->switchOff();
	/********************************************************BOTTOM AREA*************************************************************/

	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 180, vUi->m_zf.m_iWidthWindow, 180), "BottomBar", 0.9F);


	/********************************************************Infofield AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.00F, 0.00F, 0.22F, 1.0F), &VMaterialLoader::materialInfofieldBackground, "Infofield", 0.3F);


	getContainer("BottomBar")->getContainer("Infofield")->addViewport(&m_viewportModels, &m_CamModels, CFloatRect(0.1F, 0.05F, 0.75F, 0.55F), &m_zmbackgroundModels, "DetailedModels");
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.10F, 0.70F, 0.5F, 0.08F), &VMaterialLoader::standardFont, "100", "PowerInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.10F, 0.85F, 0.5F, 0.08F), &VMaterialLoader::GoldFont, "1000", "MoneyInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->addOverlay(CFloatRect(0.65F, 0.70F, 0.25, 0.08F), &VMaterialLoader::materialIngameIconEnergy, "EngergyInfoIcon", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->addOverlay(CFloatRect(0.65F, 0.85F, 0.25, 0.08F), &VMaterialLoader::materialIngameIconMoney, "MoneyInfoIcon", 0.1F);


	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOff();
	vUi->m_zf.AddViewport(&m_viewportModels);

	/********************************************************Baumenu AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.22F, 0.00F, 0.51F, 1.0F), "Craftmenu", 0.5F);
	getContainer("BottomBar")->getContainer("Craftmenu")->addContainer(IViewGUIContainer::ContainerType::Register, CFloatRect(0.00F, 0.0F, 1.0F, 1.0F), "Register", 0.3F);

	vrRegister = CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"));
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonCraftmenu, &VMaterialLoader::materialIngameButtonCraftmenuHover, &VMaterialLoader::materialIngameButtonCraftmenuActive, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_BUILDING, "TabBuilding", 0.2F);
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonSabotage, &VMaterialLoader::materialIngameButtonSabotageHover, &VMaterialLoader::materialIngameButtonSabotageActive, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_SABOTAGE, "TabSabotage", 0.2F);
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonStatistics, &VMaterialLoader::materialIngameButtonStatisticsHover, &VMaterialLoader::materialIngameButtonStatisticsActive, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_STATISTICS, "TabStatistics", 0.2F);


	// Tabs
	m_vtTabStatistics = CASTD<VRegister*>(vrRegister)->getTab("TabStatistics");
	m_vtTabSabotage = CASTD<VRegister*>(vrRegister)->getTab("TabSabotage");
	m_vtTabBuilding = CASTD<VRegister*>(vrRegister)->getTab("TabBuilding");


	//CraftMenu
	m_vtTabBuilding->addButton(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonWindmill, &VMaterialLoader::materialCraftmenuButtonWindmillHover, SELECT_BUILDING_WINDMILL, "windmill", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, &VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover, SELECT_BUILDING_HYDROPOWERPLANT, "hydroPowerPlant", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, &VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover, SELECT_BUILDING_SOLARPOWERPLANT, "solarPowerPlant", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.025F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, &VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover, SELECT_BUILDING_NUCLEARPOWERPLANT, "nuclearPowerPlant", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.275F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, &VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover, SELECT_BUILDING_COALPOWERPLANT, "coalPowerPlant", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.525F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, &VMaterialLoader::materialCraftmenuButtonOilPowerplantHover, SELECT_BUILDING_OILPOWERPLANT, "oilPowerPlant", 0.1F);
	m_vtTabBuilding->addButton(CFloatRect(0.775F, 0.525F, 0.20F, 0.4F), &VMaterialLoader::materialCraftmenuButtonPowerline, &VMaterialLoader::materialCraftmenuButtonPowerlineHover, SELECT_BUILDING_POWERLINE, "powerLine", 0.1F);

	m_vtTabSabotage->addButton(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonScissors, &VMaterialLoader::materialSabotageButtonScissorsHover, SELECT_SABOTAGE_POWERLINECUT, "sabotagePowerlineCut", 0.1F);
	m_vtTabSabotage->addButton(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonStrike, &VMaterialLoader::materialSabotageButtonStrikeHover, SELECT_SABOTAGE_STRIKE, "sabotageStrike", 0.1F);
	m_vtTabSabotage->addButton(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonHalf, &VMaterialLoader::materialSabotageButtonHalfHover, SELECT_SABOTAGE_HALF, "sabotageHalf", 0.1F);

	m_vtTabSabotage->addButton(CFloatRect(0.025F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonPowerOn, &VMaterialLoader::materialSabotageButtonPowerOnHover, SELECT_SABOTAGE_POWERON, "sabotagePowerOn", 0.1F);
	m_vtTabSabotage->addButton(CFloatRect(0.275F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonPowerOff, &VMaterialLoader::materialSabotageButtonPowerOffHover, SELECT_SABOTAGE_POWEROFF, "sabotagePowerOff", 0.1F);
	m_vtTabSabotage->addButton(CFloatRect(0.525F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonSell, &VMaterialLoader::materialSabotageButtonSellHover, SELECT_SABOTAGE_SELL, "sabotageSell", 0.1F);
	
	m_vtTabSabotage->addOverlay(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialAnimSabotageCutPowerline, "CooldownSabotagePowerLineCut", 0.1F);
	m_vtTabSabotage->addOverlay(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialAnimSabotageStrike, "CooldownSabotageStrike", 0.1F);
	m_vtTabSabotage->addOverlay(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialAnimSabotageHalfResource, "CooldownSabotageHalfResource", 0.1F);
	
	m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOff();
	m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOff();
	m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOff();

	// Tab for statistics

	m_vtTabStatistics->addText(CFloatRect(0.05f, 0, 0.2f, 0.2f), &VMaterialLoader::standardFont, "Gebaeude", "buildingText", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.25f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonWindmill, "statisticWind",0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.1f, 0.28f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_WINDMILL],0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.50f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, "statisticHydro", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.1f, 0.53f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_HYDROPOWERPLANT], 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.75f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, "statisticSolar", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.1f, 0.78f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_SOLARPOWERPLANT], 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.22f, 0.25f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, "statisticNuclear", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.27f, 0.28f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_NUCLEARPOWERPLANT], 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.22f, 0.50f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, "statisticCoal", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.27f, 0.53f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_COALPOWERPLANT], 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.22f, 0.75f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, "statisticOil", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.27f, 0.78f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_OILPOWERPLANT], 0.1F);

	// Renewable / fossil energy Statistics
	m_vtTabStatistics->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.575F, 0.275F, 0.1F, 0.6F), &VMaterialLoader::materialFossil, "RenFosEnergyContainerOwn", 0.199F);
	m_vgGraphEnergyRatioOwn = m_vtTabStatistics->getContainer("RenFosEnergyContainerOwn")->addGraphRatio(CFloatRect(0, 0, 1, 1), "renfosRatio", &VMaterialLoader::materialRegenerative);
	m_vtTabStatistics->addText(CFloatRect(0.475F, 0, 0.2F, 0.2F), &VMaterialLoader::standardFont, "Placeholder", "ownHeadlineFossile", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.485F, 0.285F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "ownGraphTextLeft", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.485F, 0.805F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "ownGraphTextRight", 0.1F);

	m_vtTabStatistics->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.825F, 0.275F, 0.1F, 0.6F), &VMaterialLoader::materialFossil, "RenFosEnergyContainerEnemy", 0.199F);
	m_vgGraphEnergyRatioEnemy = m_vtTabStatistics->getContainer("RenFosEnergyContainerEnemy")->addGraphRatio(CFloatRect(0, 0, 1, 1), "renfosRatioEnemy", &VMaterialLoader::materialRegenerative);
	m_vtTabStatistics->addText(CFloatRect(0.725F, 0, 0.2F, 0.2F), &VMaterialLoader::standardFont, "Placeholder", "enemyHeadlineFossile", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.735F, 0.285F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "enemyGraphTextTop", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.735F, 0.805F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "enemyGraphTextBottom", 0.1F);

	//vrRegister->SwitchToTab("TabBuilding");

	SabotageTabSwitchOff();
	m_vtTabStatistics->switchOff();
	vrRegister->getTab("TabBuilding")->switchOn();
	vrRegister->setActiveTab("TabBuilding");

	/********************************************************Minimap AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.73F, 0.00F, 0.27F, 1.0F), &VMaterialLoader::materialMinimapBackground, "Minimap", 0.3F);


	/***********************************************************Dialog******************************************************************/
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.35F, 0.10F, 0.30F, 0.55F), &VMaterialLoader::materialLobbyRunningGamesBackground, "DialogBox", 0.3F);

	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.10F, 0.80F, 0.15F), &VMaterialLoader::materialButtonGameContinue, &VMaterialLoader::materialButtonGameContinueHover, NOTHING, "MenueButtonContinue", 0.2F);
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.27F, 0.80F, 0.15F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "MenueButtonQuit", 0.2F);
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.44F, 0.80F, 0.15F), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover, NOTHING, "MenueButtonBack", 0.2F);

	
	//******** Statistics Menu *********//
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.25F,0.25F,0.5F,0.5F), "StatisticsMenu", 0.3F);

	VStatistics* statisticsMenus = getContainer("StatisticsMenu")->addStatisticsScreen(CFloatRect(0, 0, 1, 1), &VMaterialLoader::materialLobbyRunningGamesBackground, "statisticsScreen", 0.3F);
	statisticsMenus->addText("Du bist ein zukunftsorientierter Mensch und setzt auf Nachhaltigkeit\nAchte jedoch auf die Beduerfnisse deiner Stadtbowohner und versorge sie gut\n\nDenn nichts ist wichtiger als glueckliche Einwohner und gruener Fortschritt");
	statisticsMenus->addText("Konfuzius sagt: Harmonie und Mitte, Gleichmut und Gleichgewicht - blubb blubb");

	getContainer("DialogBox")->switchOff();

}

VScreenIngame::~VScreenIngame()
{
}

void VScreenIngame::onNotify(const Event& events)
{
	selectedBuilding = VIdentifier::Undefined;
	selectedAction = IViewBuilding::Undefined;

	switch (events)
	{
	case SWITCH_TO_REGISTER_BUILDING:
		if (vrRegister->getActiveTab()->getName() != "TabBuilding")
		{
			vUi->switchCursor(VUI::CursorType::Default);
			SabotageTabSwitchOff();
			m_vtTabStatistics->switchOff();
			vrRegister->getTab("TabBuilding")->switchOn();
			vrRegister->setActiveTab("TabBuilding");
		}
		break;

	case SWITCH_TO_REGISTER_SABOTAGE:
		if (vrRegister->getActiveTab()->getName() != "TabSabotage")
		{
			vUi->switchCursor(VUI::CursorType::Default);
			m_vtTabStatistics->switchOff();
			vrRegister->getTab("TabBuilding")->switchOff();
			SabotageTabSwitchOn();
			vrRegister->setActiveTab("TabSabotage");
		}
		break;
	case SWITCH_TO_REGISTER_STATISTICS:
		if (vrRegister->getActiveTab()->getName() != "TabStatistics")
		{
			vUi->switchCursor(VUI::CursorType::Default);
			SabotageTabSwitchOff();
			m_vtTabStatistics->switchOn();
			vrRegister->getTab("TabBuilding")->switchOff();
			vrRegister->setActiveTab("TabStatistics");
			updatePowerPlants();
		}
		break;

	case SELECT_BUILDING_WINDMILL:
		clearInfofield();
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VWindmillPowerPlant;
		vUi->switchCursor(vUi->CursorType::Hammer);
		setActiveButton("windmill");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LWindmillPowerPlant)));


		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();

		
		break;
	case SELECT_BUILDING_COALPOWERPLANT:
		clearInfofield();
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VCoalPowerPlant;
		vUi->switchCursor(vUi->CursorType::Hammer);

		setActiveButton("coalPowerPlant");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LCoalPowerPlant)));
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		
		

		break;
	case SELECT_BUILDING_OILPOWERPLANT:
		clearInfofield();
		
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VOilRefinery;
		vUi->switchCursor(vUi->CursorType::Hammer);

		setActiveButton("oilPowerPlant");
		
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LOilRefinery)));
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		

		break;
	case SELECT_BUILDING_NUCLEARPOWERPLANT:
		clearInfofield();
		
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VNuclearPowerPlant;
		vUi->switchCursor(vUi->CursorType::Hammer);

		setActiveButton("nuclearPowerPlant");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LNuclearPowerPlant)));
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		break;
	case SELECT_BUILDING_HYDROPOWERPLANT:
		clearInfofield();
		
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VHydroelectricPowerPlant;
		vUi->switchCursor(vUi->CursorType::Hammer);

		setActiveButton("hydroPowerPlant");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LHydroelectricPowerPlant)));
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		break;
	case SELECT_BUILDING_SOLARPOWERPLANT:
		clearInfofield();
		selectedBuilding = VIdentifier::VSolarPowerPlant;
		m_viewportModels.SwitchOn();

		vUi->switchCursor(vUi->CursorType::Hammer);
		setActiveButton("solarPowerPlant");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LSolarPowerPlant)));
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		break;
	case SELECT_BUILDING_POWERLINE:
		clearInfofield();
		
		m_viewportModels.SwitchOn();
		selectedBuilding = VIdentifier::VPowerLine;
		vUi->switchCursor(vUi->CursorType::Hammer);


		CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LPowerLine)));

		setActiveButton("powerLine");
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
		getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
		break;

	case SELECT_SABOTAGE_POWERLINECUT:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::Sabotage);
		setActiveButton("sabotagePowerlineCut");
		selectedAction = IViewBuilding::sabotageRemove;
		break;
	case SELECT_SABOTAGE_STRIKE:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::Sabotage);
		setActiveButton("sabotageStrike");
		selectedAction = IViewBuilding::sabotageDeactivate;
		break;
	case SELECT_SABOTAGE_HALF:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::Sabotage);
		setActiveButton("sabotageHalf");
		selectedAction = IViewBuilding::sabotageResource;
		break;

	case SELECT_SABOTAGE_POWERON:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::PowerOn);
		setActiveButton("sabotagePowerOn");
		selectedAction = IViewBuilding::switchOn;
		break;
	case SELECT_SABOTAGE_POWEROFF:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::PowerOff);
		setActiveButton("sabotagePowerOff");
		selectedAction = IViewBuilding::switchOff;
		break;
	case SELECT_SABOTAGE_SELL:
		clearInfofield();
		vUi->switchCursor(vUi->CursorType::Sell);
		setActiveButton("sabotageSell");
		selectedAction = IViewBuilding::sell;
		break;

	default:
		notify(events);
		break;

	}

	updateModelView();
}


void VScreenIngame::switchOn()
{
	m_viewport->SwitchOn();
	m_scene.SwitchOn();
	m_isOn = true;
}

void VScreenIngame::switchOff()
{
	m_viewport->SwitchOff();
	m_viewportModels.SwitchOff();
	m_scene.SwitchOff();
	m_isOn = false;
}

void VScreenIngame::checkShortcut(CDeviceKeyboard* keyboard)
{
	static bool bK = false;
	static bool enabled = true;
	static bool iwas = true;
	static bool iwas2 = true;
	static bool iwas3 = true;

	if (keyboard->KeyPressed(DIK_O) && iwas)
	{
		iwas = false;
		startCooldown(SABOTAGE_HALF);
		startCooldown(SABOTAGE_STRIKE);
		startCooldown(SABOTAGE_CUTPOWERLINE);
	}
	if (keyboard->KeyPressed(DIK_Y) && iwas3)
	{
		startCooldown(SABOTAGE_CUTPOWERLINE);
	}
	if (keyboard->KeyPressed(DIK_N))
	{
		static bool zeug = true;
		if (zeug)
		{
			m_viewport->SubOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
		}
	}

	if (keyboard->KeyPressed(DIK_M))
	{
		static bool zeug2 = true;
			if (zeug2)
			{
				m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
			}
	}

	if (keyboard->KeyPressed(DIK_SPACE) && iwas2)
	{
		iwas2 = false;
		hideBottomBar();
	}

	if (keyboard->KeyPressed(DIK_V))
	{
		vUi->gameOver(false);
	}

	
	
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
		static std::string hover = "Hover Windmill";
		static std::string standard = "infofeld";
		float curPosX;
		float curPosY;
		cursor->GetFractional(curPosX, curPosY);
		if (CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("windmill")->checkHover(curPosX, curPosY))
		{
			
			updateInfofield(hover);
		}
		else
			updateInfofield(standard);*/

	if (vUi->m_zkCursor.ButtonPressedRight())
	{
		if (activeButton != nullptr)
		{
			vUi->switchCursor(vUi->CursorType::Default);
			activeButton->setActive(false);


			clearInfofield();

			if (selectedBuilding != VIdentifier::Undefined)

			{
				selectedBuilding = VIdentifier::Undefined;
				updateModelView();
			}

			activeButton = nullptr;
		}
	}
}

void VScreenIngame::updateMoney(const int wert)
{
	CASTD<VText*>(getContainer("Topbar")->getGuiObject("moneyValue"))->updateText(std::to_string(wert));
}

void VScreenIngame::updatePopulation(const int wert)
{
	CASTD<VText*>(getContainer("Topbar")->getGuiObject("popValue"))->updateText(std::to_string(wert));
}

void VScreenIngame::updateInfofield(const std::string& neuerText)
{
	//CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText"))->updateText(neuerText);
}

void VScreenIngame::updateAddedPowerPlant(const LIdentifier::LIdentifier id)
{
	switch (id)
	{
	case LIdentifier::LCoalPowerPlant: statPlacedBuildings[BUILDING_COALPOWERPLANT]++;
		break;
	case LIdentifier::LHydroelectricPowerPlant: statPlacedBuildings[BUILDING_HYDROPOWERPLANT]++;
		break;
	case LIdentifier::LNuclearPowerPlant: statPlacedBuildings[BUILDING_NUCLEARPOWERPLANT]++;
		break;
	case LIdentifier::LOilRefinery: statPlacedBuildings[BUILDING_OILPOWERPLANT]++;
		break;
	case LIdentifier::LSolarPowerPlant: statPlacedBuildings[BUILDING_SOLARPOWERPLANT]++;
		break;
	case LIdentifier::LWindmillPowerPlant: statPlacedBuildings[BUILDING_WINDMILL]++;
		break;
	case LIdentifier::LPowerLine: statPlacedBuildings[BUILDING_POWERLINE]++;
		break;
	default: break;
	}
}

void VScreenIngame::updateRemovedPowerPlant(const LIdentifier::LIdentifier id)
{
	switch (id)
	{
	case LIdentifier::LCoalPowerPlant: statPlacedBuildings[BUILDING_COALPOWERPLANT]--;
		break;
	case LIdentifier::LHydroelectricPowerPlant: statPlacedBuildings[BUILDING_HYDROPOWERPLANT]--;
		break;
	case LIdentifier::LNuclearPowerPlant: statPlacedBuildings[BUILDING_NUCLEARPOWERPLANT]--;
		break;
	case LIdentifier::LOilRefinery: statPlacedBuildings[BUILDING_OILPOWERPLANT]--;
		break;
	case LIdentifier::LSolarPowerPlant: statPlacedBuildings[BUILDING_SOLARPOWERPLANT]--;
		break;
	case LIdentifier::LWindmillPowerPlant: statPlacedBuildings[BUILDING_WINDMILL]--;
		break;
	case LIdentifier::LPowerLine: statPlacedBuildings[BUILDING_POWERLINE]--;
		break;
	default: break;
	}
}


void VScreenIngame::updateNumberPowerLines(const int newNumberPowerLines)
{
	statPlacedBuildings[BUILDING_POWERLINE] = newNumberPowerLines;
}

void VScreenIngame::updatePowerPlants()
{
	//VTab * tabStatistics = CASTD<VRegister *>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics");
	for (const std::pair<BUILDINGTYPE, int>& plant : statPlacedBuildings)
	{
		if (plant.first != BUILDING_POWERLINE) {
			if (plant.second < 10)
				CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first]))->updateText("0" + std::to_string(plant.second));
			else 
				CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first]))->updateText(std::to_string(plant.second));
		}
	}
}

void VScreenIngame::updateGraphProdNeeded(float fProduced, float fNeeded)
{
	m_vgGraphEnergy->updateBar2("producedEnergy", fProduced);
	m_vgGraphEnergy->updateBar2("neededEnergy", fNeeded);
}

void VScreenIngame::updateEnergyOverload(int overload)
{
	CASTD<VText*>(m_vtTopbar->getGuiObject("energyOverload"))->updateText(std::to_string(overload));
}

void VScreenIngame::updateOwnGraphRatio(float fRatio)
{
	m_vgGraphEnergyRatioOwn->updateValue(fRatio);
	CASTD<VText*>(m_vtTabStatistics->getGuiObject("ownGraphTextLeft"))->updateText(std::to_string(CASTS<int>(fRatio) * 100) + "%");
	CASTD<VText*>(m_vtTabStatistics->getGuiObject("ownGraphTextRight"))->updateText(std::to_string(100 - (CASTS<int>(fRatio) * 100)) + "%");

	float x = fRatio * 100, y = 100 - fRatio;
}

void VScreenIngame::updateEnemyGraphRatio(float fRatio) {
	
	m_vgGraphEnergyRatioEnemy->updateValue(fRatio);
	CASTD<VText*>(m_vtTabStatistics->getGuiObject("enemyGraphTextTop"))->updateText(std::to_string(CASTS<int>(fRatio) * 100) + "%");
	CASTD<VText*>(m_vtTabStatistics->getGuiObject("enemyGraphTextBottom"))->updateText(std::to_string(100 - (CASTS<int>(fRatio) * 100)) + "%");
}

CFloatRect VScreenIngame::getTopSpace()
{
	return getContainer("Topbar")->getRectangle();
}

CFloatRect VScreenIngame::getBottomSpace()
{
	return getContainer("BottomBar")->getRectangle();
}

void VScreenIngame::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

	for (const std::pair<std::string, IViewGUIObject*>& ObjectPair : tempGUIObjects)
	{
		if (ObjectPair.second->isOn())
		{
			if (!vUi->m_BlockCursorLeftPressed)
			{
				//check for events
				ObjectPair.second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
			}
			//if screen was changed
			if (vUi->m_screenChanged)
			{
				vUi->m_screenChanged = false;

				vUi->m_BlockCursorLeftPressed = true;
				return;
			}
		}
	}
}

void VScreenIngame::checkGUIContainer(IViewGUIContainer* tempGuicontainer)
{
	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainerMap;

	tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();

	checkGUIObjects(tempGuicontainer);
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainerMap)
	{
		checkGUIObjects(ContainerPair.second);

		if (tempGuicontainer->getGuiContainerMap().size() > 0)
		{
			checkGUIContainer(ContainerPair.second);
		}
	}
}

void VScreenIngame::resize(const int width, const int height)
{
	m_viewport->ReSize();
}

void VScreenIngame::handleInput()
{
	static bool keyPressed = false;
	float direction = 1.0f;

	//TODO (MBR) remove when we get the final models (This is used to place them in the right hight)
	//float step = 0.05f;
	//static float total = 0.0f;
	//extern IViewModel *viemodelPointer;
	////Model UP
	//if (vUi->m_zkKeyboard.KeyPressed(DIK_T))
	//{

	//	viemodelPointer->getPlacementMain()->TranslateZDelta(step);
	//	total += step;
	//}

	////Model Down
	//if (vUi->m_zkKeyboard.KeyPressed(DIK_G))
	//{

	//	viemodelPointer->getPlacementMain()->TranslateZDelta(-step);
	//	total -= step;		
	//}

	//DEBUG_OUTPUT("Total" << total);


	if (vUi->m_zkKeyboard.KeyPressed(DIK_LCONTROL))
	{
		direction = -1.0f;
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_U))
	{
		m_zpModels.RotateXDelta(0.1f * direction);
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_I))
	{
		m_zpModels.TranslateZDelta(0.1f * direction);
	}

	const float cameraStength = 1.0f;
	//Left + Right:
	if (vUi->m_zkKeyboard.KeyPressed(DIK_A))
	{
		m_zpCamera.TranslateXDelta(-cameraStength);
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_D))
	{
		m_zpCamera.TranslateXDelta(cameraStength);
	}

	//Back + Forward
	if (vUi->m_zkKeyboard.KeyPressed(DIK_S))
	{
		m_zpCamera.TranslateYDelta(-cameraStength);
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_W))
	{
		m_zpCamera.TranslateYDelta(cameraStength);
	}

	//Zoom In + Out
	const float mouseWheelPositionMin = -25.0f;
	const float mouseWheelPositionMax = 10.0f;
	const float zoomFactor = 2.0f;

	if (vUi->m_zkKeyboard.KeyPressed(DIK_UP))
	{
		if (mouseWheelPosition > mouseWheelPositionMin)
		{
			m_zpCamera.TranslateZDelta(-cameraStength * zoomFactor);
			mouseWheelPosition += -cameraStength * zoomFactor;
		}
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_DOWN))
	{
		if (mouseWheelPosition < mouseWheelPositionMax)
		{
			m_zpCamera.TranslateZDelta(cameraStength * zoomFactor);
			mouseWheelPosition += cameraStength * zoomFactor;
		}
	}

	if (vUi->m_zkMouse.GetRelativeZ() != 0.0f)
	{
		if (vUi->m_zkMouse.GetRelativeZ() > 0.0f)
		{
			if (mouseWheelPosition > mouseWheelPositionMin)
			{
				m_zpCamera.TranslateZDelta(-cameraStength * zoomFactor);
				mouseWheelPosition += -cameraStength * zoomFactor;
			}
		}
		else
		{
			if (mouseWheelPosition < mouseWheelPositionMax)
			{
				m_zpCamera.TranslateZDelta(cameraStength * zoomFactor);
				mouseWheelPosition += cameraStength * zoomFactor;
			}
		}
	}

	//Flip View
	if (vUi->m_zkKeyboard.KeyPressed(DIK_E))
	{
		if (cameraAngle < 5)
		{
			m_zpCamera.RotateZDelta(cameraStength / 10.0f);
			cameraAngle += (int)cameraStength;
		}
	}

	if (vUi->m_zkKeyboard.KeyPressed(DIK_Q))
	{
		if (cameraAngle > -5)
		{
			m_zpCamera.RotateZDelta(-cameraStength / 10.0f);
			cameraAngle -= (int)cameraStength;
		}
	}

	//Return to Default View 
	if (!vUi->m_zkKeyboard.KeyPressed(DIK_Q) && !vUi->m_zkKeyboard.KeyPressed(DIK_E))
	{	
		if (cameraAngle != 0)
		{

			if (cameraAngle < 0)
			{
				m_zpCamera.RotateZDelta(cameraStength / 10.0f);
				cameraAngle += (int)cameraStength;
			}


			 if (cameraAngle > 0)
		   	{
				m_zpCamera.RotateZDelta(-cameraStength / 10.0f);
				cameraAngle -= (int)cameraStength;
			}
		}
	
	}

	CFloatRect topSpace = CASTD<VScreenIngame*>(vUi->m_screens["Ingame"])->getTopSpace();
	CFloatRect bottomSpace = CASTD<VScreenIngame*>(vUi->m_screens["Ingame"])->getBottomSpace();

	/*
	(0,0)=(x,y)
	#----> x (1,0)
	|
	|
	y
	(0,1)
	*/
	static float cursorXOld = -5.0f;
	static float cursorYOld = -5.0f;
	float cursorX, cursorY;
	bool insideFrame = vUi->m_zkCursor.GetFractional(cursorX, cursorY);
	if (!insideFrame || cursorY < topSpace.GetYSize() || cursorY > (1.0f - bottomSpace.GetYSize()) || fabs(cursorXOld - cursorX) + fabs(cursorYOld - cursorY) <= 0.05)
	{
		//Restrict picking when not in window or cursor is only over UI or when the cursor doesn't move much
		return;
	}

	std::map<int, std::vector<int>> pickedElements = pickElements();
	if (pickedElements.count(VIdentifier::VPlayingField) > 0)
	{
		vUi->vMaster->getVPlayingField()->hoverField(pickedElements[VIdentifier::VPlayingField][0], pickedElements[VIdentifier::VPlayingField][1]);
	}

	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		handleLeftClick(pickedElements);
	}
	else if (vUi->m_zkCursor.ButtonPressedRight())
	{
		if (!clickActive)
		{
			selectedBuilding = VIdentifier::Undefined;
			updateModelView();

			clickActive = true;
		}
	}
	else
	{
		clickActive = false;
	}
}

void VScreenIngame::tick(const float fTimeDelta)
{
	if (!vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = false;
	}

	handleInput();

	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainer;

	checkShortcut(&vUi->m_zkKeyboard);
	checkSpecialEvent(&vUi->m_zkCursor);
	tempGuiContainer = getGuiContainerMap();

	//For all containers in the screen
	for (const std::pair<std::string, IViewGUIContainer*>& ContainerPair : tempGuiContainer)
	{
		checkGUIContainer(ContainerPair.second);
	}

	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = true;
	}

	modelWindmill.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VWindmillPowerPlant, fTimeDelta));
	modelOil.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VOilRefinery, fTimeDelta));
	modelSolar.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VSolarPowerPlant, fTimeDelta));
	modelHydroelectric.rotate(VMaterialLoader::getRotationPerTick(VIdentifier::VHydroelectricPowerPlant, fTimeDelta));
}

std::map<int, std::vector<int>> VScreenIngame::pickElements()
{
	std::map<int, std::vector<int>> pickedElements;

	CGeo* pickedGeo = vUi->m_zkCursor.PickGeoPreselected(VPlayingField::geosField);

	if (pickedGeo != nullptr)
	{
		std::vector<std::string> nameParts = split(pickedGeo->GetName(), ';');
		ASSERT(nameParts.size() == 3, "The picked geo has an invalid name");

		//Convert the arguments to integer (skip the first one, because its the key for the map
		std::vector<int> namePartsInt;
		for (size_t j = 1; j < nameParts.size(); j++)
		{
			namePartsInt.emplace_back(std::stoi(nameParts[j]));
		}

		pickedElements[std::stoi(nameParts[0])] = namePartsInt;
	}

	return pickedElements;
}

void VScreenIngame::startAnimation()
{
}

void VScreenIngame::StartEvent()
{
}

void VScreenIngame::EndEvent()
{
}

std::unordered_map<std::string, IViewGUIObject*> VScreenIngame::getScreenObjects()
{
	std::unordered_map<std::string, IViewGUIObject*> resultObjectList;

	for (std::pair<std::string, IViewGUIContainer*> container : m_Guicontainer)
	{
		std::unordered_map<std::string, IViewGUIObject*> tempMap = getObjects(container.second);
		if (tempMap.size() != 0)
			resultObjectList.insert(tempMap.begin(), tempMap.end());
	}

	return resultObjectList;
}

std::unordered_map<std::string, IViewGUIObject*> VScreenIngame::getObjects(IViewGUIContainer* container)
{
	static std::unordered_map<std::string, IViewGUIObject*> objectList;

	std::unordered_map<std::string, IViewGUIObject*> tempObjectList = container->getGuiObjectList();
	objectList.insert(tempObjectList.begin(), tempObjectList.end());

	if (container->getGuiContainerMap().size() == 0) return objectList;
	else
	{
		for (std::pair<std::string, IViewGUIContainer*> containerCon : container->getGuiContainerMap())
		{
			getObjects(containerCon.second);
		}
	}
	return std::unordered_map<std::string, IViewGUIObject*>();
}

void VScreenIngame::showMessage(const std::string& messageRow1, const std::string& messageRow2, const int timeSeconds)
{
	static bool brunning = false;
	if (!brunning)
	{
		std::thread([this, messageRow1, messageRow2, timeSeconds]
			{
				CASTD<VText*>(getContainer("MessageArea")->getGuiObject("Messagebox"))->updateText(messageRow1);
				CASTD<VText*>(getContainer("MessageArea")->getGuiObject("Messagebox2"))->updateText(messageRow2);

				brunning = true;
				getContainer("MessageArea")->switchOn();

				if (messageRow2 == "")
					getContainer("MessageArea")->getGuiObject("Messagebox2")->switchOff();

				std::this_thread::sleep_for(std::chrono::seconds(timeSeconds));
				getContainer("MessageArea")->switchOff();
				brunning = false;
			}).detach();
	}
}

void VScreenIngame::startCooldown(const INTERACTIONS interaction)
{
	switch (interaction)
	{
		case SABOTAGE_CUTPOWERLINE:
			std::thread([this]
				{
					m_CooldownPowerLineCut = true;
					m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOff();
					m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOn();
					VMaterialLoader::materialAnimSabotageCutPowerline.SetAni(30, 2, 1);
					m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
					std::this_thread::sleep_for(std::chrono::seconds(LBalanceLoader::getSabotageCooldown(LSabotage::Remove)));
					m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOff();
					VMaterialLoader::materialAnimSabotageCutPowerline.SetAni(30, 2, 0);
					m_CooldownPowerLineCut = false;

					if (vrRegister->getActiveTab()->getName() == "TabSabotage")
						m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOn();
				}).detach();
			break;
		case SABOTAGE_STRIKE:
			std::thread([this]
				{
					m_CooldownStrike = true;
					m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOff();
					m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOn();
					VMaterialLoader::materialAnimSabotageStrike.SetAni(45, 2, 1);
					m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageStrike"));
					std::this_thread::sleep_for(std::chrono::seconds(LBalanceLoader::getSabotageCooldown(LSabotage::Deactivate)));
					m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOff();
					VMaterialLoader::materialAnimSabotageStrike.SetAni(45, 2, 0);
					m_CooldownStrike = false;

					if (vrRegister->getActiveTab()->getName() == "TabSabotage")
						m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOn();
				}).detach();
			break;
		case SABOTAGE_HALF:

			std::thread([this]
				{
					m_CooldownHalfResource = true;
					m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOff();
					m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOn();
					VMaterialLoader::materialAnimSabotageHalfResource.SetAni(60, 2, 1);
					m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource"));
					std::this_thread::sleep_for(std::chrono::seconds(LBalanceLoader::getSabotageCooldown(LSabotage::Remove)));
					m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOff();
					VMaterialLoader::materialAnimSabotageHalfResource.SetAni(60, 2, 0);
					m_CooldownHalfResource = false;

					if (vrRegister->getActiveTab()->getName() == "TabSabotage")
						m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOn();
				}).detach();
			break;
	}
}

void VScreenIngame::clearInfofield()
{
	for(std::pair<std::string,IViewGUIObject*> obj : getContainer("BottomBar")->getContainer("Infofield")->getGuiObjectList())
	{
		obj.second->switchOff();
	}
	for (std::pair<std::string, COverlay*> overlay : getContainer("BottomBar")->getContainer("Infofield")->getOverlayMap())
	{
		overlay.second->SwitchOff();
	}

	m_viewportModels.SwitchOff();
}

void VScreenIngame::hideBottomBar()
{
	std::thread([this] {
		while (getContainer("BottomBar")->getRectangle().GetYPos() > 0.0F)
		{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
			getContainer("BottomBar")->slideDown(-0.01F);
		}
	}).detach();
}

void VScreenIngame::setActiveButton(const std::string& sName)
{
	std::unordered_map<std::string, IViewGUIObject*> objectList = getScreenObjects();

	if (activeButton)
		activeButton->setActive(false);

	ASSERT(objectList[sName]->getType() == IViewGUIObject::ObjectType::BUTTON, "The Element is not a Button");
	CASTD<VButton*>(objectList[sName])->setActive();
	activeButton = CASTD<VButton*>(objectList[sName]);
}

CFloatRect VScreenIngame::getRectForPixel(const int iPosX, const int iPosY, const int iSizeX, const int iSizeY)
{
	CFloatRect tempRectangle;
	const int iFensterBreite = vUi->m_zf.m_iWidthWindow;
	const int iFensterHöhe = vUi->m_zf.m_iHeightWindow;

	ASSERT((((iPosX + iSizeX) <= iFensterBreite) && ((iPosY + iSizeY) <= iFensterHöhe)), "Angegebener Bereich liegt außerhalb des Fensters");

	/* iFensterBreite/100% = iPosX/X% => iFensterbreite=(iPosX*100%)/x =>x=(iPosX*100%)/iFensterBreite */

	tempRectangle.SetXPos(iPosX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYPos(iPosY / CASTS<float>(iFensterHöhe));
	tempRectangle.SetXSize(iSizeX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYSize(iSizeY / CASTS<float>(iFensterHöhe));

	return tempRectangle;
}

void VScreenIngame::handleLeftClick(const std::map<int, std::vector<int>>& pickedElements)
{
	if (!clickActive)
	{
		if (pickedElements.count(VIdentifier::VPlayingField) > 0)
		{
			int x = pickedElements.at(VIdentifier::VPlayingField)[0];
			int y = pickedElements.at(VIdentifier::VPlayingField)[1];
			bool operationSuccessful = false;

			if (selectedBuilding != VIdentifier::Undefined)
			{
				operationSuccessful = tryBuilding(x, y);
			}
			
			if (selectedAction != IViewBuilding::Undefined)
			{
				if (IViewBuilding::isSabotageAction(selectedAction))
				{
					operationSuccessful = trySabotage(x, y);
					if (operationSuccessful)
					{
						VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_EMITTED, nullptr);
					}
				}
				else
				{
					operationSuccessful = tryBuildingInteraction(x, y);
				}
			}

			if (!operationSuccessful)
			{
				VSoundLoader::playSoundeffect(VSoundLoader::OPERATION_CANCELED, nullptr);
			}
		}

		clickActive = true;
	}
}

bool VScreenIngame::tryBuilding(const int x, const int y)
{
	switch (selectedBuilding)
	{
	case VIdentifier::VPowerLine:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LPowerLine>(x, y);
		break;
	case VIdentifier::VWindmillPowerPlant:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LWindmillPowerPlant>(x, y);
		break;
	case VIdentifier::VCoalPowerPlant:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LCoalPowerPlant>(x, y);
		break;
	case VIdentifier::VHydroelectricPowerPlant:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LHydroelectricPowerPlant>(x, y);
		break;
	case VIdentifier::VNuclearPowerPlant:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LNuclearPowerPlant>(x, y);
		break;
	case VIdentifier::VOilRefinery:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LOilRefinery>(x, y);
		break;
	case VIdentifier::VSolarPowerPlant:
		vUi->vMaster->getVPlayingField()->tryBuildOnField<LSolarPowerPlant>(x, y);
		break;
	default:
		return false;
	}

	return true;
}

bool VScreenIngame::trySabotage(const int x, const int y)
{
	IViewBuilding* vbuilding = vUi->vMaster->getVPlayingField()->getBuilding(x, y);

	//No building selected
	if (vbuilding == nullptr)
	{
		return false;
	}
	//Own building selected
	
	if (vbuilding->getLBuilding()->getPlayerId() != LPlayer::PlayerId::Remote)
	{
		return false;
	}

	switch (selectedAction)
	{
		case IViewBuilding::sabotageDeactivate:
			{
				//No power plant selected
				if (dynamic_cast<IVPowerPlant*>(vbuilding) == nullptr)
				{
					return false;
				}

				bool operationSuccessful = vbuilding->clicked(selectedAction);
				if (operationSuccessful)
				{
					startCooldown(SABOTAGE_STRIKE);
				}

				return operationSuccessful;
			}
		case IViewBuilding::sabotageRemove:
			{
				bool operationSuccessful = vbuilding->clicked(selectedAction);
				if (operationSuccessful)
				{
					//only remove it if action was successfull
					vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
					startCooldown(SABOTAGE_CUTPOWERLINE);
				}

				return operationSuccessful;
			}
		case IViewBuilding::sabotageResource:
			{
				// Deduct enemys resources
				if (dynamic_cast<IViewPowerPlant*>(vbuilding) == nullptr)
				{
					return false;
				}

				bool operationSuccessful = vbuilding->clicked(selectedAction);
				if (operationSuccessful)
				{
					startCooldown(SABOTAGE_HALF);
				}

				return operationSuccessful;
			}
		default:
			return false;
	}
}

bool VScreenIngame::tryBuildingInteraction(const int x, const int y)
{
	IViewBuilding* vbuilding = vUi->vMaster->getVPlayingField()->getBuilding(x, y);

	//No building selected
	if (vbuilding == nullptr)
	{
		return false;
	}

	//Remote building selected
	if (vbuilding->getLBuilding()->getPlayerId() != LPlayer::PlayerId::Local)
	{
		return false;
	}

	switch (selectedAction)
	{
		case IViewBuilding::switchOff:
		case IViewBuilding::switchOn:
			//No power plant selected
			if (dynamic_cast<IViewPowerPlant*>(vbuilding) == nullptr)
			{
				return false;
			}

			return vbuilding->clicked(selectedAction);
		
		case IViewBuilding::sell:
			//Currently the sell action does not perform any checks, so remove immediatly
			vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
			return true;

		default:
			return false;
	}
}

void VScreenIngame::updateModelView()
{
	static IViewModel* previousModel = nullptr;

	if (previousModel != nullptr)
	{
		m_sceneModels.SubPlacement(previousModel->getPlacementMain());
	}

	if (models.count(selectedBuilding) > 0)
	{
		previousModel = models.at(selectedBuilding);
		m_sceneModels.AddPlacement(previousModel->getPlacementMain());
	}
	else
	{ //Disable action
		previousModel = nullptr;
	}
}

void VScreenIngame::SabotageTabSwitchOn()
{
	
		if (m_CooldownPowerLineCut)
			m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
		else
			m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOn();


		if (m_CooldownStrike)
			m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageStrike"));
		else
			m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOn();

		if (m_CooldownHalfResource)
			m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource"));
	    else
		m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOn();
		
	

	m_vtTabSabotage->getGuiObject("sabotagePowerOn")->switchOn();
	m_vtTabSabotage->getGuiObject("sabotagePowerOff")->switchOn();
	m_vtTabSabotage->getGuiObject("sabotageSell")->switchOn();

}

void VScreenIngame::SabotageTabSwitchOff()
{
	
		if (m_CooldownPowerLineCut)
			m_viewport->SubOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
		else
			m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOff();

		if (m_CooldownStrike)
			m_viewport->SubOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageStrike"));
		else
			m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOff();

		if (m_CooldownHalfResource)
			m_viewport->SubOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource"));
	    else
			m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOff();
		
	

	m_vtTabSabotage->getGuiObject("sabotagePowerOn")->switchOff();
	m_vtTabSabotage->getGuiObject("sabotagePowerOff")->switchOff();
	m_vtTabSabotage->getGuiObject("sabotageSell")->switchOff();

}

void VScreenIngame::addToScene(CPlacement* placement)
{
	m_scene.AddPlacement(placement);
}

NAMESPACE_VIEW_E
