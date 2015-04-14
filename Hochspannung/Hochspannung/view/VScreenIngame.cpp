#include "VScreenIngame.h"
#include "VMaster.h"
NAMESPACE_VIEW_B

VScreenIngame::VScreenIngame()
{
}
VScreenIngame::VScreenIngame(CFrame* frame, CRoot* root, CScene* scene, CPlacement* camplacement)
{
	m_scene = scene;
	m_zpCamera = camplacement;
	m_zc.Init();
	m_viewport.InitFull(&m_zc);
	frame->AddViewport(&m_viewport);
	root->AddScene(scene);
	m_scene->SwitchOff();
	m_zb.InitFull("textures/black_image.jpg");
	m_viewport.AddBackground(&m_zb);
	
	m_bottomBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.0, 0.75, 1.0, 0.25));
	m_viewport.AddOverlay(&m_bottomBar);
	m_bottomBar.SetLayer(0.8);

	m_topBar.Init("textures\\MainMenueBackground.png", CFloatRect(0.2, 0.0, 0.6, 0.05));
	m_viewport.AddOverlay(&m_topBar);
	
	m_topBar.SetLayer(0.8);

	m_scene->AddPlacement(m_zpCamera);
	m_zpCamera->AddCamera(&m_zc);

	m_zpCamera->TranslateZ(50.0);
	m_zpCamera->RotateXDelta(0.3 * PI);

	m_scene->AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
		CColor(1.0f, 1.0f, 1.0f));
	
	addContainer(IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.10, 0.30, 0.55), "DialogBox");
	
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.10, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, IViewUIObserver::NOTHING);
	getContainer("DialogBox")->addButton(CFloatRect(0.10, 0.27, 0.80, 0.15), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, IViewUIObserver::QUIT_GAME);
	
	
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
	m_scene->SwitchOn();
	m_isOn = true;
}
void VScreenIngame::switchOff()
{
	m_viewport.SwitchOff();
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
NAMESPACE_VIEW_E