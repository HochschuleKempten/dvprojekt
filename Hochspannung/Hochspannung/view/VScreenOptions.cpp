#include "VScreenOptions.h"

NAMESPACE_VIEW_B
VScreenOptions::VScreenOptions()
{
}

VScreenOptions::VScreenOptions(CFrame* frame)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	frame->AddViewport(m_viewport);


	m_background = new CBackground();

	m_background->InitFull("textures\\MainMenueBackground.png");

	m_viewport->AddBackground(m_background);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.83, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, IViewUIObserver::SWITCH_TO_MAINMENUE);

}

VScreenOptions::~VScreenOptions()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;
}

	void VScreenOptions::onNotify(IViewUIObserver::Event events)
	{
		switch (events)
		{

		default:
			notify(events);
			break;
		}
	}

	void VScreenOptions::checkShortcut(CDeviceKeyboard* keyboard)
	{
		if (keyboard->KeyPressed(DIK_ESCAPE))
		{
			notify(IViewUIObserver::SWITCH_TO_MAINMENUE);
		}
	}

	NAMESPACE_VIEW_E