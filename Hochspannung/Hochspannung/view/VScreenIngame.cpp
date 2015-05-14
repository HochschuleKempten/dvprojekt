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
#include "VSoundLoader.h"
#include "VPowerLine.h"

NAMESPACE_VIEW_B


VScreenIngame::VScreenIngame(VUI* vUi)
	: IViewScreen(vUi)
{
	m_viewport = new CViewport();
	//Standard Init
	m_zc.Init();
	m_zb.InitFull("textures/black_image.jpg");

	m_viewport->AddBackground(&m_zb);
	m_viewport->InitFull(&m_zc);

	//Minimap
	m_CamMiniMap.Init();
	m_zpMinimapCam.AddCamera(&m_CamMiniMap);
	m_CamMiniMap.SetOrthoOn();
	m_CamMiniMap.SetFov(1.5F);
	m_zpMinimapCam.TranslateZ(10);
	m_zpMinimapCam.Scale(50);
	m_zpMinimapCam.RotateXDelta(0);
	m_minimap.Init(&m_CamMiniMap, CFloatRect(0.8F, 0.765F, 0.195F, 0.23F));

	m_zl.Init(CHVector(1.0F, 1.0F, 1.0F),
	          CColor(1.0F, 1.0F, 1.0F));

	m_scene.AddPlacement(&m_zpMinimapCam);
	m_scene.AddParallelLight(&m_zl);
	m_scene.AddPlacement(&m_zpCamera);

	vUi->m_zf.AddViewport(m_viewport);
	//vUi->m_zf.AddViewport(&m_minimap);
	vUi->m_zr.AddScene(&m_scene);

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


	/********************************************************TOP AREA***************************************************************/
	addContainer(m_viewport, IViewGUIContainer::GUIArea, CFloatRect(0.1F, 0.0F, 0.8F, 0.05F), &VMaterialLoader::materialTopbar, "Topbar");
	//getContainer("Topbar")->addText(CFloatRect(0.10F, 0.2F, 0.2F, 0.65F), &VMaterialLoader::standardFont, "Bevoelkerung:", "population");
	getContainer("Topbar")->addOverlay(CFloatRect(0.1F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconPopulation,"true", "TopPopulationIcon");
	getContainer("Topbar")->addText(CFloatRect(0.201F, 0.1F, 0.2F, 0.85F), &VMaterialLoader::standardFont, "0000", "popValue");
	//getContainer("Topbar")->addText(CFloatRect(0.50F, 0.2F, 0.2F, 0.65F), &VMaterialLoader::GoldFont, "Geld:", "money");
	getContainer("Topbar")->addOverlay(CFloatRect(0.50F, 0.2F, 0.1F, 0.5F), &VMaterialLoader::materialIngameIconMoney, "true", "TopMoneyIcon");
	getContainer("Topbar")->addText(CFloatRect(0.601F, 0.2F, 0.2F, 0.85F), &VMaterialLoader::GoldFont, "0000", "moneyValue");


	/********************************************************BOTTOM AREA*************************************************************/
	//addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.0F, 0.75F, 1.0F, 0.25F), "BottomBar");
	addContainer(m_viewport, IViewGUIContainer::ContainerType::GUIArea, getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 150, vUi->m_zf.m_iWidthWindow, 150), "BottomBar");


	

	/********************************************************Infofield AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.00F, 0.00F, 0.22F, 1.0F), &VMaterialLoader::materialInfofieldBackground, "Infofield");
	getContainer("BottomBar")->getContainer("Infofield")->addText(CFloatRect(0.01F, 0.3F, 0.80F, 0.1F), &VMaterialLoader::standardFont, "Infofeld", "infoText");
	getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText")->setLayer(0.2F);
	getContainer("BottomBar")->getContainer("Infofield")->setLayer(0.2F);

	/********************************************************Baumenu AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.22F, 0.00F, 0.51F, 1.0F), &VMaterialLoader::m_zmCraftMenueBackground, "Craftmenu");
	getContainer("BottomBar")->getContainer("Craftmenu")->addContainer(IViewGUIContainer::ContainerType::Register, CFloatRect(0.00F, 0.1F, 1.0F,0.90F), "Register");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonCraftmenu,
		&VMaterialLoader::materialIngameButtonCraftmenuHover, &VMaterialLoader::materialRed, SWITCH_TO_REGISTER_BUILDING, "TabBuilding");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonSabotage,
		&VMaterialLoader::materialIngameButtonSabotageHover, &VMaterialLoader::materialGreen, SWITCH_TO_REGISTER_SABOTAGE, "TabSabotage");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->addTab(&VMaterialLoader::materialIngameButtonStatistics,
		&VMaterialLoader::materialIngameButtonStatisticsHover, &VMaterialLoader::materialBlue, SWITCH_TO_REGISTER_STATISTICS, "TabStatistics");

	getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register")->setLayer(0.7);

	//CraftMenu
	CASTD <VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.025F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonWindmill, &VMaterialLoader::materialCraftmenuButtonWindmillHover, SELECT_BUILDING_WINDMILL, "windmill");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.275F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonHydroPowerplant, &VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover, SELECT_BUILDING_HYDROPOWERPLANT, "hydroPowerPlant");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.525F, 0.075F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonSolarPowerplant, &VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover, SELECT_BUILDING_SOLARPOWERPLANT, "solarPowerPlant");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.025F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonNuclearPowerplant, &VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover, SELECT_BUILDING_NUCLEARPOWERPLANT, "nuclearPowerPlant");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.275F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonCoalPowerplant, &VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover, SELECT_BUILDING_COALPOWERPLANT, "coalPowerPlant");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.525F, 0.525F, 0.2F, 0.4F), &VMaterialLoader::materialCraftmenuButtonOilPowerplant, &VMaterialLoader::materialCraftmenuButtonOilPowerplantHover, SELECT_BUILDING_OILPOWERPLANT, "oilPowerPlant");
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->addButton(CFloatRect(0.775F, 0.525F, 0.20F, 0.4F), &VMaterialLoader::materialCraftmenuButtonPowerline, &VMaterialLoader::materialCraftmenuButtonPowerlineHover, SELECT_BUILDING_POWERLINE, "powerLine");

	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("windmill")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("hydroPowerPlant")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("solarPowerPlant")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("coalPowerPlant")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("oilPowerPlant")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("nuclearPowerPlant")->setLayer(0.2F);
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->getGuiObject("powerLine")->setLayer(0.2F);
	
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
	CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOff();

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


	/********************************************************Energy AREA*************************************************************/
	getContainer("BottomBar")->addContainer(IViewGUIContainer::ContainerType::GUIArea, CFloatRect(0.74F, 0.03F, 0.05F, 1.0F), &VMaterialLoader::materialGreen, "Energy");
	getContainer("BottomBar")->getContainer("Energy")->addOverlay(CFloatRect(0.5F, 0.4F, 0.5F, 0.6F), &VMaterialLoader::materialRed, false, "NeededEnergy");
	getContainer("BottomBar")->getContainer("Energy")->setLayer(0.3F);

	switchCursor("textures/gui/default_zeiger.png", true);

	//CFloatRect iwas = getRectForPixel(0, vUi->m_zf.m_iHeightWindow - 100, vUi->m_zf.m_iWidthWindow, 100);

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
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->switchOn();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
			break;
		case SWITCH_TO_REGISTER_SABOTAGE:
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabSabotage")->switchOn();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOff();
			break;
		case SWITCH_TO_REGISTER_STATISTICS:
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabBuilding")->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabSabotage")->switchOff();
			CASTD<VRegister*>(getContainer("BottomBar")->getContainer("Craftmenu")->getContainer("Register"))->getTab("TabStatistics")->switchOn();
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
	m_viewport->SwitchOn();
	m_minimap.SwitchOn();
	m_scene.SwitchOn();
	m_isOn = true;
}

