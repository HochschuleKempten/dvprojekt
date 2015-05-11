#include "StdAfx.h"
#include "Game.h"



CGame::CGame(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

void CGame::Init(HWND hwnd, CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einf�gen:
	// Root initialisieren
	m_root.Init(psplash);
	// Frame initialisieren
	m_frame.Init(hwnd, eApiRender_DirectX11_Shadermodel50);
	// Kamera initialisieren
	m_camera.Init();
	// Viewport initialisieren
	m_viewport.InitFull(&m_camera);
	// Beleuchtung initialisieren
	m_light.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Frame an Root anh�ngen
	m_root.AddFrameHere(&m_frame);
	// Viewport an den Frame anh�ngen
	m_frame.AddViewport(&m_viewport);
	// Szene an Root anh�ngen
	m_root.AddScene(&m_scene);

	// Placements und Beleuchtung zur Szene hinzuf�gen
	m_scene.AddPlacement(&m_placeSound0);

	// Kamera dem Placement hinzuf�gen
	m_placeCamera.AddCamera(&m_camera);

	// Kamera positionieren
	m_placeCamera.Translate(CHVector(0, 0, 3));
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Ver�nderungen einf�gen:

	// Tick im Root aufrufen
	m_root.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	// Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:
	//m_frame.ReSize(iNewWidth, iNewHeight);
}

