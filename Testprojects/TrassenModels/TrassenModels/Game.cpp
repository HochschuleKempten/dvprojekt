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
	//Initiate all the basic stuff
	m_zr.Init(psplash);
	m_zc.Init();
	m_zf.Init(hwnd);
	m_zdk.SetWASDRotationSensitivity(5.0f);
	m_zdk.SetWASDTranslationSensitivity(5.0f);
	m_zf.AddDeviceKeyboard(&m_zdk);
	m_zv.InitFull(&m_zc);
	//m_zv.SetWireframeOn();
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));
	
	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);

	m_zs.AddPlacement(&m_zp);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddParallelLight(&m_zl);
	m_zpCamera.AddCamera(&m_zc);

	m_zs.AddPlacement(m_zTrasse);
	m_zTrasse->Init();
	m_zTrasse->Translate(CHVector(0, 0, -2.0f));
	//m_zTester->Init(&m_zs);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}
