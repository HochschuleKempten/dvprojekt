#include "StdAfx.h"
#include "Game.h"
#include <sstream>

CGame::CGame(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

void CGame::Init(HWND hwnd, CSplash *psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einf�gen:
	m_vMaster.initScene(hwnd, psplash);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_vMaster.tick(fTime, fTimeDelta);
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