void VScreenIngame::switchOff()
{
	m_viewport->SwitchOff();
	m_minimap.SwitchOff();
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
	CASTD<VText*>(getContainer("BottomBar")->getContainer("Infofield")->getGuiObject("infoText"))->updateText(neuerText);
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
	updateCursorImagePos(&vUi->m_zkCursor);

	if (!vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = false;
	}

	handleInput();
	std::map<std::string, IViewGUIContainer*> tempGuicontainer;
	std::map<std::string, IViewGUIContainer*>::iterator tempIterGuicontainer;

	checkShortcut(&vUi->m_zkKeyboard);
	checkSpecialEvent(&vUi->m_zkCursor);
	tempGuicontainer = getGuiContainerMap();

	//For all containers in the screen
	for (tempIterGuicontainer = tempGuicontainer.begin(); tempIterGuicontainer != tempGuicontainer.end(); tempIterGuicontainer++)
	{
		checkGUIContainer(tempIterGuicontainer->second);
	}

	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		vUi->m_BlockCursorLeftPressed = true;
	}
}

void VScreenIngame::checkGUIObjects(IViewGUIContainer* tempGuicontainer)
{
	std::map<std::string, IViewGUIObject*>::iterator tempIterGUIObjects;
	std::map<std::string, IViewGUIObject*> tempGUIObjects = tempGuicontainer->getGuiObjectList();

	for (tempIterGUIObjects = tempGUIObjects.begin(); tempIterGUIObjects != tempGUIObjects.end(); tempIterGUIObjects++)
	{
		if (tempIterGUIObjects->second->isOn())
		{
			if (!vUi->m_BlockCursorLeftPressed)
			{
				//check for events
				tempIterGUIObjects->second->checkEvent(&vUi->m_zkCursor, &vUi->m_zkKeyboard);
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
	std::map<std::string, IViewGUIContainer*> tempGuiContainerMap;
	std::map<std::string, IViewGUIContainer*>::iterator ItertempGuiContainerMap;

	tempGuiContainerMap = tempGuicontainer->getGuiContainerMap();

	checkGUIObjects(tempGuicontainer);

	for (ItertempGuiContainerMap = tempGuiContainerMap.begin(); ItertempGuiContainerMap != tempGuiContainerMap.end(); ItertempGuiContainerMap++)
	{
		checkGUIObjects(ItertempGuiContainerMap->second);

		if (tempGuicontainer->getGuiContainerMap().size() > 0)
		{
			checkGUIContainer(ItertempGuiContainerMap->second);
		}
	}
}


void VScreenIngame::resize(int width, int height)
{
	m_viewport->ReSize();
}

void VScreenIngame::handleInput()
{
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
	float cursorX, cursorY;
	bool insideFrame = vUi->m_zkCursor.GetFractional(cursorX, cursorY, true);
	if (!insideFrame || cursorY < topSpace.GetYSize() || cursorY > (1.0f - bottomSpace.GetYSize()))
	{
		//Restrict picking when not in window or cursor is only over UI
		return;
	}

	std::map<int, std::vector<int>> pickedElements = pickElements();
	if (pickedElements.count(VIdentifier::VPlayingField) > 0)
	{
		vUi->vMaster->getPlayingField()->hoverField(pickedElements[VIdentifier::VPlayingField][0], pickedElements[VIdentifier::VPlayingField][1]);
	}

	static bool clickActive = false;
	if (vUi->m_zkCursor.ButtonPressedLeft())
	{
		if (!clickActive)
		{
			if (pickedElements.count(VIdentifier::VPlayingField) > 0)
			{
				int x = pickedElements[VIdentifier::VPlayingField][0];
				int y = pickedElements[VIdentifier::VPlayingField][1];

				switch (m_selectedBuilding)
				{
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
	else if (vUi->m_zkCursor.ButtonPressedRight())
	{
		if (!clickActive)
		{
			if (pickedElements.count(VIdentifier::VPlayingField) > 0)
			{
				int x = pickedElements[VIdentifier::VPlayingField][0];
				int y = pickedElements[VIdentifier::VPlayingField][1];



				//Interact with buildings
				
				IViewBuilding* vbuilding = dynamic_cast<IViewBuilding*>(vUi->vMaster->getPlayingField()->getBuilding(x, y));
				
				//check if ist your building or if its enemys buidling
				if (vbuilding != nullptr)
				{

				if (vbuilding->getLBuilding()->getPlayerId() != 1)
				{
					
						//Switch enemys Powerplant Off

						if (dynamic_cast<IVPowerPlant*>(vbuilding) != nullptr)
						{
							vbuilding->clicked(IViewObject::action::switchOnOff);
						}

						if (dynamic_cast<VPowerLine*>(vbuilding) != nullptr)
						{
							vUi->vMaster->getPlayingField()->tryRemoveObject(x, y);
						}							
						
					}
				

					else
					{
						if (dynamic_cast<IVPowerPlant*>(vbuilding) != nullptr)
						{
							vbuilding->clicked(IViewObject::action::switchOnOff);
						}

						if (dynamic_cast<VPowerLine*>(vbuilding) != nullptr)
						{
							vUi->vMaster->getPlayingField()->tryRemoveObject(x, y);
						}
					}
				}
				//Place objects everywhere
//#ifdef _DEBUG
//				extern bool isCheatModeOn;
//				isCheatModeOn = true;
//				vUi->vMaster->getPlayingField()->tryBuildOnField<LSolarPowerPlant>(x, y);
//				isCheatModeOn = false;
//#endif
			}

			clickActive = true;
		}
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
	vUi->m_zkCursor.PickGeos(&geos);

	for (int i = 0; i < geos.m_iGeos; i++)
	{
		std::vector<std::string> nameParts = split(geos.m_apgeo[i]->GetName(), ';');

		if (nameParts.size() == 3)	//Currently all valid name parts consists of 3 elements
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

CFloatRect VScreenIngame::getRectForPixel(int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	CFloatRect tempRectangle;
	int iFensterBreite = vUi->m_zf.m_iWidthWindow;
	int iFensterHöhe = vUi->m_zf.m_iHeightWindow;

	ASSERT((((iPosX + iSizeX) <= iFensterBreite) && ((iPosY + iSizeY) <= iFensterHöhe)), "Angegebener Bereich liegt außerhalb des Fensters");

	/* iFensterBreite/100% = iPosX/X% => iFensterbreite=(iPosX*100%)/x =>x=(iPosX*100%)/iFensterBreite */

	tempRectangle.SetXPos(iPosX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYPos(iPosY / CASTS<float>(iFensterHöhe));
	tempRectangle.SetXSize(iSizeX / CASTS<float>(iFensterBreite));
	tempRectangle.SetYSize(iSizeY / CASTS<float>(iFensterHöhe));

	return tempRectangle;
}

void VScreenIngame::addToScene(CPlacement* placement)
{
	m_scene.AddPlacement(placement);
}

NAMESPACE_VIEW_E
