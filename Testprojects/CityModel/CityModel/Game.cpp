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
	// Hier die Initialisierung der Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput);
	m_zv.InitFull(&m_zc);
	m_zc.Init();
	m_zl.Init(CHVector(2, 2, 2), CColor(2, 2, 2));

	

	m_zr.AddScene(&m_zs);
	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zf.AddDeviceKeyboard(&m_zdk);
	
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddParallelLight(&m_zl);
	m_zpCamera.AddCamera(&m_zc);

	
	city = new VModelCity;
	m_zpVCity = city->getMainPlacement();
	m_zs.AddPlacement(m_zpVCity);

	m_zpCamera.Translate(0, 50, 300);
	
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
	m_zdk.SetWASDRotationSensitivity(5.0F);
	m_zdk.SetWASDTranslationSensitivity(20.0F);
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






