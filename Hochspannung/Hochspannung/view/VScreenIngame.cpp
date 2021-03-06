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
#include "../logic/LBalanceLoader.h"
#include "../logic/LPlayingField.h"
#include <thread>

NAMESPACE_VIEW_B


VScreenIngame::VScreenIngame(VUI* vUi)
	: IViewScreen(vUi),
	  m_fieldValueStorage(LBalanceLoader::getFieldLength() * LBalanceLoader::getFieldLength(), LPlayingFieldHasher(LBalanceLoader::getFieldLength())),
	  activeInfo(nullptr)
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
	modelNuclear.init();
	modelWindmill.init();
	modelOil.init();
	modelHydroelectric.init();
	modelCoal.init();
	modelSolar.init();
	modelPowerline.Init(VModelPowerLine::NORTH | VModelPowerLine::EAST | VModelPowerLine::SOUTH | VModelPowerLine::WEST);

	models.emplace(VIdentifier::VWindmillPowerPlant, &modelWindmill);
	models.emplace(VIdentifier::VSolarPowerPlant, &modelSolar);
	models.emplace(VIdentifier::VNuclearPowerPlant, &modelNuclear);
	models.emplace(VIdentifier::VOilRefinery, &modelOil);
	models.emplace(VIdentifier::VPowerLine, &modelPowerline);
	models.emplace(VIdentifier::VHydroelectricPowerPlant, &modelHydroelectric);
	models.emplace(VIdentifier::VCoalPowerPlant, &modelCoal);


	//Positioning models
	models[VIdentifier::VWindmillPowerPlant]->getPlacementMain()->TranslateYDelta(2.0f);
	models[VIdentifier::VSolarPowerPlant]->getPlacementMain()->TranslateZ(5.0f);
	models[VIdentifier::VSolarPowerPlant]->getPlacementMain()->TranslateYDelta(2.0f);
	models[VIdentifier::VPowerLine]->getPlacementMain()->TranslateZ(6.0f);
	models[VIdentifier::VPowerLine]->getPlacementMain()->TranslateYDelta(2.0f);
	models[VIdentifier::VOilRefinery]->getPlacementMain()->TranslateYDelta(-0.8);
	models[VIdentifier::VHydroelectricPowerPlant]->getPlacementMain()->TranslateYDelta(-2.0);
	models[VIdentifier::VHydroelectricPowerPlant]->getPlacementMain()->TranslateZDelta(-2.8);
	models[VIdentifier::VNuclearPowerPlant]->getPlacementMain()->TranslateYDelta(-0.8);
	models[VIdentifier::VCoalPowerPlant]->getPlacementMain()->TranslateYDelta(-2.3);
	models[VIdentifier::VCoalPowerPlant]->getPlacementMain()->TranslateZDelta(-2.8);


	CHVector vector = models[VIdentifier::VNuclearPowerPlant]->getPlacementMain()->GetTranslation();
	CHVector vector2 = m_zpModels.GetTranslation();

	for (const std::pair<VIdentifier::VIdentifier, IViewModel*>& p : models)
	{
		p.second->initViewModel(nullptr);
	}


	m_zl.Init(CHVector(0.0F, 0.35F, 0.7F),
	          CColor(0.1F, 0.1F, 0.1F));

	m_zlSpot.Init(CColor(0.6f, 0.6f, 0.6f), 0.01f, 0.07f, 1.75f); //last param = light intensity
	m_zlSpot.SetMaxDistance(2500);
	m_zlSpot.SetMinDistance(40);
	m_zlSpot.SetSoftShadowOn();
	m_zlSpot.SetShadowMapResolution(8192, 8192);
	m_zlSpot.SetRadius(16000);

	m_zpSpot.TranslateZ(900.0f);
	m_zpSpot.TranslateXDelta(700.0f);
	m_zpSpot.TranslateYDelta(-200.0f);
	m_PointingSpot.Init(-3.5f, -5.5f, 0.0f, 1.0f); //Adjust center of the spot light
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


	VSoundLoader::init(&m_scene);

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
	getContainer("Topbar")->addText(CFloatRect(0.151F, 0.25F, 0.2F, 0.6F), &VMaterialLoader::standardFont, "00000", "popValue", 0.1F);

	getContainer("Topbar")->addOverlay(CFloatRect(0.32F, 0.2F, 0.08F, 0.6F), &VMaterialLoader::materialIngameIconMoney, "TopMoneyIcon", 0.1F);
	getContainer("Topbar")->addText(CFloatRect(0.421F, 0.25F, 0.2F, 0.6F), &VMaterialLoader::GoldFont, "00000", "moneyValue", 0.1F);

	getContainer("Topbar")->addOverlay(CFloatRect(0.65F, 0.2F, 0.1F, 0.8F), &VMaterialLoader::materialBattery, "energyOverloadIcon", 0.1F);
	getContainer("Topbar")->addText(CFloatRect(0.751F, 0.25F, 0.2F, 0.6F), &VMaterialLoader::standardFont, "00000", "energyOverload", 0.1F);
	/********************************************************TOP MESSAGE AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.1F, 0.1F, 0.8F, 0.13F), &VMaterialLoader::materialErrorBackground, "MessageArea", 0.3F);
	getContainer("MessageArea")->addText(CFloatRect(0.1F, 0.1F, 0.8F, 0.3F), &VMaterialLoader::errorFont, "Aktion hier nicht moeglich KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK", "Messagebox", 0.1F, VText::TextMode::CENTERED);
	getContainer("MessageArea")->addText(CFloatRect(0.1F, 0.5F, 0.8F, 0.3F), &VMaterialLoader::errorFont, "Weil das und das passiert ist KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK", "Messagebox2", 0.1F, VText::TextMode::CENTERED);

	getContainer("MessageArea")->switchOff();
	/********************************************************BOTTOM AREA*************************************************************/

	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 180, vUi->m_zf.m_iWidthWindow, 180), "BottomBar", 0.9F);


	/********************************************************Infofield AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.00F, 0.00F, 0.22F, 1.0F), &VMaterialLoader::materialInfofieldBackground, "Infofield", 0.3F);
	getContainer("BottomBar")->getContainer("Infofield")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.10F, 0.0F, 0.8F, 1.0F), "BuildingCraftInfo", 0.2F);
	getContainer("BottomBar")->getContainer("Infofield")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.10F, 0.0F, 0.8F, 1.0F), "FieldInfo", 0.2F);
	getContainer("BottomBar")->getContainer("Infofield")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.10F, 0.0F, 0.8F, 1.0F), "SabotageInfo", 0.2F);

	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->addViewport(&m_viewportModels, &m_CamModels, CFloatRect(0.1F, 0.05F, 0.75F, 0.55F), &m_zmbackgroundModels, "DetailedModels");
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->addText(CFloatRect(0.10F, 0.70F, 0.5F, 0.08F), &VMaterialLoader::standardFont, "1000", "PowerInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->addText(CFloatRect(0.10F, 0.85F, 0.5F, 0.08F), &VMaterialLoader::GoldFont, "1000", "MoneyInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->addOverlay(CFloatRect(0.65F, 0.70F, 0.25, 0.08F), &VMaterialLoader::materialIngameIconEnergy, "PowerInfoIcon", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->addOverlay(CFloatRect(0.65F, 0.85F, 0.25, 0.08F), &VMaterialLoader::materialIngameIconMoney, "MoneyInfoIcon", 0.1F);

	//getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addViewport(&m_viewportModels, &m_CamModels, CFloatRect(0.1F, 0.05F, 0.75F, 0.55F), &m_zmbackgroundModels, "ContextModels");
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addText(CFloatRect(0.10F, 0.61F, 0.5F, 0.05F), &VMaterialLoader::standardFont, "1000", "PopulationInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addText(CFloatRect(0.10F, 0.71F, 0.5F, 0.05F), &VMaterialLoader::standardFont, "1000", "EnergyInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addText(CFloatRect(0.10F, 0.81F, 0.5F, 0.05F), &VMaterialLoader::standardFont, "1000", "ResourceInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addText(CFloatRect(0.10F, 0.91F, 0.5F, 0.05F), &VMaterialLoader::GoldFont, "1000", "SellPriceInfo", 0.1F);

	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addOverlay(CFloatRect(0.65F, 0.61F, 0.25, 0.05F), &VMaterialLoader::materialIngameIconPopulation, "PopulationInfoIcon", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addOverlay(CFloatRect(0.65F, 0.71F, 0.25, 0.05F), &VMaterialLoader::materialIngameIconEnergy, "EnergyInfoIcon", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addOverlay(CFloatRect(0.65F, 0.81F, 0.25, 0.05F), &VMaterialLoader::materialIngameIconResource, "ResourceInfoIcon", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->addOverlay(CFloatRect(0.65F, 0.91F, 0.25, 0.05F), &VMaterialLoader::materialIngameIconMoney, "SellPriceInfoIcon", 0.1F);

	getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->addText(CFloatRect(0.10F, 0.70F, 0.5F, 0.08F), &VMaterialLoader::GoldFont, "1000", "CostInfo", 0.1F);
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->addOverlay(CFloatRect(0.65F, 0.70F, 0.25, 0.08F), &VMaterialLoader::materialIngameIconMoney, "CostInfoIcon", 0.1F);


	getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->switchOff();


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

	m_vtTabSabotage->addText(CFloatRect(0.775F, 0.075F, 0.2F, 0.2F), &VMaterialLoader::errorFont, "Sabotage verbleibend", "HeaderSabNum", 0.1F, VText::TextMode::CENTERED);
	m_vtTabSabotage->addText(CFloatRect(0.775F, 0.4F, 0.2F, 0.3F), &VMaterialLoader::errorFont, std::to_string(LBalanceLoader::getSabotageActs()), "SabotageNumLeft", 0.1F, VText::TextMode::CENTERED);

	m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOff();
	m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOff();
	m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOff();
	m_vtTabSabotage->getGuiObject("HeaderSabNum")->switchOff();
	m_vtTabSabotage->getGuiObject("SabotageNumLeft")->switchOff();

	// Tab for own statistics

	m_vtTabStatistics->addText(CFloatRect(0.05f, 0.04f, 0.4f, 0.2f), &VMaterialLoader::standardFont, "Gebaeude Selbst", "buildingText", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.25f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonWindmill, "statisticWind", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.1f, 0.28f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_WINDMILL], 0.1F);

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

	// Tab for enemy statistics

	m_vtTabStatistics->addText(CFloatRect(0.55f, 0.04f, 0.4f, 0.2f), &VMaterialLoader::standardFont, "Gebaeude Gegner", "buildingTextEnemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.55f, 0.25f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonWindmill, "statisticWindEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.6f, 0.28f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_WINDMILL] + "enemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.55f, 0.50f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, "statisticHydroEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.6f, 0.53f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_HYDROPOWERPLANT] + "enemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.55f, 0.75f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, "statisticSolarEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.6f, 0.78f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_SOLARPOWERPLANT] + "enemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.72f, 0.25f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, "statisticNuclearEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.77f, 0.28f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_NUCLEARPOWERPLANT] + "enemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.72f, 0.50f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, "statisticCoalEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.77f, 0.53f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_COALPOWERPLANT] + "enemy", 0.1F);

	m_vtTabStatistics->addOverlay(CFloatRect(0.72f, 0.75f, 0.05f, 0.15f), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, "statisticOilEnemy", 0.1F);
	m_vtTabStatistics->addText(CFloatRect(0.77f, 0.78f, 0.1f, 0.1f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_OILPOWERPLANT] + "enemy", 0.1F);

	

	SabotageTabSwitchOff();
	m_vtTabStatistics->switchOff();
	vrRegister->getTab("TabBuilding")->switchOn();
	vrRegister->setActiveTab("TabBuilding");

	/********************************************************Minimap AREA*************************************************************/
	float fBarIconPosX = 0.2F;
	float fBarIconSizeX = 0.2F;
	float fBarDistance = 0.1F;
	float fBarEnemyPosX = fBarIconPosX + fBarIconSizeX + fBarDistance;

	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.73F, 0.00F, 0.27F, 1.0F), &VMaterialLoader::materialMinimapBackground, "Bars", 0.3F);
	getContainer("BottomBar")->getContainer("Bars")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(fBarIconPosX + 0.1F, 0.33F, 0.1F, 0.6F), &VMaterialLoader::materialFossil, "RenFosEnergyContainerOwn", 0.199F);
	m_vgGraphEnergyRatioOwn = getContainer("BottomBar")->getContainer("Bars")->getContainer("RenFosEnergyContainerOwn")->addGraphRatio(CFloatRect(0, 0, 1, 1), "renfosRatio", &VMaterialLoader::materialRegenerative);
	getContainer("BottomBar")->getContainer("Bars")->addOverlay(CFloatRect(fBarIconPosX, 0.095f, fBarIconSizeX, 0.2F), &VMaterialLoader::materialLeaffossileOwn, "ownHeadlineFossile", 0.1F);
	getContainer("BottomBar")->getContainer("Bars")->addText(CFloatRect(fBarIconPosX, 0.35F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "ownGraphTextTop", 0.1F);
	getContainer("BottomBar")->getContainer("Bars")->addText(CFloatRect(fBarIconPosX, 0.85F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "ownGraphTextBottom", 0.1F);

	getContainer("BottomBar")->getContainer("Bars")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(fBarEnemyPosX + 0.1F, 0.33F, 0.1F, 0.6F), &VMaterialLoader::materialFossil, "RenFosEnergyContainerEnemy", 0.199F);
	m_vgGraphEnergyRatioEnemy = getContainer("BottomBar")->getContainer("Bars")->getContainer("RenFosEnergyContainerEnemy")->addGraphRatio(CFloatRect(0, 0, 1, 1), "renfosRatioEnemy", &VMaterialLoader::materialRegenerative);
	getContainer("BottomBar")->getContainer("Bars")->addOverlay(CFloatRect(fBarEnemyPosX, 0.095f, fBarIconSizeX, 0.2F), &VMaterialLoader::materialLeaffossileEnemy, "enemyHeadlineFossile", 0.1F);
	getContainer("BottomBar")->getContainer("Bars")->addText(CFloatRect(fBarEnemyPosX, 0.35F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "enemyGraphTextTop", 0.1F);
	getContainer("BottomBar")->getContainer("Bars")->addText(CFloatRect(fBarEnemyPosX, 0.85F, 0.08F, 0.08F), &VMaterialLoader::standardFont, "000%", "enemyGraphTextBottom", 0.1F);


	/***********************************************************Dialog******************************************************************/
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.35F, 0.10F, 0.30F, 0.55F), &VMaterialLoader::materialLobbyRunningGamesBackground, "DialogBox", 0.3F);

	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.10F, 0.80F, 0.2F), &VMaterialLoader::materialButtonGameContinue, &VMaterialLoader::materialButtonGameContinueHover, INGAME_MENU_CLOSE, "MenueButtonContinue", 0.2F);
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.4F, 0.80F, 0.2F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "MenueButtonQuit", 0.2F);
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.70F, 0.80F, 0.2F), &VMaterialLoader::materialButtonAbort, &VMaterialLoader::materialButtonAbortHover, INGAME_MENU_CLOSE, "MenueButtonBack", 0.2F);

	getContainer("DialogBox")->switchOff();
}

