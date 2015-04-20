#include "VScreenIngame.h"
#include "VMaster.h"
#include "VText.h"
NAMESPACE_VIEW_B

VScreenIngame::VScreenIngame()
{
}
VScreenIngame::VScreenIngame(CFrame* frame, CRoot* root, CScene* scene, CPlacement* camplacement)
{
	//Standard Init
	m_scene = scene;
	m_zpCamera = camplacement;
	m_zc.Init();
	m_viewport.InitFull(&m_zc);
	
	//Minimap
	m_CamMiniMap.Init();
	
	m_scene->AddPlacement(&m_zpMinimapCam);
	m_zpMinimapCam.AddCamera(&m_CamMiniMap);
	
	m_CamMiniMap.SetOrthoOn();
	//m_CamMiniMap.SetFov(1.5);
	//m_zpMinimapCam.TranslateZ(10);
	m_zpMinimapCam.Scale(50);
	m_zpMinimapCam.RotateXDelta(0);
	m_minimap.Init(&m_CamMiniMap, CFloatRect(0.8, 0.76, 0.195, 0.235));
	
	frame->AddViewport(&m_viewport);
	frame->AddViewport(&m_minimap);
	
	//Scene "3D-World"
	root->AddScene(scene);
	m_zb.InitFull("textures/black_image.jpg");
	m_viewport.AddBackground(&m_zb);
	
	m_scene->AddPlacement(m_zpCamera);
	m_zpCamera->AddCamera(&m_zc);

	m_zpCamera->TranslateZ(50.0);
	m_zpCamera->RotateXDelta(0.3 * PI);

	m_scene->AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
		CColor(1.0f, 1.0f, 1.0f));

	
	
	

	//Bottom Bar

	m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport.AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);

	addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.23, 0.82, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.23, 0.91, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.82, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.91, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueEinzelspieler, &VMaterialLoader::materialButtonMainMenueEinzelspielerHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.43, 0.82, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueMehrspieler, &VMaterialLoader::materialButtonMainMenueMehrspielerHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.43, 0.91, 0.05, 0.07), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.54, 0.85, 0.10, 0.10), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, NOTHING);

	
	//Boarder BottomBar
	m_bottomBarBorderTop.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.0, 0.75, 1.0, 0.01));
	m_bottomBarBorderBottom.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.0, 0.99, 1.0, 0.01));
	m_bottomBarBorderLeft.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.0, 0.75, 0.01, 0.25));
	m_bottomBarBorderRight.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.99, 0.75, 0.01, 0.25));
	m_bottomBarSeperatorMenueInfofeld.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.20, 0.75, 0.01, 0.25));
	m_bottomBarSeperatorMenueMinimap.Init(&VMaterialLoader::materialIngameBorder, CFloatRect(0.79, 0.75, 0.01, 0.25));

	m_bottomBarBorderTop.SetLayer(0.7);
	m_bottomBarBorderBottom.SetLayer(0.7);
	m_bottomBarBorderLeft.SetLayer(0.7);
	m_bottomBarBorderRight.SetLayer(0.7);
	m_bottomBarSeperatorMenueInfofeld.SetLayer(0.7);
	m_bottomBarSeperatorMenueMinimap.SetLayer(0.7);


	m_viewport.AddOverlay(&m_bottomBarBorderTop);
	m_viewport.AddOverlay(&m_bottomBarBorderBottom);
	m_viewport.AddOverlay(&m_bottomBarBorderLeft);
	m_viewport.AddOverlay(&m_bottomBarBorderRight);
	m_viewport.AddOverlay(&m_bottomBarSeperatorMenueInfofeld);
	m_viewport.AddOverlay(&m_bottomBarSeperatorMenueMinimap);
	
	//Top Bar
	m_topBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.2, 0.0, 0.6, 0.05));
	m_viewport.AddOverlay(&m_topBar);
	
	m_topBar.SetLayer(0.7);

	addContainer(IViewGUIContainer::Group, CFloatRect(0.2, 0.0, 0.6, 0.05), "top");
	getContainer("top")->addText(CFloatRect(0.25, 0.01, 0.10, 0.05), &VMaterialLoader::standardFont, "Bevoelkerung:");
	getContainer("top")->addText(CFloatRect(0.351, 0.01, 0.10, 0.05), &VMaterialLoader::standardFont, "popNumber");

	addContainer(IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.10, 0.30, 0.55), "DialogBox");
	
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.10, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING);
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.27, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME);
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.44, 0.80, 0.15), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE);
	
	m_viewport.SwitchOff();
getContainer("DialogBox")->switchOff();

}
VScreenIngame::VScreenIngame(CViewport* viewp, CFrame* frame)
{
	frame->AddViewport(&m_viewport);
}
VScreenIngame::~VScreenIngame()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();
}

void VScreenIngame::onNotify(IViewUIObserver::Event events)
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
	m_viewport.SwitchOn();
	m_minimap.SwitchOn();
	m_scene->SwitchOn();
	
	m_isOn = true;
}
void VScreenIngame::switchOff()
{
	m_viewport.SwitchOff();
	m_minimap.SwitchOff();
	m_scene->SwitchOff();
	m_isOn = false;
}

void VScreenIngame::checkShortcut(CDeviceKeyboard* keyboard)
{
	//Test
	
	static int zahl = 0;
	
	dynamic_cast<VText*>(getContainer("top")->getGuiObjectList()[1])->updateText(static_cast<ostringstream*>(&(ostringstream() << zahl++))->str());

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

	void VScreenIngame::updateMoney(const int& wert)
	{
	}

	void VScreenIngame::updatePopulation(const int& wert)
	{
	}

	NAMESPACE_VIEW_E