#include "StdAfx.h"
#include "Game.h"
#include <sstream>
#include "view\VPlayingField.h"
#include "logic\LPlayingField.h"

CGame::CGame(void)
	: lMaster(&vMaster)
{
	vMaster.setLMaster(&lMaster);
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

void CGame::Init(HWND hwnd, CSplash *psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	vMaster.initScene(hwnd, psplash);
	lMaster.getLPlayingField()->initVPlayingField();
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	vMaster.tick(fTime, fTimeDelta);
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
