#include "VScreenMainMenue.h"

NAMESPACE_VIEW_B

VScreenMainMenue::VScreenMainMenue(CFrame* frame)
{
	m_camera.Init();
	m_viewport.InitFull(&m_camera);
	frame->AddViewport(&m_viewport);

	addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.27, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::START_GAME);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.42, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::MainOptions);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.57, 0.33, 0.14), &VMaterialLoader::materialMainMenue, &VMaterialLoader::materialMainMenueHover, IViewObserver::QUIT_GAME);

}


VScreenMainMenue::~VScreenMainMenue()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();
}

void VScreenMainMenue::onNotify(IViewObserver::Event events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}
NAMESPACE_VIEW_E