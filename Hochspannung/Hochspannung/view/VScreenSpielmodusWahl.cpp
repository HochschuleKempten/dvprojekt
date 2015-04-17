#include "VScreenSpielmodusWahl.h"

NAMESPACE_VIEW_B

VScreenSpielmodusWahl::VScreenSpielmodusWahl(CFrame* frame)
{
	m_camera.Init();
	m_viewport.InitFull(&m_camera);
	frame->AddViewport(&m_viewport);

	m_flash = new COverlay();
	m_background = new CBackground();
	m_headline = new COverlay();

	m_background->InitFull("textures\\MainMenueBackground.png");
	m_flash->Init("textures\\Blitz.png", CFloatRect(0.75, 0.2, 0.20, 0.7));
	m_headline->Init("textures\\Hochvolt.png", CFloatRect(0.20, 0.05, 0.6, 0.15));

	m_viewport.AddOverlay(m_flash);
	m_viewport.AddBackground(m_background);
	m_viewport.AddOverlay(m_headline);


	addContainer(IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.27, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueEinzelspieler, &VMaterialLoader::materialButtonMainMenueEinzelspielerHover, IViewUIObserver::NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.42, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueMehrspieler, &VMaterialLoader::materialButtonMainMenueMehrspielerHover, IViewUIObserver::SWITCH_TO_LOBBY);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.57, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, IViewUIObserver::SWITCH_TO_MAINMENUE);



}


VScreenSpielmodusWahl::~VScreenSpielmodusWahl()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_flash;
	delete m_background;
	delete m_headline;
}

void VScreenSpielmodusWahl::onNotify(IViewUIObserver::Event events)
{
	switch (events)
	{

	default:
		notify(events);
		break;
	}
}

void VScreenSpielmodusWahl::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(IViewUIObserver::SWITCH_TO_MAINMENUE);
	}
}
NAMESPACE_VIEW_E