#include "StdAfx.h"
#include "Game.h"
#include <sstream>

#define DEBUG_OUTPUT(expr) do { std::stringstream s; s << expr << std::endl; OutputDebugString(s.str().c_str()); } while(0)

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
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	//m_zc.Init(120 * M_PI / 180, 0.1f);
	m_zc.Init();
	m_zv.InitFull(&m_zc);
	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zf.AddDeviceKeyboard(&m_zk);
	m_zf.AddDeviceCursor(&m_zkCursor);
	m_zf.AddDeviceMouse(&m_zkMouse);
	m_zr.AddScene(&m_zs);

	m_zb.InitFull("textures/red_image.jpg");
	m_zv.AddBackground(&m_zb);

	m_zs.AddPlacement(&m_zpCamera);
	m_zpCamera.AddCamera(&m_zc);
	m_zs.AddPlacement(&m_zpCentral);
	m_zs.AddParallelLight(&m_zl);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f),
			  CColor(1.0f, 1.0f, 1.0f));

	m_zm.MakeTextureDiffuse("textures\\_original.jpg");

	CHVector size(2, 2, 0.5);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::stringstream stream;
			stream << "i = " << i << ", j = " << j;

			m_zg[i][j].Init(size, &m_zm);
			m_zg[i][j].SetName(stream.str().c_str());
			m_zp[i][j].AddGeo(&m_zg[i][j]);
			m_zp[i][j].SetName(stream.str().c_str());
			m_zpCentral.AddPlacement(&m_zp[i][j]);

			m_zp[i][j].TranslateX(i * 4.1);
			m_zp[i][j].TranslateYDelta(j * 4.1);
		}
	}

	//m_zpCentral.RotateX(-40 * M_PI / 180);
	//m_zpCentral.RotateXDelta(0.1);
	m_zpCentral.TranslateDelta(-4, -4, -6);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zk.PlaceWASD(m_zpCamera, fTimeDelta);

	/* Picking */
	static bool pickingActive = false;

	float f;
	CGeo* pickedGeo = m_zkCursor.PickGeo(CHVector(), f);
	CPlacement* pickedPlacement = m_zkCursor.PickPlacement();

	if (pickedGeo != nullptr) {
		DEBUG_OUTPUT("picked geo = " << pickedGeo->GetName());
	}

	if (pickedPlacement != nullptr) {
		DEBUG_OUTPUT("picked placement = " << pickedPlacement->GetName());
	}

	// Hier die Echtzeit-Veränderungen einfügen:
	m_zr.Tick(fTimeDelta);



	//m_vMaster.tick(fTime, fTimeDelta);
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

