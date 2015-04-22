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
	//Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	//Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	vMaster.resize(iNewWidth, iNewHeight);
}
