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
	// Hier die Initialisierung der Vektoria-Objekte einf�gen:
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zv.InitFull(&m_zc);
	m_zo.InitFull(&m_zi);
	m_zi.Init("textures\\HalloWelt.bmp");

	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zv.AddOverlay(&m_zo);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Ver�nderungen einf�gen:
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	// Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:

}
