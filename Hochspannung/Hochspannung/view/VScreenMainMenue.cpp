#include "VScreenMainMenue.h"

NAMESPACE_VIEW_B

VScreenMainMenue::VScreenMainMenue(CFrame* frame)
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
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.27, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, IViewUIObserver::START_GAME);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.42, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, IViewUIObserver::MainOptions);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.57, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, IViewUIObserver::NOTHING);
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.72, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, IViewUIObserver::QUIT_GAME);
	
}


VScreenMainMenue::~VScreenMainMenue()
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

void VScreenMainMenue::onNotify(IViewUIObserver::Event events)
{
	switch (events)
	{
	default:
		notify(events);
		break;
	}
}

void VScreenMainMenue::checkShortcut(CDeviceKeyboard* keyboard)
{
	if(keyboard->KeyPressed(DIK_ESCAPE))
	{

	}
}
NAMESPACE_VIEW_E