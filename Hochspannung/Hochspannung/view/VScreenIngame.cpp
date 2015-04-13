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

	m_scene->AddPlacement(m_zpCamera);
	m_zpCamera->AddCamera(&m_zc);

	m_zpCamera->TranslateZ(50.0);
	m_zpCamera->RotateXDelta(0.3 * PI);

	m_scene->AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
		CColor(1.0f, 1.0f, 1.0f));
	addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.0, 0.75, 1, 0.25), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::NOTHING);
	
	addContainer(IViewGUIContainer::ContainerType::Dialog, CFloatRect(0.33, 0.22, 0.33, 0.66), "DialogBox");
	getContainer("DialogBox")->addButton(CFloatRect(0.33, 0.27, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::START_GAME);
	getContainer("DialogBox")->addButton(CFloatRect(0.33, 0.42, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::MainOptions);
	getContainer("DialogBox")->addButton(CFloatRect(0.33, 0.57, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::QUIT_GAME);

	
	m_viewport.SwitchOff();

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
NAMESPACE_VIEW_E