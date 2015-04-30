#include "VScreenMainMenue.h"
#include "VUI.h"

NAMESPACE_VIEW_B

VScreenMainMenue::VScreenMainMenue(VUI* vUi) : IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);

	m_flash = new COverlay();
	m_background = new CBackground();
	m_headline = new COverlay();
	
	m_background->InitFull("textures\\MainMenueBackground.png");
	m_flash->Init("textures\\Blitz.png", CFloatRect(0.75, 0.2, 0.20, 0.7));
	m_headline->Init("textures\\Hochvolt.png", CFloatRect(0.20, 0.05, 0.6, 0.15));

	m_viewport->AddBackground(m_background);
	m_viewport->AddOverlay(m_flash);
	m_viewport->AddOverlay(m_headline);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.27, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, SWITCH_TO_LOBBY,"buttonSwitchToPlayMode");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.42, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueOptionen, &VMaterialLoader::materialButtonMainMenueOptionenHover, SWITCH_TO_OPTIONS, "buttonSwitchToOptions");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.57, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, SWITCH_TO_CREDITS, "buttonSwitchToCredits");
	getContainer("Menue")->addButton(CFloatRect(0.33, 0.72, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueSpielBeenden, &VMaterialLoader::materialButtonMainMenueSpielBeendenHover, QUIT_GAME, "buttonQuitGame");
	
	

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
	delete m_viewport;
}

void VScreenMainMenue::onNotify(Event events)
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

	void VScreenMainMenue::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}

	void VScreenMainMenue::resize(int width, int height)
	{
	}

	void VScreenMainMenue::tick()
	{
	}

	NAMESPACE_VIEW_E