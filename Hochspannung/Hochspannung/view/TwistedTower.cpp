#include "TwistedTower.h"

NAMESPACE_VIEW_B


CTwistedTower::CTwistedTower(void)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:

	//m_hwnd = hwnd;
	//m_bReSized = false;
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	//m_zr.Init(psplash);
	//m_zc.Init();
	//m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput);
	//m_zf.AddDeviceKeyboard(&m_zdk);
	//m_zv.InitFull(&m_zc);
	//m_zl.Init(CHVector(1, 1, 1), CColor(1, 1, 1));
	this->fResize = fResize;

	//Window 
	InitWindows();

	//Miters
	CreateMiters();


	//Add Windows
	AddWindows();

	//Walls
	InitWalls();


	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");
	//m_zr.AddFrameHere(&m_zf);
	//m_zf.AddViewport(&m_zv);
	//m_zr.AddScene(&m_zs);

	//Placements
	AddPlacements();

	//m_zs.AddParallelLight(&m_zl);

	//m_zpCamera.Translate(0, 0, 5);
	//m_zpCamera.AddCamera(&m_zc);

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CTwistedTower::~CTwistedTower(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}
/*
void CTwistedTower::Init(HWND hwnd, CSplash * psplash)
{
}

void CTwistedTower::Tick(float fTime, float fTimeDelta)
{	// Hier die Echtzeit-Veränderungen einfügen:

m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
m_zdk.SetWASDRotationSensitivity(2);
m_zdk.SetWASDTranslationSensitivity(2.0F);
m_zr.Tick(fTimeDelta);
}

void CTwistedTower::Fini()
{
// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CTwistedTower::WindowReSize(int iNewWidth, int iNewHeight)
{
// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}
*/

CPlacement*CTwistedTower::getPlacement(){
	return &m_zpTwistedTower;
}

void CTwistedTower::InitWindows() {

	m_zgWindow.InitRect(CFloatRect(1, 1, 0.5, 1), true);

}

void CTwistedTower::CreateMiters() {

	m_zgRoof.SetMiterLeft(PI / 3);
	m_zgRoof.SetMiterRight(PI / 3);

	m_zgWallNorth.SetMiterLeft(PI / 3);
	m_zgWallNorth.SetMiterRight(PI / 3);

	m_zgWallEast.SetMiterLeft(PI / 3);
	m_zgWallEast.SetMiterRight(PI / 3);

	m_zgWallWest.SetMiterLeft(PI / 3);
	m_zgWallWest.SetMiterRight(PI / 3);

}

void CTwistedTower::AddWindows() {

	m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 1, 3, 6), 4, 5);

}

void CTwistedTower::InitWalls() {

	//m_zgGround.Init(40.0F, 0.1F, 40.0F, &m_zm);
	m_zgRoof.Init(3.0F, 0.1F, 2.598F, &m_zm);

	m_zgWallNorth.Init(3, 5, 0.2, &m_zm);
	m_zgWallEast.Init(3, 5, 0.2, &m_zm);
	m_zgWallWest.Init(3, 5, 0.2, &m_zm);

}

void CTwistedTower::AddPlacements() {

	//m_zs.AddPlacement(&m_zpGround);
	m_zpTwistedTower.AddPlacement(&m_zpRoof);

	//m_zs.AddPlacement(&m_zpCamera);

	m_zpTwistedTower.AddPlacement(&m_zpWallNorth);
	m_zpTwistedTower.AddPlacement(&m_zpWallEast);
	m_zpTwistedTower.AddPlacement(&m_zpWallWest);

}

void CTwistedTower::RotateAll(){

	m_zpWallNorth.Rotate(0, 1, 0, 0);
	m_zpWallEast.Rotate(0, 1, 0, -2.0943951F);
	m_zpWallWest.Rotate(0, 1, 0, +2.0943951F);

}

void CTwistedTower::TranslateAll() {

	//m_zpGround.Translate(CHVector(-20.0F, 0, -20.0F));
	//m_zpGround.AddGeo(&m_zgGround);
	m_zpRoof.Translate(CHVector(0.0F, 0.0F, 0.0F));
	m_zpRoof.AddGeo(&m_zgRoof);

	m_zpWallNorth.TranslateDelta(CHVector(0, 0, 0));
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallEast.TranslateDelta(CHVector(1.6F, 0, -2.598F));
	m_zpWallEast.AddGeo(&m_zgWallEast);
	m_zpWallWest.TranslateDelta(CHVector(2.8F, 0, 0.2F));
	m_zpWallWest.AddGeo(&m_zgWallWest);

}


NAMESPACE_VIEW_E
