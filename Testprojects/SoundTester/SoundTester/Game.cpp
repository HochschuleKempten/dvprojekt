#include "StdAfx.h"
#include "Game.h"



CGame::CGame(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

void CGame::Init(HWND hwnd, CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	// Root initialisieren
	m_root.Init(psplash);
	// Frame initialisieren
	m_frame.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput, eApiSound_DirectSound);
	// Kamera initialisieren
	m_camera.Init();
	// Viewport initialisieren
	m_viewport.InitFull(&m_camera);
	// Beleuchtung initialisieren
	m_light.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Frame an Root anhängen
	m_root.AddFrameHere(&m_frame);
	// Viewport an den Frame anhängen
	m_frame.AddViewport(&m_viewport);
	// Szene an Root anhängen
	m_root.AddScene(&m_scene);

	//Sound tests
	m_audio0.Init("res/Vektoria.wav");
	m_audio0.SetVolume(1);
	m_audio1.Init3D("res/Vektoria.wav", 20);
	m_placeSound0.AddAudio(&m_audio1);

	// Placements und Beleuchtung zur Szene hinzufügen
	m_scene.AddPlacement(&m_placeSound0);

	// Kamera dem Placement hinzufügen
	m_placeCamera.AddCamera(&m_camera);

	// Kamera positionieren
	m_placeCamera.Translate(CHVector(0, 0, 3));

	m_audio0.Start();
	//m_audio1.Start();
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:

	// Tick im Root aufrufen
	m_root.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	//m_frame.ReSize(iNewWidth, iNewHeight);
}

