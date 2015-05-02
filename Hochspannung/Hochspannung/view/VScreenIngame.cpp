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
#include "../logic/LMaster.h"
#include <Vektoria/Placements.h>

NAMESPACE_VIEW_B


VScreenIngame::VScreenIngame(VUI* vUi)
	: IViewScreen(vUi)
{
	//Standard Init
	m_zc.Init();
	m_zb.InitFull("textures/black_image.jpg");

	m_viewport.AddBackground(&m_zb);
	m_viewport.InitFull(&m_zc);

	//Minimap
	m_CamMiniMap.Init();
	m_zpMinimapCam.AddCamera(&m_CamMiniMap);
	m_CamMiniMap.SetOrthoOn();
	m_CamMiniMap.SetFov(1.5);
	m_zpMinimapCam.TranslateZ(10);
	m_zpMinimapCam.Scale(50);
	m_zpMinimapCam.RotateXDelta(0);
	m_minimap.Init(&m_CamMiniMap, CFloatRect(0.8, 0.765, 0.195, 0.23));

	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
			  CColor(1.0f, 1.0f, 1.0f));

	m_scene.AddPlacement(&m_zpMinimapCam);
	m_scene.AddParallelLight(&m_zl);
	m_scene.AddPlacement(&m_zpCamera);

	vUi->m_zf.AddViewport(&m_viewport);
	//vUi->m_zf.AddViewport(&m_minimap);
	vUi->m_zr.AddScene(&m_scene);

	DEBUG_EXPRESSION(m_zpCamera.SetName("#Placement Camera"));
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.TranslateZ(50.0);
	m_zpCamera.RotateXDelta(0.15 * PI);
	m_zpCamera.RotateZDelta(0.15);

	//Bottom Bar

	/*m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport.AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);*/


	/********************************************************TOP AREA***************************************************************/
	addContainer(&m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.2, 0.0, 0.6, 0.05), &VMaterialLoader::materialTopbar, "Topbar");
	getContainer("Topbar")->addText(CFloatRect(0.05, 0.2, 0.2, 0.7), &VMaterialLoader::standardFont, "Bevoelkerung:", "population");
	getContainer("Topbar")->addText(CFloatRect(0.251, 0.2, 0.2, 0.65), &VMaterialLoader::standardFont, "0000", "popValue");
	getContainer("Topbar")->addText(CFloatRect(0.55, 0.2, 0.2, 0.65), &VMaterialLoader::GoldFont, "Geld:", "money");
	getContainer("Topbar")->addText(CFloatRect(0.751, 0.2, 0.2, 0.65), &VMaterialLoader::GoldFont, "0000", "moneyValue");


	/********************************************************BOTTOM AREA*************************************************************/
	addContainer(&m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0, 0.75F, 1.0F, 0.25F), "BottomBar");

	getContainer("BottomBar")->addOverlay(CFloatRect(0.0, 0.0, 1, 0.05), &VMaterialLoader::materialBottombarBorderTop, false, "BottomTopBorder");
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
	addContainer(&m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.10, 0.30, 0.55), &VMaterialLoader::materialDialogBackground, "DialogBox");


	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.10, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING, "MenueButtonContinue");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.27, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "MenueButtonQuit");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.44, 0.80, 0.15), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "MenueButtonBack");


	/********************************************************Energy AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.74, 0.03F, 0.05F, 1.0F), &VMaterialLoader::materialGreen, "Energy");
	getContainer("BottomBar")->getContainer("Energy")->addOverlay(CFloatRect(0.5, 0.4, 0.5, 0.6), &VMaterialLoader::materialRed, false, "NeededEnergy");
	getContainer("BottomBar")->getContainer("Energy")->setLayer(0.3);


	m_viewport.SwitchOff();
	getContainer("DialogBox")->switchOff();
}

VScreenIngame::~VScreenIngame()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer) {
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();
}

void VScreenIngame::onNotify(Event events)
{
	switch (events) {
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

		case SELECT_BUILDING_WINDMILL:
			updateInfofield("Windmill");
			m_selectedBuilding = VIdentifier::VWindmillPowerPlant;
			//TODO BuildMenue Button Windmill 
			break;
		case SELECT_BUILDING_COALPOWERPLANT:
			updateInfofield("CoalPowerplant");
			m_selectedBuilding = VIdentifier::VCoalPowerPlant;
			//TODO BuildMenue Button CoalPowerplant 
			break;
		case SELECT_BUILDING_OILPOWERPLANT:
			updateInfofield("OilPowerplant");
			m_selectedBuilding = VIdentifier::VOilRefinery;
			//TODO BuildMenue Button Oilpowerplant
			break;
		case SELECT_BUILDING_NUCLEARPOWERPLANT:
			updateInfofield("NuclearPowerplant");
			m_selectedBuilding = VIdentifier::VNuclearPowerPlant;
			//TODO BuildMenue Button Nuclearpowerplant
			break;
		case SELECT_BUILDING_HYDROPOWERPLANT:
			updateInfofield("HydroPowerplant");
			m_selectedBuilding = VIdentifier::VHydroelectricPowerPlant;
			//TODO BuildMenue Button Hydropowerplant
			break;
		case SELECT_BUILDING_SOLARPOWERPLANT:
			updateInfofield("SolarPowerplant");
			m_selectedBuilding = VIdentifier::VSolarPowerPlant;
			//TODO BuildMenue Button Solarpowerplant
			break;
		case SELECT_BUILDING_POWERLINE:
			updateInfofield("Powerline");
			m_selectedBuilding = VIdentifier::VPowerLine;
			//TODO BuildMenue Button Powerline
			break;
		default:
			m_selectedBuilding = VIdentifier::Undefined;
			notify(events);
			break;
	}
}


void VScreenIngame::switchOn()
{
	m_viewport.SwitchOn();
	m_minimap.SwitchOn();
	m_scene.SwitchOn();
	m_isOn = true;
}

void VScreenIngame::switchOff()
{
	m_viewport.SwitchOff();
	m_minimap.SwitchOff();
	m_scene.SwitchOff();
	m_isOn = false;
}

void VScreenIngame::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (!keyboard->KeyPressed(DIK_ESCAPE)) {
		bK = false;
	}
	if (keyboard->KeyPressed(DIK_ESCAPE) && bK == false) {
		if (!getContainer("DialogBox")->isOn()) {
			getContainer("DialogBox")->switchOn();
		}
		else {
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
			
			updateInfofield(hover);
		}
		else
			updateInfofield(standard);*/
}

