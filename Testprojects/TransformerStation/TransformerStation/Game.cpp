#include "StdAfx.h"
#include "Game.h"
#include <filesystem>
#include "../../../Hochspannung/Hochspannung/view/VMaterialLoader.h"


CGame::CGame(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:
	std::tr2::sys::current_path(std::tr2::sys::path("../../../Hochspannung/Hochspannung"));
	VMaterialLoader::init();
}

CGame::~CGame(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

void CGame::Init(HWND hwnd, CSplash * psplash)
{
	m_hwnd = hwnd;
	m_bReSized = false;
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zf.Init(hwnd);
	m_zcFront.Init();

	m_zvFront.InitFull(&m_zcFront);

	m_zl.Init(CHVector(1, 1, 2), CColor(1, 1, 1));


	m_zr.AddFrameHere(&m_zf);
	m_zf.AddViewport(&m_zvFront);

	m_zf.AddDeviceKeyboard(&m_zdk);
	m_zr.AddScene(&m_zs);
	m_zs.AddParallelLight(&m_zl);

	//Placements

	m_zs.AddPlacement(&m_zpCameraFront);

	
	m_zpTransformerStation.getMainPlacement()->Translate(CHVector(2.0f, -2.0f, 3.0f));

	m_zs.AddPlacement(m_zpTransformerStation.getMainPlacement());


	//Adding
	m_zpCameraFront.Translate(CHVector(0.0f, -2.0f, 5.0f));
	m_zpCameraFront.AddCamera(&m_zcFront);

	std::string text = "Testqüöä123";
	std::string call = "textures\\DynamischerTest\\convert -size 320x85 canvas:none -pointsize 72 -draw \"text 25, 60 '" + text + "'\" -channel RGBA -fill darkred test.png";
	system(call.c_str());
	overlayDynTest.Init("test.png", CFloatRect(0.1, 0.1, 0.7, 0.26));
	m_zvFront.AddOverlay(&overlayDynTest);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	m_zdk.PlaceWASD(m_zpCameraFront, fTimeDelta);

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

