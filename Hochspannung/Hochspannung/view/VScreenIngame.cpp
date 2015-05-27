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
#include "VSoundLoader.h"
#include "VPowerLine.h"
#include "../logic/LBalanceLoader.h"

NAMESPACE_VIEW_B


VScreenIngame::VScreenIngame(VUI* vUi)
	: IViewScreen(vUi)
{
	m_viewport = new CViewport();
	//Standard Init
	m_zc.Init();
	m_zb.InitFull("textures/3d-office-wallpaper.jpg");

	m_viewport->AddBackground(&m_zb);
	m_viewport->InitFull(&m_zc);


	//Detailled model view
	m_zmbackgroundModels.InitFull(&VMaterialLoader::materialDefaultBackground);
	m_CamModels.Init();
	m_zlModels.Init(CHVector(1.0F, 1.0F, 1.0F),
	                CColor(1.0F, 1.0F, 1.0F));
	m_zpModels.AddCamera(&m_CamModels);
	m_sceneModels.AddParallelLight(&m_zlModels);
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

	for (const std::pair<VIdentifier::VIdentifier, IViewModel*>& p : models)
	{
		p.second->initViewModel(nullptr);
	}

	m_zl.Init(CHVector(1.0F, 1.0F, 1.0F),
	          CColor(1.0F, 1.0F, 1.0F));

	m_scene.AddParallelLight(&m_zl);
	m_scene.AddPlacement(&m_zpCamera);

	vUi->m_zf.AddViewport(m_viewport);

	vUi->m_zr.AddScene(&m_scene);
	vUi->m_zr.AddScene(&m_sceneModels);

	DEBUG_EXPRESSION(m_zpCamera.SetName("#Placement Camera"));
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.TranslateZ(50.0F);
	m_zpCamera.RotateXDelta(0.15F * PI);
	m_zpCamera.RotateZDelta(0.15F);

	VSoundLoader::init(&m_scene);
	VSoundLoader::playBackgroundMusicIngame();

	//Bottom Bar

	/*m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport.AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);*/

	// initialize statistics constants and string mappings for power plants
	m_powerPlantsNameMapping[BUILDING_HYDROPOWERPLANT]   = "countHydro";
	m_powerPlantsNameMapping[BUILDING_SOLARPOWERPLANT]   = "countSolar";
	m_powerPlantsNameMapping[BUILDING_NUCLEARPOWERPLANT] = "countNuclear";
	m_powerPlantsNameMapping[BUILDING_COALPOWERPLANT]    = "countCoal";
	m_powerPlantsNameMapping[BUILDING_OILPOWERPLANT]     = "countOil";
	m_powerPlantsNameMapping[BUILDING_WINDMILL]          = "countWind";



	/********************************************************TOP AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.1F, 0.0F, 0.8F, 0.05F), &VMaterialLoader::materialTopbar, "Topbar");
	//getContainer("Topbar")->addText(CFloatRect(0.10F, 0.2F, 0.2F, 0.65F), &VMaterialLoader::standardFont, "Bevoelkerung:", "population");
	getContainer("Topbar")->addOverlay(CFloatRect(0.1F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconPopulation, "TopPopulationIcon");
	getContainer("Topbar")->addText(CFloatRect(0.201F, 0.1F, 0.15F, 0.9F), &VMaterialLoader::standardFont, "0000", "popValue");
	//getContainer("Topbar")->addText(CFloatRect(0.50F, 0.2F, 0.2F, 0.65F), &VMaterialLoader::GoldFont, "Geld:", "money");
	getContainer("Topbar")->addOverlay(CFloatRect(0.50F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconMoney, "TopMoneyIcon");
	getContainer("Topbar")->addText(CFloatRect(0.601F, 0.2F, 0.2F, 0.85F), &VMaterialLoader::GoldFont, "0000", "moneyValue");

	getContainer("Topbar")->getGuiObject("popValue")->setLayer(0.1F);
	getContainer("Topbar")->getGuiObject("moneyValue")->setLayer(0.1F);

	getContainer("Topbar")->getOverlay("TopPopulationIcon")->SetLayer(0.1F);
	getContainer("Topbar")->getOverlay("TopMoneyIcon")->SetLayer(0.1F);

	/********************************************************BOTTOM AREA*************************************************************/
	//addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 0.75F, 1.0F, 0.25F), "BottomBar");
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 150, vUi->m_zf.m_iWidthWindow, 150), "BottomBar");


	/********************************************************Infofield AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.00F, 0.00F, 0.22F, 1.0F), &VMaterialLoader::materialInfofieldBackground, "Infofield");
	//getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.01F, 0.3F, 0.80F, 0.1F), &VMaterialLoader::standardFont, "Infofeld", "infoText");
	//getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText")->setLayer(0.2F);

	getContainer("BottomBar")->getContainer("Infofield")->addViewport(&m_viewportModels, &m_CamModels, CFloatRect(0.1F, 0.2F, 0.75F, 0.4F), &m_zmbackgroundModels,"DetailedModels");
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.10F, 0.65F, 0.60F, 0.13F), &VMaterialLoader::standardFont, "100", "PowerInfo");
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.10F, 0.83F, 0.6F, 0.13F), &VMaterialLoader::standardFont, "1000", "MoneyInfo");
	getContainer("BottomBar")->getContainer("Infofield")->addOverlay(CFloatRect(0.65F, 0.65F, 0.25, 0.13F), &VMaterialLoader::materialIngameIconEnergy, "EngergyInfoIcon");
	getContainer("BottomBar")->getContainer("Infofield")->addOverlay(CFloatRect(0.65F, 0.83F, 0.25, 0.13F), &VMaterialLoader::materialIngameIconMoney, "MoneyInfoIcon");

	getContainer("BottomBar")->getContainer("Infofield")->setLayer(0.2F);
	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOff();
	getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOff();
	vUi->m_zf.AddViewport(&m_viewportModels);
	/********************************************************Baumenu AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.22F, 0.00F, 0.51F, 1.0F), &VMaterialLoader::m_zmCraftMenueBackground, "Craftmenu");
	getContainer("BottomBar")->getContainer("Craftmenu")->addContainer(IViewGUIContainer::ContainerType::Register, CFloatRect(0.00F, 0.105F, 1.0F, 0.895F), "Register");

	VRegister* vrRegister = CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"));
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonCraftmenu, &VMaterialLoader::materialIngameButtonCraftmenuHover, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_BUILDING, "TabBuilding");
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonSabotage, &VMaterialLoader::materialIngameButtonSabotageHover, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_SABOTAGE, "TabSabotage");
	vrRegister->addTab(&VMaterialLoader::materialIngameButtonStatistics, &VMaterialLoader::materialIngameButtonStatisticsHover, &VMaterialLoader::materialDefaultBackground, SWITCH_TO_REGISTER_STATISTICS, "TabStatistics");
	vrRegister->setLayer(0.7);

	// Tabs
	m_vtTabStatistics = CASTD<VRegister*>(vrRegister)->getTab("TabStatistics");
	m_vtTabSabotage = CASTD<VRegister*>(vrRegister)->getTab("TabSabotage");
	m_vtTabBuilding = CASTD<VRegister*>(vrRegister)->getTab("TabBuilding");

	getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register")->setLayer(0.7F);

	//CraftMenu
	m_vtTabBuilding->addButton(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonWindmill, &VMaterialLoader::materialCraftmenuButtonWindmillHover, SELECT_BUILDING_WINDMILL, "windmill");
	m_vtTabBuilding->addButton(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, &VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover, SELECT_BUILDING_HYDROPOWERPLANT, "hydroPowerPlant");
	m_vtTabBuilding->addButton(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, &VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover, SELECT_BUILDING_SOLARPOWERPLANT, "solarPowerPlant");
	m_vtTabBuilding->addButton(CFloatRect(0.025F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, &VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover, SELECT_BUILDING_NUCLEARPOWERPLANT, "nuclearPowerPlant");
	m_vtTabBuilding->addButton(CFloatRect(0.275F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, &VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover, SELECT_BUILDING_COALPOWERPLANT, "coalPowerPlant");
	m_vtTabBuilding->addButton(CFloatRect(0.525F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, &VMaterialLoader::materialCraftmenuButtonOilPowerplantHover, SELECT_BUILDING_OILPOWERPLANT, "oilPowerPlant");
	m_vtTabBuilding->addButton(CFloatRect(0.775F, 0.525F, 0.20F, 0.4F), &VMaterialLoader::materialCraftmenuButtonPowerline, &VMaterialLoader::materialCraftmenuButtonPowerlineHover, SELECT_BUILDING_POWERLINE, "powerLine");

	m_vtTabBuilding->getGuiObject("windmill")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("hydroPowerPlant")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("solarPowerPlant")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("coalPowerPlant")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("oilPowerPlant")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("nuclearPowerPlant")->setLayer(0.2F);
	m_vtTabBuilding->getGuiObject("powerLine")->setLayer(0.2F);

	m_vtTabSabotage->addButton(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonScissors, &VMaterialLoader::materialSabotageButtonScissorsHover, SELECT_SABOTAGE_POWERLINECUT, "sabotagePowerlineCut");
	m_vtTabSabotage->addButton(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonStrike, &VMaterialLoader::materialSabotageButtonStrikeHover, SELECT_SABOTAGE_STRIKE, "sabotageStrike");
	m_vtTabSabotage->addButton(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialSabotageButtonBomb, &VMaterialLoader::materialSabotageButtonBombHover, SELECT_SABOTAGE_BOMB, "sabotageBomb");


	m_vtTabSabotage->getGuiObject("sabotagePowerlineCut")->setLayer(0.2F);
	m_vtTabSabotage->getGuiObject("sabotageStrike")->setLayer(0.2F);
	m_vtTabSabotage->getGuiObject("sabotageBomb")->setLayer(0.2F);
	//m_vtTabSabotage->getGuiObject("TurnOffPowerPlant")->setLayer(0.2F);

	// Tab for statistics
	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.175f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonWindmill, "statisticWind");
	m_vtTabStatistics->addText(CFloatRect(0.16f, 0.2f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_WINDMILL]);

	m_vtTabStatistics->addOverlay(CFloatRect(0.26f, 0.175f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, "statisticHydro");
	m_vtTabStatistics->addText(CFloatRect(0.37f, 0.2f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_HYDROPOWERPLANT]);

	m_vtTabStatistics->addOverlay(CFloatRect(0.51f, 0.175f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, "statisticSolar");
	m_vtTabStatistics->addText(CFloatRect(0.62f, 0.2f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_SOLARPOWERPLANT]);

	m_vtTabStatistics->addOverlay(CFloatRect(0.05f, 0.625f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, "statisticNuclear");
	m_vtTabStatistics->addText(CFloatRect(0.16f, 0.65f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_NUCLEARPOWERPLANT]);

	m_vtTabStatistics->addOverlay(CFloatRect(0.26f, 0.625f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, "statisticCoal");
	m_vtTabStatistics->addText(CFloatRect(0.37f, 0.65f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_COALPOWERPLANT]);

	m_vtTabStatistics->addOverlay(CFloatRect(0.51f, 0.625f, 0.1f, 0.2f), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, "statisticOil");
	m_vtTabStatistics->addText(CFloatRect(0.62f, 0.65f, 0.1f, 0.2f), &VMaterialLoader::standardFont, "00", m_powerPlantsNameMapping[BUILDING_OILPOWERPLANT]);

	// Renewable / fossil energy Statistics
	m_vtTabStatistics->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.74F, 0.175F, 0.1F, 0.6F), &VMaterialLoader::materialRed, "RenFosEnergyContainer");
	m_vgGraphEnergyRatio = m_vtTabStatistics->getContainer("RenFosEnergyContainer")->addGraphRatio(CFloatRect(0, 0, 1, 1), "renfosRatio", &VMaterialLoader::materialGreen);
	m_vtTabStatistics->getContainer("RenFosEnergyContainer")->setLayer(0.2F);

	m_vgGraphEnergyRatio->toggleType();
	updateGraphRatio(0.9f);

	m_vtTabSabotage->switchOff();
	m_vtTabStatistics->switchOff();


	/********************************************************Minimap AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.73F, 0.01F, 0.27F, 1.0F), &VMaterialLoader::materialMinimapBackground, "Minimap");
	getContainer("BottomBar")->getContainer("Minimap")->addText(CFloatRect(0.01F, 0.3F, 0.80F, 0.1F), &VMaterialLoader::standardFont, "Minimap", "MinimapText");
	getContainer("BottomBar")->getContainer("Minimap")->getGuiObject("MinimapText")->setLayer(0.2F);
	getContainer("BottomBar")->getContainer("Minimap")->setLayer(0.2F);

	/***********************************************************Dialog******************************************************************/
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33F, 0.10F, 0.30F, 0.55F), &VMaterialLoader::materialIngameMenueDialogBackground, "DialogBox");


	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.10F, 0.80F, 0.15F), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING, "MenueButtonContinue");
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.27F, 0.80F, 0.15F), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "MenueButtonQuit");
	getContainer("DialogBox")->addButton(CFloatRect(0.10F, 0.44F, 0.80F, 0.15F), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "MenueButtonBack");

	getContainer("DialogBox")->getGuiObject("MenueButtonContinue")->setLayer(0.1F);
	getContainer("DialogBox")->getGuiObject("MenueButtonQuit")->setLayer(0.1F);
	getContainer("DialogBox")->getGuiObject("MenueButtonBack")->setLayer(0.1F);

	/********************************************************Energy AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.74F, 0.03F, 0.05F, 1.0F), &VMaterialLoader::materialLightGrey, "Energy");
	getContainer("BottomBar")->getContainer("Energy")->setLayer(0.1F);
	m_vgGraphEnergy = getContainer("BottomBar")->getContainer("Energy")->addGraph(CFloatRect(0, 0, 1, 1), "energyGraph"); // ->addOverlay(CFloatRect(0.5F, 0.4F, 0.5F, 0.6F), &VMaterialLoader::materialRed, "NeededEnergy");
	m_vgGraphEnergy->addBar("neededEnergy", &VMaterialLoader::materialRed);
	m_vgGraphEnergy->addBar("producedEnergy", &VMaterialLoader::materialGreen);
	m_vgGraphEnergy->updateBar2("neededEnergy", 10);
	m_vgGraphEnergy->updateBar2("producedEnergy", 50);

	//CFloatRect iwas = getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 100, vUi->m_zf.m_iWidthWindow, 100);

	m_viewport->SwitchOff();
	getContainer("DialogBox")->switchOff();
}

VScreenIngame::~VScreenIngame()
{}

void VScreenIngame::onNotify(const Event& events)
{
	switch (events)
	{
		case SWITCH_TO_REGISTER_BUILDING:
			m_vtTabBuilding->switchOn();
			m_vtTabSabotage->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
			break;

		case SWITCH_TO_REGISTER_SABOTAGE:
			m_vtTabBuilding->switchOff();
			m_vtTabSabotage->switchOn();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
			break;
		case SWITCH_TO_REGISTER_STATISTICS:
			m_vtTabBuilding->switchOff();
			m_vtTabSabotage->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOn();
			// TODO get stats and update statistics here
			updatePowerPlants({{BUILDINGTYPE::BUILDING_WINDMILL, 11},{BUILDINGTYPE::BUILDING_OILPOWERPLANT, 15}}); // testing
			break;

		case SELECT_BUILDING_WINDMILL:
			updateInfofield("Windmill");
			m_selectedBuilding = VIdentifier::VWindmillPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);
			setActiveButton("windmill");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LWindmillPowerPlant)));
			//CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo"))->updateText();
			
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			
			//TODO BuildMenue Button Windmill 
			break;
		case SELECT_BUILDING_COALPOWERPLANT:
			updateInfofield("CoalPowerplant");
			m_selectedBuilding = VIdentifier::VCoalPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);
			//TODO BuildMenue Button CoalPowerplant 
			setActiveButton("coalPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LCoalPowerPlant)));
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;
		case SELECT_BUILDING_OILPOWERPLANT:
			updateInfofield("OilPowerplant");
			m_selectedBuilding = VIdentifier::VOilRefinery;
			vUi->switchCursor(vUi->CursorType::Hammer);
			//TODO BuildMenue Button Oilpowerplant
			setActiveButton("oilPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LOilRefinery)));
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;
		case SELECT_BUILDING_NUCLEARPOWERPLANT:
			updateInfofield("NuclearPowerplant");
			m_selectedBuilding = VIdentifier::VNuclearPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);
			//TODO BuildMenue Button Nuclearpowerplant
			setActiveButton("nuclearPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LNuclearPowerPlant)));
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;
		case SELECT_BUILDING_HYDROPOWERPLANT:
			updateInfofield("HydroPowerplant");
			m_selectedBuilding = VIdentifier::VHydroelectricPowerPlant;
			vUi->switchCursor(vUi->CursorType::Hammer);
			//TODO BuildMenue Button Hydropowerplant
			setActiveButton("hydroPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LHydroelectricPowerPlant)));
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;
		case SELECT_BUILDING_SOLARPOWERPLANT:
			updateInfofield("SolarPowerplant");
			m_selectedBuilding = VIdentifier::VSolarPowerPlant;

			//TODO BuildMenue Button Solarpowerplant
			vUi->switchCursor(vUi->CursorType::Hammer);
			setActiveButton("solarPowerPlant");
			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LSolarPowerPlant)));
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;
		case SELECT_BUILDING_POWERLINE:
			updateInfofield("Powerline");
			m_selectedBuilding = VIdentifier::VPowerLine;
			vUi->switchCursor(vUi->CursorType::Hammer);
			//TODO BuildMenue Button Powerline

			CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo"))->updateText(std::to_string(LBalanceLoader::getProducedEnergy(LIdentifier::LPowerLine)));

			setActiveButton("powerLine");
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOn();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOn();
			break;

		case SELECT_SABOTAGE_POWERLINECUT:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotagePowerlineCut");
			selectedAction = IViewBuilding::sabotagePowerLine;
			break;
		case SELECT_SABOTAGE_STRIKE:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotageStrike");
			selectedAction = IViewBuilding::sabotagePowerPlant;
			break;
		case SELECT_SABOTAGE_BOMB:
			vUi->switchCursor(vUi->CursorType::Sabotage);
			setActiveButton("sabotageBomb");
			selectedAction = IViewBuilding::sabotageResourceField;
			break;

		default:
			m_selectedBuilding = VIdentifier::Undefined;
			selectedAction = IViewBuilding::Undefined;
			notify(events);
			break;
	}

	updateModelView();
}


void VScreenIngame::switchOn()
{
	m_viewport->SwitchOn();
	m_viewportModels.SwitchOn();
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

	if (keyboard->KeyPressed(DIK_M) && enabled)
	{
		enabled = false;
		m_vtTabSabotage->getGuiObject("sabotageBomb")->switchOff();

		m_vtTabSabotage->addOverlay(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialAnimSabotageBomb, "AnimBomb");
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


			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("PowerInfo")->switchOff();
			getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("MoneyInfo")->switchOff();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("EngergyInfoIcon")->SwitchOff();
			getContainer("BottomBar")->getContainer("Infofield")->getOverlay("MoneyInfoIcon")->SwitchOff();

			if (m_selectedBuilding!=VIdentifier::Undefined)

			{
				m_selectedBuilding = VIdentifier::Undefined;
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

void VScreenIngame::updatePowerPlants(const std::map<VScreenIngame::BUILDINGTYPE, int> powerPlants) {
	for each (std::pair<VScreenIngame::BUILDINGTYPE, int> plant in powerPlants) {
		CASTD<VText*>(m_vtTabStatistics->getGuiObject(m_powerPlantsNameMapping[plant.first]))->updateText(std::to_string(plant.second));
	}
}

void VScreenIngame::updateGraph(float fProduced, float fNeeded)
{
	m_vgGraphEnergy->updateBar2("producedEnergy", fProduced);
	m_vgGraphEnergy->updateBar2("neededEnergy", fProduced);
}

void VScreenIngame::updateGraphRatio(float fRatio) {
	m_vgGraphEnergyRatio->updateValue(fRatio);
}

CFloatRect VScreenIngame::getTopSpace()
{
	return getContainer("Topbar")->getRectangle();
}

CFloatRect VScreenIngame::getBottomSpace()
{
	return getContainer("BottomBar")->getRectangle();
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
	const float mouseWheelPositionMin = -18.0f;
	const float mouseWheelPositionMax = 50.0f;

	if (vUi->m_zkKeyboard.KeyPressed(DIK_UP))
	{
		if (mouseWheelPosition > mouseWheelPositionMin)
		{
			m_zpCamera.TranslateZDelta(-cameraStength * 4.0f);
			mouseWheelPosition += -cameraStength * 4.0f;
		}
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_DOWN))
	{
		if (mouseWheelPosition < mouseWheelPositionMax)
		{
			m_zpCamera.TranslateZDelta(cameraStength * 4.0f);
			mouseWheelPosition += cameraStength * 4.0f;
		}
	}

	if (vUi->m_zkMouse.GetRelativeZ() != 0.0f)
	{
		if (vUi->m_zkMouse.GetRelativeZ() > 0.0f)
		{
			if (mouseWheelPosition > mouseWheelPositionMin)
			{
				m_zpCamera.TranslateZDelta(-cameraStength * 4.0f);
				mouseWheelPosition += -cameraStength * 4.0f;
			}
		}
		else
		{
			if (mouseWheelPosition < mouseWheelPositionMax)
			{
				m_zpCamera.TranslateZDelta(cameraStength * 4.0f);
				mouseWheelPosition += cameraStength * 4.0f;
			}
		}

		DEBUG_OUTPUT("Mousewheel Pos:::" << mouseWheelPosition);
	}


	if (vUi->m_zkKeyboard.KeyPressed(DIK_E))
	{
		if (cameraAngle < 0.5f)
		{
			m_zpCamera.RotateZDelta(cameraStength / 10.0f);
			cameraAngle += cameraStength / 10.0f;
			DEBUG_OUTPUT("Camera Angle:::" << cameraAngle);
		}
	}

	if (vUi->m_zkKeyboard.KeyPressed(DIK_Q))
	{
		if (cameraAngle > -0.5f)
		{
			m_zpCamera.RotateZDelta(-cameraStength / 10.0f);
			cameraAngle -= cameraStength / 10.0f;
			DEBUG_OUTPUT("Camera Angle:::" << cameraAngle);
		}
	}

	if (!vUi->m_zkKeyboard.KeyPressed(DIK_Q) && !vUi->m_zkKeyboard.KeyPressed(DIK_E))
	{
		if (cameraAngle < 0.0f)
		{
			m_zpCamera.RotateZDelta(cameraStength / 10.0f);
			cameraAngle += cameraStength / 10.f;
			DEBUG_OUTPUT("Camera Angle:::" << cameraAngle);
		}

		if (cameraAngle > 0.0f)
		{
			m_zpCamera.RotateZDelta(-cameraStength / 10.0f);
			cameraAngle -= cameraStength / 10.0f;
			DEBUG_OUTPUT("Camera Angle:::" << cameraAngle);
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
			m_selectedBuilding = VIdentifier::Undefined;
			updateModelView();

			clickActive = true;
		}
	}
	else if (vUi->m_zkKeyboard.KeyPressed(DIK_T))
	{
		handleTestClick(pickedElements);
	}
	else
	{
		clickActive = false;
	}
}

std::map<int, std::vector<int>> VScreenIngame::pickElements()
{
	std::map<int, std::vector<int>> pickedElements;

	CGeos geos;
	vUi->m_zkCursor.PickGeos(&geos, 5);

	for (int i = 0; i < geos.m_iGeos; i++)
	{
		std::vector<std::string> nameParts = split(geos.m_apgeo[i]->GetName(), ';');

		if (nameParts.size() == 3) //Currently all valid name parts consists of 3 elements
		{
			//Convert the arguments to integer (skip the first one, because its the key for the map
			std::vector<int> namePartsInt;
			for (size_t j = 1; j < nameParts.size(); j++)
			{
				namePartsInt.emplace_back(std::stoi(nameParts[j]));
			}

			pickedElements[std::stoi(nameParts[0])] = namePartsInt;
		}
	}

	return pickedElements;
}

void VScreenIngame::startAnimation()
{ }

void VScreenIngame::StartEvent()
{ }

void VScreenIngame::EndEvent()
{ }

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

			if (m_selectedBuilding != VIdentifier::Undefined)
			{
				if (!tryBuilding(x, y))
				{
					VSoundLoader::playSoundeffect(VSoundLoader::OPERATION_CANCELED, nullptr);
				}
			}

			if (selectedAction != IViewBuilding::Undefined)
			{
				if (trySabotage(x, y))
				{
					VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_EMITTED, nullptr);
				}
				else
				{
					VSoundLoader::playSoundeffect(VSoundLoader::OPERATION_CANCELED, nullptr);
				}
			}
		}

		clickActive = true;
	}
}

void VScreenIngame::handleTestClick(const std::map<int, std::vector<int>>& pickedElements)
{
	if (!clickActive)
	{
		if (pickedElements.count(VIdentifier::VPlayingField) > 0)
		{
			int x = pickedElements.at(VIdentifier::VPlayingField)[0];
			int y = pickedElements.at(VIdentifier::VPlayingField)[1];

			//Interaction with buildings				
			IViewBuilding* vbuilding = vUi->vMaster->getVPlayingField()->getBuilding(x, y);

			//check if ist your building or if its enemys buidling
			if (vbuilding != nullptr)
			{
				//Check if player is allowed to sabotage (check cooldown or count or wahtever)

				if (vbuilding->getLBuilding()->getPlayerId() == LPlayer::PlayerId::Remote)
				{
					/*if (vbuilding->getLBuilding()->getPlayerId() == LPlayer::PlayerId::Local)
				{*/
					auto sabotageSoundHelper = [] (const bool operationSuccessful)
							{
								if (operationSuccessful)
								{
									VSoundLoader::playSoundeffect(VSoundLoader::SABOTAGE_EMITTED, nullptr);
								}
								else
								{
									VSoundLoader::playSoundeffect(VSoundLoader::OPERATION_CANCELED, nullptr);
								}
							};

					//Switch enemys Powerplant Off
					if (dynamic_cast<IVPowerPlant*>(vbuilding) != nullptr)
					{
						// Deduct enemys resources
						if (vUi->m_zkKeyboard.KeyPressed(DIK_LCONTROL))
						{
							sabotageSoundHelper(vbuilding->clicked(IViewBuilding::sabotageResourceField));
						}
						else
						{
							sabotageSoundHelper(vbuilding->clicked(IViewBuilding::sabotagePowerPlant));
						}
					}
					//Destroy enemy Powerline
					else if (dynamic_cast<VPowerLine*>(vbuilding) != nullptr)
					{
						bool operationSuccessful = vbuilding->clicked(IViewBuilding::sabotagePowerLine);
						sabotageSoundHelper(operationSuccessful);

						if (operationSuccessful)
						{
							//only remove it if action was successfull
							vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
						}
					}
				}
				else
				{
					if (dynamic_cast<IVPowerPlant*>(vbuilding) != nullptr)
					{
						vbuilding->clicked(IViewBuilding::switchOnOff);
					}

					if (dynamic_cast<VPowerLine*>(vbuilding) != nullptr)
					{
						vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
					}
				}
			}
			//Place objects everywhere
			//#ifdef _DEBUG
			//				extern bool isCheatModeOn;
			//				isCheatModeOn = true;
			//				vUi->vMaster->getVPlayingField()->tryBuildOnField<LSolarPowerPlant>(x, y);
			//				isCheatModeOn = false;
			//#endif
		}

		clickActive = true;
	}
}