void VScreenIngame::updateMoney(const int wert)
{
	dynamic_cast<VText*>(getContainer("Topbar")->getGuiObject("moneyValue"))->updateText(std::to_string(wert));
}

void VScreenIngame::updatePopulation(const int wert)
{
	dynamic_cast<VText*>(getContainer("Topbar")->getGuiObject("popValue"))->updateText(std::to_string(wert));
}

void VScreenIngame::updateInfofield(const string& neuerText)
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

void VScreenIngame::tick()
{
	handleInput();
}

void VScreenIngame::resize(int width, int height)
{
	m_viewport.ReSize();
}

void VScreenIngame::handleInput()
{
	const float cameraStength = 0.9f;

	//Left + Right: 
	if (vUi->m_zkKeyboard.KeyPressed(DIK_A)) {
		m_zpCamera.TranslateXDelta(-cameraStength);
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_D)) {
		m_zpCamera.TranslateXDelta(cameraStength);
	}

	//Back + Forward
	if (vUi->m_zkKeyboard.KeyPressed(DIK_S)) {
		m_zpCamera.TranslateYDelta(-cameraStength);
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_W)) {
		m_zpCamera.TranslateYDelta(cameraStength);
	}

	//Zoom In + Out
	if (vUi->m_zkKeyboard.KeyPressed(DIK_UP)) {
		if (mouseWheelPosition > -18) {
			m_zpCamera.TranslateZDelta(-cameraStength * 4);
			mouseWheelPosition += -cameraStength * 4;
		}
	}
	if (vUi->m_zkKeyboard.KeyPressed(DIK_DOWN)) {
		if (mouseWheelPosition < 180) {
			m_zpCamera.TranslateZDelta(cameraStength * 4);
			mouseWheelPosition += cameraStength * 4;
		}
	}

	if (vUi->m_zkMouse.GetRelativeZ() != 0.0) {
		if (vUi->m_zkMouse.GetRelativeZ() > 0.0) {
			if (mouseWheelPosition > -18) {
				m_zpCamera.TranslateZDelta(-cameraStength * 4);
				mouseWheelPosition += -cameraStength * 4;
			}
		}
		else {
			if (mouseWheelPosition < 180) {
				m_zpCamera.TranslateZDelta(cameraStength * 4);
				mouseWheelPosition += cameraStength * 4;
			}
		}

		DEBUG_OUTPUT("Mousewheel Pos:::" << mouseWheelPosition);
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
	float cursorX, cursorY;
	bool insideFrame = vUi->m_zkCursor.GetFractional(cursorX, cursorY);
	if (!insideFrame || cursorY < topSpace.GetYSize() || cursorY > (1.0f - bottomSpace.GetYSize())) {
		//Restrict picking when not in window or cursor is only over UI
		return;
	}

	std::map<int, std::vector<int>> pickedElements = pickElements();
	if (pickedElements.count(VIdentifier::VPlayingField) > 0) {
		vUi->vMaster->getPlayingField()->hoverField(pickedElements[VIdentifier::VPlayingField][0], pickedElements[VIdentifier::VPlayingField][1]);
	}

	static bool clickActive = false;
	if (vUi->m_zkCursor.ButtonPressedLeft()) {
		if (!clickActive) {
			if (pickedElements.count(VIdentifier::VPlayingField) > 0) {
				int x = pickedElements[VIdentifier::VPlayingField][0];
				int y = pickedElements[VIdentifier::VPlayingField][1];

				switch (m_selectedBuilding) {
					case VIdentifier::VPowerLine:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LPowerLine>(x, y);
						break;
					case VIdentifier::VWindmillPowerPlant:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LWindmillPowerPlant>(x, y);
						break;
					case VIdentifier::VCoalPowerPlant:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LCoalPowerPlant>(x, y);
						break;
					case VIdentifier::VHydroelectricPowerPlant:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LHydroelectricPowerPlant>(x, y);
						break;
					case VIdentifier::VNuclearPowerPlant:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LNuclearPowerPlant>(x, y);
						break;
					case VIdentifier::VOilRefinery:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LOilRefinery>(x, y);
						break;
					case VIdentifier::VSolarPowerPlant:
						vUi->vMaster->getPlayingField()->tryBuildOnField<LSolarPowerPlant>(x, y);
						break;
					default:
						break;
				}
			}

			clickActive = true;
		}
	}
	else if (vUi->m_zkCursor.ButtonPressedRight()) {
		if (!clickActive) {

			clickActive = true;
		}
	}
	else {
		clickActive = false;
	}
}