VScreenIngame::~VScreenIngame()
{}

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
				switchInfo(NOINFO);
				std::cout << m_viewport->m_overlays.m_iOverlays << std::endl;
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
				switchInfo(NOINFO);
				std::cout << m_viewport->m_overlays.m_iOverlays << std::endl;
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
				switchInfo(NOINFO);
				std::cout << m_viewport->m_overlays.m_iOverlays << std::endl;
			}
			break;

		case SELECT_BUILDING_WINDMILL:

			selectedBuilding = VIdentifier::VWindmillPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);
			setActiveButton("windmill");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LWindmillPowerPlant)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LWindmillPowerPlant>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_COALPOWERPLANT:

			selectedBuilding = VIdentifier::VCoalPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);

			setActiveButton("coalPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LCoalPowerPlant)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LCoalPowerPlant>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_OILPOWERPLANT:

			selectedBuilding = VIdentifier::VOilRefinery;
			vUi->switchCursor(vUi->CursorType::Hammer);

			setActiveButton("oilPowerPlant");

			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LOilRefinery)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LOilRefinery>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_NUCLEARPOWERPLANT:

			selectedBuilding = VIdentifier::VNuclearPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);

			setActiveButton("nuclearPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LNuclearPowerPlant)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LNuclearPowerPlant>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_HYDROPOWERPLANT:

			selectedBuilding = VIdentifier::VHydroelectricPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);

			setActiveButton("hydroPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LHydroelectricPowerPlant)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LHydroelectricPowerPlant>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_SOLARPOWERPLANT:

			selectedBuilding = VIdentifier::VSolarPowerPlant;

			vUi->switchCursor(vUi->CursorType::Hammer);
			setActiveButton("solarPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LSolarPowerPlant)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LSolarPowerPlant>()));

			switchInfo(CRAFTBUILDING);
			break;
		case SELECT_BUILDING_POWERLINE:

			selectedBuilding = VIdentifier::VPowerLine;
			vUi->switchCursor(vUi->CursorType::Hammer);

			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LPowerLine)));
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo")->getGuiObject("MoneyInfo"))->updateText(std::to_string(LBalanceLoader::getCost<LPowerLine>()));

			setActiveButton("powerLine");
			switchInfo(CRAFTBUILDING);
			break;

		case SELECT_SABOTAGE_POWERLINECUT:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotagePowerlineCut");
			selectedAction = IViewBuilding::sabotageRemove;
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->getGuiObject("CostInfo"))->updateText(std::to_string(m_RemoveCost));
			switchInfo(SABOTAGEINFO);
			break;
		case SELECT_SABOTAGE_STRIKE:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotageStrike");
			selectedAction = IViewBuilding::sabotageDeactivate;
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->getGuiObject("CostInfo"))->updateText(std::to_string(m_DeactivateCost));
			switchInfo(SABOTAGEINFO);
			break;
		case SELECT_SABOTAGE_HALF:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotageHalf");
			selectedAction = IViewBuilding::sabotageResource;
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo")->getGuiObject("CostInfo"))->updateText(std::to_string(m_ResourceCost));
			switchInfo(SABOTAGEINFO);
			break;

		case SELECT_SABOTAGE_POWERON:
			vUi->switchCursor(vUi->CursorType::PowerOn);
			setActiveButton("sabotagePowerOn");
			selectedAction = IViewBuilding::switchOn;
			switchInfo(INFOTYPE::NOINFO);
			break;
		case SELECT_SABOTAGE_POWEROFF:
			vUi->switchCursor(vUi->CursorType::PowerOff);
			setActiveButton("sabotagePowerOff");
			selectedAction = IViewBuilding::switchOff;
			switchInfo(INFOTYPE::NOINFO);
			break;
		case SELECT_SABOTAGE_SELL:
			vUi->switchCursor(vUi->CursorType::Sell);
			setActiveButton("sabotageSell");
			selectedAction = IViewBuilding::sell;
			switchInfo(INFOTYPE::NOINFO);
			break;

		case INGAME_MENU_OPEN:
			getContainer("DialogBox")->switchOn();
			break;

		case INGAME_MENU_CLOSE:
			getContainer("DialogBox")->switchOff();
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

	VSoundLoader::playBackgroundMusicIngame();
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

