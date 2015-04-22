#include "VScreenCredits.h"

NAMESPACE_VIEW_B
VScreenCredits::VScreenCredits()
{
}

	VScreenCredits::VScreenCredits(CFrame* frame)
	{
		m_viewport = new CViewport();
		m_camera.Init();
		m_viewport->InitFull(&m_camera);
		frame->AddViewport(m_viewport);

		
		m_background = new CBackground();
		
		m_background->InitFull("textures\\MainMenueBackground.png");

		m_viewport->AddBackground(m_background);

		addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
		getContainer("Menue")->addButton(CFloatRect(0.65, 0.83, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover,SWITCH_TO_MAINMENUE,"BackMainMenue");


		addContainer(m_viewport, IViewGUIContainer::ContainerType::Dialog, CFloatRect(0, 0.7F, 1.0F, 0.3F), "iwas");
		getContainer("iwas")->addContainer(IViewGUIContainer::ContainerType::Dialog, CFloatRect(0, 0.7F, 1.0F, 0.3F), "neues");
		getContainer("iwas")->getContainer("neues")->addButton(CFloatRect(0.25, 0.63, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE, "BackMainMenue");;
	}

	VScreenCredits::~VScreenCredits()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;
}

	void VScreenCredits::onNotify(Event events)
{
	switch (events)
	{

	default:
		notify(events);
		break;
	}
	
}
	void VScreenCredits::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(SWITCH_TO_MAINMENUE);
	}
	
}
NAMESPACE_VIEW_E