#include "VScreenLobby.h"
#include "VUI.h"

NAMESPACE_VIEW_B

VScreenLobby::VScreenLobby(VUI* vUi): IViewScreen(vUi)
{
	m_viewport = new CViewport();
	m_camera.Init();
	m_viewport->InitFull(&m_camera);
	vUi->m_zf.AddViewport(m_viewport);


	m_background = new CBackground();

	m_background->InitFull("textures\\MainMenueBackground.png");

	m_bigDialog = new COverlay();
	m_bigDialog->Init("textures\\LobbyBigDialog.png", CFloatRect(0.01, 0.05, 0.6, 0.76), false);
	m_bigDialog->SetLayer(0.9);
	m_viewport->AddBackground(m_background);
	m_viewport->AddOverlay(m_bigDialog);

	addContainer(m_viewport,IViewGUIContainer::ContainerType::Group, CFloatRect(0, 0.7F, 1.0F, 0.3F), "Menue");
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.83, 0.30, 0.12), &VMaterialLoader::materialButtonBack, &VMaterialLoader::materialButtonBackHover, SWITCH_TO_MAINMENUE,"buttonBackToPlaymode");
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.05, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueNeuesSpiel, &VMaterialLoader::materialButtonMainMenueNeuesSpielHover, START_GAME,"buttonStartGame");
	getContainer("Menue")->addButton(CFloatRect(0.65, 0.19, 0.30, 0.12), &VMaterialLoader::materialButtonMainMenueCredits, &VMaterialLoader::materialButtonMainMenueCreditsHover, NOTHING,"iwas");
	getContainer("Menue")->addTextfield(CFloatRect(0.02, 0.06, 0.30, 0.08), &VMaterialLoader::materialIngameBorder, &VMaterialLoader::materialRed, &VMaterialLoader::materialGreen,30,"Suche IP-Adresse...","textfieldIP");
	
}

VScreenLobby::~VScreenLobby()
{
	for (m_IterGuicontainer = m_Guicontainer.begin(); m_IterGuicontainer != m_Guicontainer.end(); ++m_IterGuicontainer)
	{
		delete m_IterGuicontainer->second;
	}
	m_Guicontainer.clear();

	delete m_viewport;
	delete m_background;
	delete m_bigDialog;

	}
void VScreenLobby::onNotify(Event events)
{
	switch (events)
	{

	default:
		notify(events);
		break;
	}
}
void VScreenLobby::checkShortcut(CDeviceKeyboard* keyboard)
{
	if (keyboard->KeyPressed(DIK_ESCAPE))
	{
		notify(SWITCH_TO_SPIELMODUS);
	}
	if (keyboard->KeyPressed(DIK_K))
	{
		
	}

}

	void VScreenLobby::checkSpecialEvent(CDeviceCursor* cursor)
	{
	}

	void VScreenLobby::tick()
	{
	}

	void VScreenLobby::resize(int width, int height)
	{
	}

	NAMESPACE_VIEW_E