#include "StdAfx.h"
#include "Game.h"
#include "../../../Hochspannung/Hochspannung/view/Helper.h"

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

	//m_zs.AddPlacement(&m_zp);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddParallelLight(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.RotateXDelta(AngleToRad(-30));
	m_zpCamera.TranslateZDelta(2.0f);
	m_zpCamera.TranslateYDelta(2.5f);
	m_zpCamera.SetFrustumCullingOn();
	
	m_zs.AddPlacement(m_zTrasse1->getMainPlacement());
	m_zs.AddPlacement(m_zTrasse2->getMainPlacement());
	m_zs.AddPlacement(m_zTrasse3->getMainPlacement());
	m_zs.AddPlacement(m_zTrasse4->getMainPlacement());

	m_zTrasse1->Init(VModelPowerLine::DIRECTION::EAST | VModelPowerLine::DIRECTION::WEST | VModelPowerLine::DIRECTION::SOUTH | VModelPowerLine::DIRECTION::NORTH);
	m_zTrasse2->Init(VModelPowerLine::DIRECTION::EAST | VModelPowerLine::DIRECTION::WEST | VModelPowerLine::DIRECTION::SOUTH | VModelPowerLine::DIRECTION::NORTH);
	m_zTrasse3->Init(VModelPowerLine::DIRECTION::EAST | VModelPowerLine::DIRECTION::WEST | VModelPowerLine::DIRECTION::SOUTH | VModelPowerLine::DIRECTION::NORTH);
	m_zTrasse4->Init(VModelPowerLine::DIRECTION::EAST | VModelPowerLine::DIRECTION::WEST | VModelPowerLine::DIRECTION::SOUTH | VModelPowerLine::DIRECTION::NORTH);

	m_zTrasse1->SetPosition(-1, 0);
	m_zTrasse2->SetPosition(1, 0);
	VModelPowerLine::DIRECTION test = m_zTrasse1->Direction();

	m_zTrasse3->SetPosition(3, 0);
	m_zTrasse4->SetPosition(3, -2);

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
	// Windows ReSize wird immer automatisch aufgerufen,		 wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}
