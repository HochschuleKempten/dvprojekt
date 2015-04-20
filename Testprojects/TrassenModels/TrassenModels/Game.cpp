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
	m_zpCamera.RotateXDelta(CHelper::AngleToRad(-30));
	m_zpCamera.TranslateZDelta(2.0f);
	m_zpCamera.TranslateYDelta(2.5f);
	m_zpCamera.SetFrustumCullingOn();

	m_zs.AddPlacement(m_zTrasse1);
	m_zs.AddPlacement(m_zTrasse2);
	m_zs.AddPlacement(m_zTrasse3);
	m_zs.AddPlacement(m_zTrasse4);

	m_zTrasse1->Init(VModelPowerLine::PYLONTYPE::STRAIGHT, VModelPowerLine::WEST);
	m_zTrasse2->Init(VModelPowerLine::PYLONTYPE::CROSS);
	m_zTrasse3->Init(VModelPowerLine::PYLONTYPE::CROSS, VModelPowerLine::DIRECTION::EAST);
	m_zTrasse4->Init(VModelPowerLine::PYLONTYPE::ANGLE, VModelPowerLine::EAST);

	//m_zTrasse1->Translate(CHVector(-1.0f, 0, 1));
	//m_zTrasse2->Translate(CHVector(0, 0, 0));
	//m_zTrasse3->Translate(CHVector(1, 0, 1));
	//m_zTrasse4->Translate(CHVector(2, 0, -1));

	m_zTrasse1->SetPosition(-1, 0);
	m_zTrasse2->SetPosition(2, 0);
	m_zTrasse3->SetPosition(-1, -2);
	m_zTrasse4->SetPosition(2, -2);

	m_zTrasse1->ConnectTo(m_zTrasse2);
	m_zTrasse1->ConnectTo(m_zTrasse3);
	m_zTrasse2->ConnectTo(m_zTrasse4);
	m_zTrasse3->ConnectTo(m_zTrasse4);

	//m_zTester->Init(&m_zs);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
	m_zr.Tick(fTimeDelta);
	//m_zTrasse1->TranslateX(sinf(fTime) - 1);
	//m_zTrasse2->TranslateX(-sinf(fTime) + 1);
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
