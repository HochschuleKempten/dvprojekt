#include "VScreenMainMenue.h"

NAMESPACE_VIEW_B

VScreenMainMenue::VScreenMainMenue(CFrame* frame)
{
	m_camera.Init();
	m_viewport.InitFull(&m_camera);
	frame->AddViewport(&m_viewport);

	addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.27, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::START_GAME);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.42, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::MainOptions);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.57, 0.30, 0.12), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewUIObserver::QUIT_GAME);

	
}


VScreenMainMenue::~VScreenMainMenue()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();
}

void VScreenMainMenue::onNotify(IViewUIObserver::Event events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}
NAMESPACE_VIEW_E