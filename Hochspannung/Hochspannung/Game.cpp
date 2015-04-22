#include "Game.h"
#include "view\VPlayingField.h"

CGame::CGame(void)
	: lMaster(vMaster)
{

#ifdef _DEBUG
	/* Redirect IO to console for debugging */
	redirectIOToConsole();
#endif // DEBUG

	vMaster.setLMaster(&lMaster);
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einf�gen:
}

void CGame::Init(HWND hwnd, CSplash *psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einf�gen:
	vMaster.initScene(hwnd, psplash);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	vMaster.tick(fTime, fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	//Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	//Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:
	vMaster.resize(iNewWidth, iNewHeight);
}
