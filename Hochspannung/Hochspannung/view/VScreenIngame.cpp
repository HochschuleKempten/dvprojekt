#include "VScreenIngame.h"
#include "VMaster.h"
#include "VText.h"
#include <time.h>
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
	//m_CamMiniMap.SetFov(1.5);
	//m_zpMinimapCam.TranslateZ(10);
	m_zpMinimapCam.Scale(50);
	m_zpMinimapCam.RotateXDelta(0);
	m_minimap.Init(&m_CamMiniMap, CFloatRect(0.7999, 0.7645, 0.195, 0.235));
	
	frame->AddViewport(m_viewport);
	frame->AddViewport(&m_minimap);
	
	//Scene "3D-World"
	root->AddScene(scene);
	m_zb.InitFull("textures/black_image.jpg");
	m_viewport->AddBackground(&m_zb);
	
	m_scene->AddPlacement(m_zpCamera);
	m_zpCamera->AddCamera(&m_zc);

	m_zpCamera->TranslateZ(50.0);
	m_zpCamera->RotateXDelta(0.3 * PI);

	m_scene->AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
		CColor(1.0f, 1.0f, 1.0f));

	
	
	

	//Bottom Bar

	m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport->AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.23, 0.82, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING,"windmill");
	getContainer("Menue")->addButton(CFloatRect(0.23, 0.82 + 0.022 + 0.07, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING,"coalPowerPlant");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.82, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING, "oilPowerPlant");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.82 + 0.022 + 0.07, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING, "nuclearPowerPlant");
	getContainer("Menue")->addButton(CFloatRect(0.43, 0.82, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING,"hydroPowerPlant");
	getContainer("Menue")->addButton(CFloatRect(0.43, 0.82 + 0.022 + 0.07, 0.04, 0.04 * 1.7), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING, "photovoltaicPowerPlant");
	getContainer("Menue")->addButton(CFloatRect(0.54, 0.85, 0.10, 0.10), &VMaterialLoader::materialBuildingButton, &VMaterialLoader::materialBuildingButtonHover, NOTHING,"powerLine");

	
	//Boarder BottomBar
	m_bottomBarBorderTop.Init(&VMaterialLoader::materialBottombarBorderTop, CFloatRect(0.0, 0.75, 1.0, 0.01));
	m_bottomBarBorderBottom.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.0, 0.0, 1.0, -0.01));
	m_bottomBarBorderLeft.Init(&VMaterialLoader::materialVerticalBorder, CFloatRect(0.0, 0.7495, 0.006, 0.25));
	m_bottomBarBorderRight.Init(&VMaterialLoader::materialVerticalBorder, CFloatRect(0.99, 0.7495, 0.006, 0.25));
	m_bottomBarSeperatorMenueInfofeld.Init(&VMaterialLoader::materialVerticalBorder, CFloatRect(0.20, 0.7495, 0.006, 0.25));
	m_bottomBarSeperatorMenueMinimap.Init(&VMaterialLoader::materialVerticalBorder, CFloatRect(0.79, 0.7495, 0.006, 0.25));

	m_bottomBarBorderTop.SetLayer(0.7);
	m_bottomBarBorderBottom.SetLayer(0.7);
	m_bottomBarBorderLeft.SetLayer(0.7);
	m_bottomBarBorderRight.SetLayer(0.7);
	m_bottomBarSeperatorMenueInfofeld.SetLayer(0.7);
	m_bottomBarSeperatorMenueMinimap.SetLayer(0.7);


	m_viewport->AddOverlay(&m_bottomBarBorderTop);
	m_viewport->AddOverlay(&m_bottomBarBorderBottom);
	m_viewport->AddOverlay(&m_bottomBarBorderLeft);
	m_viewport->AddOverlay(&m_bottomBarBorderRight);
	m_viewport->AddOverlay(&m_bottomBarSeperatorMenueInfofeld);
	m_viewport->AddOverlay(&m_bottomBarSeperatorMenueMinimap);
	
	//Top Bar
	m_topBar.Init(&VMaterialLoader::materialTopbar, CFloatRect(0.2, 0.0, 0.6, 0.05));
	m_viewport->AddOverlay(&m_topBar);
	
	m_topBar.SetLayer(0.7);

	addContainer(m_viewport, IViewGUIContainer::Group, CFloatRect(0.2, 0.0, 0.6, 0.05), "top");
	getContainer("top")->addText(CFloatRect(0.25, 0.005, 0.1, 0.05), &VMaterialLoader::standardFont, "Bevoelkerung:","population");
	getContainer("top")->addText(CFloatRect(0.351, 0.005, 0.1, 0.05), &VMaterialLoader::standardFont, "0000","popValue");
	getContainer("top")->addText(CFloatRect(0.60, 0.005, 0.07, 0.05), &VMaterialLoader::GoldFont, "Geld:","money");
	getContainer("top")->addText(CFloatRect(0.671, 0.005, 0.1, 0.05), &VMaterialLoader::GoldFont, "0000","moneyValue");

	
	
	addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.10, 0.30, 0.55), "DialogBox");
	
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.10, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING,"MenueButtonContinue");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.27, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME,"MenueButtonQuit");
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.44, 0.80, 0.15), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "MenueButtonBack");
	
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
	//Test
	/*time_t t;

	time(&t);
	srand(static_cast<unsigned int>(t)*50);
	static int zahl = 0;
	static int imoney = 0;
	
	dynamic_cast<VText*>(getContainer("top")->getGuiObjectList()[1])->updateText(static_cast<ostringstream*>(&(ostringstream() << zahl++))->str());
	dynamic_cast<VText*>(getContainer("top")->getGuiObjectList()[3])->updateText(static_cast<ostringstream*>(&(ostringstream() << imoney+rand()))->str());
*/
	//keyboard->GetChar(keyboard->GetKey());
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

//TODO
	void VScreenIngame::updateMoney(const int wert)
	{
		dynamic_cast<VText*>(getContainer("top")->getGuiObject("moneyValue"))->updateText(std::to_string(wert));
	}

	void VScreenIngame::updatePopulation(const int wert)
	{
		dynamic_cast<VText*>(getContainer("top")->getGuiObject("popValue"))->updateText(std::to_string(wert));
	}

	NAMESPACE_VIEW_E