void VScreenIngame::checkSpecialEvent()
{
	if (vUi->m_zkCursor.ButtonPressedRight())
	{
		if (activeButton != nullptr)
		{
			vUi->switchCursor(vUi->CursorType::Default);
			activeButton->setActive(false);


			switchInfo(NOINFO);

			if (selectedBuilding != VIdentifier::Undefined)

			{
				selectedBuilding = VIdentifier::Undefined;
				updateModelView();
			}

			activeButton = nullptr;
		}
	}
}

void VScreenIngame::updateMoney(const int wert, LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
	CASTD<VText*>(getContainer("Topbar")->getGuiObject("moneyValue"))->updateText(std::to_string(wert));
	else
	CASTD<VText*>(getContainer("Topbar")->getGuiObject("moneyValueEnemy"))->updateText(std::to_string(wert));
}

void VScreenIngame::updatePopulation(const int wert)
{
	CASTD<VText*>(getContainer("Topbar")->getGuiObject("popValue"))->updateText(std::to_string(wert));
}

void VScreenIngame::updateAddedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	switch (id)
	{
		case LIdentifier::LCoalPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_COALPOWERPLANT]++ : statPlacedBuildingsEnemy[BUILDING_COALPOWERPLANT]++;
			break;
		case LIdentifier::LHydroelectricPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_HYDROPOWERPLANT]++ : statPlacedBuildingsEnemy[BUILDING_HYDROPOWERPLANT]++;
			break;
		case LIdentifier::LNuclearPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_NUCLEARPOWERPLANT]++ : statPlacedBuildingsEnemy[BUILDING_NUCLEARPOWERPLANT]++;
			break;
		case LIdentifier::LOilRefinery:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_OILPOWERPLANT]++ : statPlacedBuildingsEnemy[BUILDING_OILPOWERPLANT]++;
			break;
		case LIdentifier::LSolarPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_SOLARPOWERPLANT]++ : statPlacedBuildingsEnemy[BUILDING_SOLARPOWERPLANT]++;
			break;
		case LIdentifier::LWindmillPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_WINDMILL]++ : statPlacedBuildingsEnemy[BUILDING_WINDMILL]++;
			break;
		case LIdentifier::LPowerLine:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_POWERLINE]++ : statPlacedBuildingsEnemy[BUILDING_POWERLINE]++;
			break;
		default: break;
	}

	updatePowerPlants();
}