bool VScreenIngame::tryBuilding(const int x, const int y)
{
	switch (m_selectedBuilding)
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
		case IViewBuilding::sabotagePowerPlant:
			//No power plant selected
			if (dynamic_cast<IVPowerPlant*>(vbuilding) == nullptr)
			{
				return false;
			}

			return vbuilding->clicked(IViewBuilding::sabotagePowerPlant);

		case IViewBuilding::sabotagePowerLine:
			{
				//No powerline selected
				if (dynamic_cast<VPowerLine*>(vbuilding) == nullptr)
				{
					return false;
				}

				bool operationSuccessful = vbuilding->clicked(IViewBuilding::sabotagePowerLine);
				if (operationSuccessful)
				{
					//only remove it if action was successfull
					vUi->vMaster->getVPlayingField()->tryRemoveObject(x, y);
				}
				return operationSuccessful;
			}
		case IViewBuilding::sabotageResourceField:
			// Deduct enemys resources
			return vbuilding->clicked(IViewBuilding::sabotageResourceField);

		default:
			return false;
	}
}

void VScreenIngame::updateModelView()
{
	static IViewModel* previousModel = nullptr;

	if (previousModel != nullptr)
	{
		m_sceneModels.SubPlacement(previousModel->getMainPlacement());
	}

	if (models.count(m_selectedBuilding) > 0)
	{
		previousModel = models.at(m_selectedBuilding);
		m_sceneModels.AddPlacement(previousModel->getMainPlacement());
	}
	else
	{ //Disable action
		previousModel = nullptr;
	}
}

void VScreenIngame::addToScene(CPlacement* placement)
{
	m_scene.AddPlacement(placement);
}

NAMESPACE_VIEW_E