std::map<int, std::vector<int>> VScreenIngame::pickElements()
{
	std::map<int, std::vector<int>> pickedElements;
	std::unordered_set<CPlacement*> pickedPlacements; //A set is duplicate free and works out of the box for pointer types

	//Pick everything
	CPlacement* singlePlacement = vUi->m_zkCursor.PickPlacement();
	CPlacements placements;
	vUi->m_zkCursor.PickPlacements(&placements);

	//TODO (JS) merge seems obsolete now. Remove this
	//Merge the found placements together in a set (to avoid duplicates)
	for (int i = 0; i < placements.m_iPlacements; i++) {
		if (placements.m_applacement[i]->m_pgeos) {
			//pickedPlacements.insert(placements.m_applacement[i]);
		}
	}
	//The two placements pick different things, so they have to be merged together
	if (singlePlacement != nullptr) {
		size_t sizeBefore = pickedPlacements.size();
		pickedPlacements.insert(singlePlacement);
		//ASSERT(sizeBefore == pickedPlacements.size(), "PickPlacements() picked something different then PickPlacement(). This should not happen");
	}

	//DEBUG_OUTPUT("Picking started");
	//Now iterate over every found placement
	for (CPlacement* p : pickedPlacements) {
		std::vector<std::string> nameParts = split(p->GetName(), ';');
		//DEBUG_OUTPUT("placement = " << p->GetName());

		if (nameParts.size() > 0 && nameParts[0].at(0) != '#') {
			//At this point only valid names remain
			ASSERT(nameParts.size() == 3, "Not enough arguments in the placement name");

			//Convert the arguments to integer (skip the first one, because its the key for the map
			std::vector<int> namePartsInt;
			for (size_t j = 1; j < nameParts.size(); j++) {
				namePartsInt.emplace_back(std::stoi(nameParts[j]));
			}

			pickedElements[std::stoi(nameParts[0])] = namePartsInt;
		}
	}

	return pickedElements;
}

void VScreenIngame::addToScene(CPlacement* placement)
{
	m_scene.AddPlacement(placement);
}

NAMESPACE_VIEW_E