void VScreenIngame::updateRemovedPowerPlant(const LIdentifier::LIdentifier id, const LPlayer::PlayerId playerId)
{
	switch (id)
	{
		case LIdentifier::LCoalPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_COALPOWERPLANT]-- : statPlacedBuildingsEnemy[BUILDING_COALPOWERPLANT]--;
			break;
		case LIdentifier::LHydroelectricPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_HYDROPOWERPLANT]-- : statPlacedBuildingsEnemy[BUILDING_HYDROPOWERPLANT]--;
			break;
		case LIdentifier::LNuclearPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_NUCLEARPOWERPLANT]-- : statPlacedBuildingsEnemy[BUILDING_NUCLEARPOWERPLANT]--;
			break;
		case LIdentifier::LOilRefinery:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_OILPOWERPLANT]-- : statPlacedBuildingsEnemy[BUILDING_OILPOWERPLANT]--;
			break;
		case LIdentifier::LSolarPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_SOLARPOWERPLANT]-- : statPlacedBuildingsEnemy[BUILDING_SOLARPOWERPLANT]--;
			break;
		case LIdentifier::LWindmillPowerPlant:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_WINDMILL]-- : statPlacedBuildingsEnemy[BUILDING_WINDMILL]--;
			break;
		case LIdentifier::LPowerLine:
			playerId == LPlayer::PlayerId::Local ? statPlacedBuildings[BUILDING_POWERLINE]-- : statPlacedBuildingsEnemy[BUILDING_POWERLINE]--;
			break;
		default: break;
	}

	updatePowerPlants();
}


void VScreenIngame::updateNumberPowerLines(const int newNumberPowerLines, const LPlayer::PlayerId playerId)
{
	if (playerId == LPlayer::Local)
		statPlacedBuildings[BUILDING_POWERLINE] = newNumberPowerLines;
	else
		statPlacedBuildingsEnemy[BUILDING_POWERLINE] = newNumberPowerLines;
}

void VScreenIngame::updatePowerPlants()
{
	//VTab * tabStatistics = CASTD<VRegister *>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics");
	for (const std::pair<BUILDINGTYPE, int>& plant : statPlacedBuildings)
	{
		if (plant.first != BUILDING_POWERLINE)
		{
			if (plant.second < 10)
			CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first]))->updateText("0" + std::to_string(plant.second));
			else
			CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first]))->updateText(std::to_string(plant.second));
		}
	}

	for (const std::pair<BUILDINGTYPE, int>& plant : statPlacedBuildingsEnemy)
	{
		if (plant.first != BUILDING_POWERLINE)
		{
			if (plant.second < 10)
			CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first] + "enemy"))->updateText("0" + std::to_string(plant.second));
			else
			CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first] + "enemy"))->updateText(std::to_string(plant.second));
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

int VScreenIngame::getNumberofBuildings(const LPlayer::PlayerId playerId)
{
	int count = 0;
	for (const std::pair<BUILDINGTYPE, int>& plant : (playerId == LPlayer::Local) ? statPlacedBuildings : statPlacedBuildingsEnemy)
	{
		if (plant.first != BUILDING_POWERLINE)
		{
			if (plant.second > 0)
				count++;
		}
	}
	return count;
}

void VScreenIngame::updateOwnGraphRatio(float fRatio)
{
	if (fRatio == 0 && getNumberofBuildings(LPlayer::Local) == 0)
	{
		m_vgGraphEnergyRatioOwn->disable();
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("ownGraphTextTop"))->updateText("0%");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("ownGraphTextBottom"))->updateText("0%");
		return;
	}
	m_vgGraphEnergyRatioOwn->enable();

	int regenerative = (fRatio) * 100;
	int fossile = 100 - fRatio * 100;

	m_vgGraphEnergyRatioOwn->updateValue(fRatio);
	CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("ownGraphTextTop"))->updateText(std::to_string(regenerative) + "%");
	CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("ownGraphTextBottom"))->updateText(std::to_string(fossile) + "%");
}

void VScreenIngame::updateEnemyGraphRatio(float fRatio)
{
	if (fRatio == 0 && getNumberofBuildings(LPlayer::Remote) == 0)
	{
		m_vgGraphEnergyRatioEnemy->disable();
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("enemyGraphTextTop"))->updateText("0%");
		CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("enemyGraphTextBottom"))->updateText("0%");
		return;
	}
	m_vgGraphEnergyRatioEnemy->enable();

	int regenerative = (fRatio) * 100;
	int fossile = 100 - fRatio * 100;

	m_vgGraphEnergyRatioEnemy->updateValue(fRatio);
	CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("enemyGraphTextTop"))->updateText(std::to_string(regenerative) + "%");
	CASTD<VText*>(getContainer("BottomBar")->getContainer("Bars")->getGuiObject("enemyGraphTextBottom"))->updateText(std::to_string(fossile) + "%");
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
		if (tempGuicontainer->getGuiContainerMap().size() > 0)
		{
			checkGUIContainer(ContainerPair.second);
		}
	}
}

void VScreenIngame::resize(const int /*width*/, const int /*height*/)
{
	m_viewport->ReSize();
}

void VScreenIngame::handleInput(const float fTimeDelta)
{
	//Models view
	float direction = 1.0f;

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

	const float cameraSlower_ctrl = 4.0f;
	float cameraStrength = 20.0f * fTimeDelta;

	//Normal movement
	const float cameraMovementLeftRightMin = -40.0f;
	const float cameraMovementLeftRightMax = 40.0f;
	const float cameraMovementBackForwardMin = -5.0f;
	const float cameraMovementBackForwardMax = 80.0f;
	float cameraMovementLeftRight = 0.0f;
	float cameraMovementBackForward = 0.0f;

	//Left + Right:
	if (vUi->m_zkKeyboard.KeyPressed(DIK_A))
	{
		cameraMovementLeftRight = -cameraStrength;
	}
	else if (vUi->m_zkKeyboard.KeyPressed(DIK_D))
	{
		cameraMovementLeftRight = cameraStrength;
	}

	//Back + Forward
	if (vUi->m_zkKeyboard.KeyPressed(DIK_S))
	{
		cameraMovementBackForward = -cameraStrength;
	}
	else if (vUi->m_zkKeyboard.KeyPressed(DIK_W))
	{
		cameraMovementBackForward = cameraStrength;
	}

	//Slower movement on left ctrl
	if (vUi->m_zkKeyboard.KeyPressed(DIK_LCONTROL))
	{
		cameraMovementLeftRight /= cameraSlower_ctrl;
		cameraMovementBackForward /= cameraSlower_ctrl;
	}

	//Check boundaries
	if (cameraMovementLeftRight < 0 && cameraMovementPositionLeftRight + cameraMovementLeftRight < cameraMovementLeftRightMin)
	{
		cameraMovementLeftRight = cameraMovementLeftRightMin - cameraMovementPositionLeftRight;
	}
	else if (cameraMovementLeftRight > 0 && cameraMovementPositionLeftRight + cameraMovementLeftRight > cameraMovementLeftRightMax)
	{
		cameraMovementLeftRight = cameraMovementLeftRightMax - cameraMovementPositionLeftRight;
	}

	if (cameraMovementBackForward < 0 && cameraMovementPositionBackForward + cameraMovementBackForward < cameraMovementBackForwardMin)
	{
		cameraMovementBackForward = cameraMovementBackForwardMin - cameraMovementPositionBackForward;
	}
	else if (cameraMovementBackForward > 0 && cameraMovementPositionBackForward + cameraMovementBackForward > cameraMovementBackForwardMax)
	{
		cameraMovementBackForward = cameraMovementBackForwardMax - cameraMovementPositionBackForward;
	}

	//Apply movement
	m_zpCamera.TranslateXDelta(cameraMovementLeftRight);
	m_zpCamera.TranslateYDelta(cameraMovementBackForward);
	cameraMovementPositionLeftRight += cameraMovementLeftRight;
	cameraMovementPositionBackForward += cameraMovementBackForward;

	//Zoom In + Out
	const float cameraZoomMin = -26.0f;
	const float cameraZoomMax = 10.0f;
	const float cameraZoomFactor = 2.0f;
	float cameraZoom = 0.0f;

	//Calculate the zoom value
	if (vUi->m_zkKeyboard.KeyPressed(DIK_UP))
	{
		if (cameraZoomPosition > cameraZoomMin)
		{
			cameraZoom = -cameraStrength * cameraZoomFactor;
		}
	}
	else if (vUi->m_zkKeyboard.KeyPressed(DIK_DOWN))
	{
		if (cameraZoomPosition < cameraZoomMax)
		{
			cameraZoom = cameraStrength * cameraZoomFactor;
		}
	}
	else if (vUi->m_zkMouse.GetRelativeZ() != 0.0f)
	{
		if (vUi->m_zkMouse.GetRelativeZ() > 0.0f)
		{
			if (cameraZoomPosition > cameraZoomMin)
			{
				cameraZoom = -cameraStrength * cameraZoomFactor;
			}
		}
		else
		{
			if (cameraZoomPosition < cameraZoomMax)
			{
				cameraZoom = cameraStrength * cameraZoomFactor;
			}
		}
	}

	//Slower zoom on left ctrl
	if (vUi->m_zkKeyboard.KeyPressed(DIK_LCONTROL))
	{
		cameraZoom /= cameraSlower_ctrl * cameraSlower_ctrl;
	}

	//Check if scroll would pass the boundaries
	if (cameraZoom > 0 && cameraZoomPosition + cameraZoom > cameraZoomMax)
	{
		cameraZoom = cameraZoomMax - cameraZoomPosition; //e. g. cameraZoomPosition = 8; cameraZoomMax = 10; cameraZoom = 4 => 10 - 8 = 2
	}
	else if (cameraZoom < 0 && cameraZoomPosition + cameraZoom < cameraZoomMin)
	{
		cameraZoom = cameraZoomMin - cameraZoomPosition; //e. g. cameraZoomPosition = -20; cameraZoomMin = -24 cameraZoom = -5 => -24 - -20 = -4
	}

	//Apply the camera zoom
	m_zpCamera.TranslateZDelta(cameraZoom);
	cameraZoomPosition += cameraZoom;

	//Flip View
	const float cameraFlipAngleMax = 1.0f;
	const float cameraFlipAngleMin = -1.0f;
	const float cameraFlipFactor = 0.1f;
	float cameraFlip = 0.0f;

	if (vUi->m_zkKeyboard.KeyPressed(DIK_E))
	{
		if (cameraFlipPosition < cameraFlipAngleMax)
		{
			cameraFlip = cameraStrength * cameraFlipFactor;
		}
	}
	else if (vUi->m_zkKeyboard.KeyPressed(DIK_Q))
	{
		if (cameraFlipPosition > cameraFlipAngleMin)
		{
			cameraFlip = -cameraStrength * cameraFlipFactor;
		}
	}
	else
	{
		//Move back
		if (cameraFlipPosition < 0)
		{
			cameraFlip = cameraStrength * cameraFlipFactor;

			if (cameraFlipPosition + cameraFlip > 0)
			{
				cameraFlip = -cameraFlipPosition;
			}
		}
		else if (cameraFlipPosition > 0)
		{
			cameraFlip = -cameraStrength * cameraFlipFactor;

			if (cameraFlipPosition + cameraFlip < 0)
			{
				cameraFlip = -cameraFlipPosition;
			}
		}
	}

	//Slower flip on left ctrl
	if (vUi->m_zkKeyboard.KeyPressed(DIK_LCONTROL))
	{
		cameraFlip /= cameraSlower_ctrl * cameraSlower_ctrl;
	}

	//Check if flip would pass the boundaries
	if (cameraFlip > 0 && cameraFlipPosition + cameraFlip > cameraFlipAngleMax)
	{
		cameraFlip = cameraFlipAngleMax - cameraFlipPosition;
	}
	else if (cameraFlip < 0 && cameraFlipPosition + cameraFlip < cameraFlipAngleMin)
	{
		cameraFlip = cameraFlipAngleMin - cameraFlipPosition;
	}

	//Apply the flip
	m_zpCamera.TranslateXDelta(-cameraMovementPositionLeftRight);
	m_zpCamera.TranslateYDelta(-cameraMovementPositionBackForward);
	m_zpCamera.RotateZDelta(cameraFlip);
	m_zpCamera.TranslateYDelta(cameraMovementPositionBackForward);
	m_zpCamera.TranslateXDelta(cameraMovementPositionLeftRight);
	cameraFlipPosition += cameraFlip;

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
	if (m_CooldownPowerLineCut)
	{
		cooldownRemove += fTimeDelta;
		if (cooldownRemove > LBalanceLoader::getSabotageCooldown(LSabotage::Remove))
		{
			stopCooldown(INTERACTIONS::SABOTAGE_CUTPOWERLINE);
		}
	}
	if (m_CooldownStrike)
	{
		cooldownDeactivate += fTimeDelta;
		if (cooldownDeactivate > LBalanceLoader::getSabotageCooldown(LSabotage::Deactivate))
		{
			stopCooldown(INTERACTIONS::SABOTAGE_STRIKE);
		}
	}
	if (m_CooldownHalfResource)
	{
		cooldownResource += fTimeDelta;
		if (cooldownResource > LBalanceLoader::getSabotageCooldown(LSabotage::Resource))
		{
			stopCooldown(INTERACTIONS::SABOTAGE_HALF);
		}
	}

	if (!vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = false;
	}

	handleInput(fTimeDelta);

	std::unordered_map<std::string, IViewGUIContainer*> tempGuiContainer;

	checkShortcut(&vUi->m_zkKeyboard);
	checkSpecialEvent();
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
	modelCoal.moveLore(VMaterialLoader::getRotationPerTick(VIdentifier::VCoalPowerPlant, fTimeDelta));
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
{}

void VScreenIngame::StartEvent()
{}

void VScreenIngame::EndEvent()
{}

std::unordered_map<std::string, IViewGUIObject*> VScreenIngame::getScreenObjects()
{
	std::unordered_map<std::string, IViewGUIObject*> resultObjectList;

	for (std::pair<std::string, IViewGUIContainer*> container : m_Guicontainer)
	{
		std::unordered_map<std::string, IViewGUIObject*> tempMap = getObjects(container.second);
		if (!tempMap.empty())
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

void VScreenIngame::stopCooldown(const INTERACTIONS interaction)
{
	switch (interaction)
	{
		case SABOTAGE_CUTPOWERLINE:
			m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOff();
			VMaterialLoader::materialAnimSabotageCutPowerline.SetAni(30, 2, 0);
			m_CooldownPowerLineCut = false;

			if (vrRegister->getActiveTab()->getName() == "TabSabotage")
				m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOn();
			break;
		case SABOTAGE_STRIKE:
			m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOff();
			VMaterialLoader::materialAnimSabotageStrike.SetAni(45, 2, 0);
			m_CooldownStrike = false;

			if (vrRegister->getActiveTab()->getName() == "TabSabotage")
				m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOn();
			break;
		case SABOTAGE_HALF:
			m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOff();
			VMaterialLoader::materialAnimSabotageHalfResource.SetAni(60, 2, 0);
			m_CooldownHalfResource = false;

			if (vrRegister->getActiveTab()->getName() == "TabSabotage")
				m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOn();
			break;
	}
}

void VScreenIngame::startCooldown(const INTERACTIONS interaction)
{
	switch (interaction)
	{
		case SABOTAGE_CUTPOWERLINE:
			m_CooldownPowerLineCut = true;
			cooldownRemove = 0.0f;
			m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->switchOff();
			if (!m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->IsNode2D())
				m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut"));
			m_vtTabSabotage->getOverlay("CooldownSabotagePowerLineCut")->SwitchOn();
			VMaterialLoader::materialAnimSabotageCutPowerline.SetAni(30, 2, 60.0f / LBalanceLoader::getSabotageCooldown(LSabotage::Remove));
			break;
		case SABOTAGE_STRIKE:
			m_CooldownStrike = true;
			cooldownDeactivate = 0.0f;
			m_vtTabSabotage->getGuiObject("sabotageStrike")->switchOff();
			if (!m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->IsNode2D())
				m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageStrike"));
			m_vtTabSabotage->getOverlay("CooldownSabotageStrike")->SwitchOn();
			VMaterialLoader::materialAnimSabotageStrike.SetAni(45, 2, 90.0f / LBalanceLoader::getSabotageCooldown(LSabotage::Deactivate));
			break;
		case SABOTAGE_HALF:
			m_CooldownHalfResource = true;
			cooldownResource = 0.0f;
			m_vtTabSabotage->getGuiObject("sabotageHalf")->switchOff();
			if (!m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->IsNode2D())
				m_viewport->AddOverlay(m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource"));
			m_vtTabSabotage->getOverlay("CooldownSabotageHalfResource")->SwitchOn();
			VMaterialLoader::materialAnimSabotageHalfResource.SetAni(60, 2, 120.0f / LBalanceLoader::getSabotageCooldown(LSabotage::Resource));
			break;
	}
}

void VScreenIngame::setSabotageNumber(const int value)
{
	CASTD<VText*>(m_vtTabSabotage->getGuiObject("SabotageNumLeft"))->updateText(std::to_string(value));
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
			lastClickPosition = std::make_pair(x, y);

			if (selectedBuilding == VIdentifier::Undefined && selectedAction == IViewBuilding::Undefined)
			{
				if (m_fieldValueStorage.count(std::make_pair(x, y)) > 0)
				{
					m_fieldValueStorage.at(std::make_pair(x, y)).showContextInfo();
				}
				else
				{
					m_fieldValueStorage.emplace(std::piecewise_construct, std::make_tuple(std::make_pair(x, y)), std::make_tuple(this));
				}
			}

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

	if (vbuilding->getLBuilding() == nullptr || vbuilding->getLBuilding()->getPlayerId() != LPlayer::PlayerId::Remote)
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
	if (vbuilding->getLBuilding() == nullptr || vbuilding->getLBuilding()->getPlayerId() != LPlayer::PlayerId::Local)
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
			if (vbuilding->clicked(selectedAction))
			{
				vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
				return true;
			}

			return false;

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
	if (m_vtTabSabotage == nullptr)
	{
		return;
	}

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
	m_vtTabSabotage->getGuiObject("HeaderSabNum")->switchOn();
	m_vtTabSabotage->getGuiObject("SabotageNumLeft")->switchOn();
}

void VScreenIngame::SabotageTabSwitchOff()
{
	if (m_vtTabSabotage == nullptr)
	{
		return;
	}

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
	m_vtTabSabotage->getGuiObject("HeaderSabNum")->switchOff();
	m_vtTabSabotage->getGuiObject("SabotageNumLeft")->switchOff();
}

void VScreenIngame::updateFieldStorageValue(std::pair<int, int> pos, const std::string& name, const std::string& wert)
{
	if (m_fieldValueStorage.count(pos) > 0)
	{
		m_fieldValueStorage.at(pos).updateValue(name, wert);
	}
	else
	{
		m_fieldValueStorage.emplace(std::piecewise_construct, std::make_tuple(pos), std::make_tuple(this));
		m_fieldValueStorage.at(pos).updateValue(name, wert);
	}

	if (selectedBuilding == VIdentifier::Undefined && selectedAction == IViewBuilding::Undefined)
	{
		//update context menu when building is still selected
		if (pos == lastClickPosition)
		{
			if (m_fieldValueStorage.count(pos) > 0)
			{
				m_fieldValueStorage.at(pos).showContextInfo();
			}
			else
			{
				m_fieldValueStorage.emplace(std::piecewise_construct, std::make_tuple(pos), std::make_tuple(this));
			}
		}
	}
}

void VScreenIngame::switchInfo(INFOTYPE infoType)
{
	if (activeInfo != nullptr)
		activeInfo->switchOff();
	switch (infoType)
	{
		case CRAFTBUILDING:
			activeInfo = getContainer("BottomBar")->getContainer("Infofield")->getContainer("BuildingCraftInfo");
			activeInfo->switchOn();
			break;
		case FIELDINFO:
			activeInfo = getContainer("BottomBar")->getContainer("Infofield")->getContainer("FieldInfo");
			activeInfo->switchOn();
			break;
		case SABOTAGEINFO:
			activeInfo = getContainer("BottomBar")->getContainer("Infofield")->getContainer("SabotageInfo");
			activeInfo->switchOn();
			break;
		case NOINFO:
			activeInfo = nullptr;
			break;
	}
}

void VScreenIngame::updateSabotageCost(LSabotage::LSabotage sabotageType, const int value)
{
	switch (sabotageType)
	{
	case LSabotage::LSabotage::Deactivate :
		m_DeactivateCost = value;
		break;
	case LSabotage::LSabotage::Resource:
		m_ResourceCost = value;
		break;
	case LSabotage::LSabotage::Remove:
		m_RemoveCost = value;
		break;
	}
}

void VScreenIngame::addToScene(CPlacement* placement)
{
	m_scene.AddPlacement(placement);
}

NAMESPACE_VIEW_E
