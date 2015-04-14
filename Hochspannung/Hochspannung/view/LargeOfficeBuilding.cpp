#include "LargeOfficeBuilding.h"

NAMESPACE_VIEW_B


CLargeOfficeBuilding::CLargeOfficeBuilding(float fResize)
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

	//window 
	InitWindows();
	//Add Door to Wall
	//Add Windows
	AddWindows();


	//Walls
	InitWalls();

	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");
	//m_zmGround.MakeTextureDiffuse("textures\\green_image.jpg");
	//m_zmGlass.MakeTextureDiffuse("textures\\blue_image.jpg");

	//m_zr.AddFrameHere(&m_zf);
	//m_zf.AddViewport(&m_zv);
	//m_zr.AddScene(&m_zs);

	//Placements
	//m_zs.AddPlacement(&m_zpCamera);
	//m_zs.AddParallelLight(&m_zl);

	AddPlacements();

	//m_zpCamera.Translate(0, 0, 5);
	//m_zpCamera.AddCamera(&m_zc);

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CLargeOfficeBuilding::~CLargeOfficeBuilding(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

/*
void CLargeOfficeBuilding::Init(HWND hwnd, CSplash * psplash)
{

}

void CLargeOfficeBuilding::Tick(float fTime, float fTimeDelta)
{	// Hier die Echtzeit-Veränderungen einfügen:

	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
	m_zdk.SetWASDRotationSensitivity(2);
	m_zdk.SetWASDTranslationSensitivity(2.0F);
	m_zr.Tick(fTimeDelta);
}

void CLargeOfficeBuilding::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CLargeOfficeBuilding::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}
*/

CPlacement*CLargeOfficeBuilding::getPlacement(){
	return &m_zpLargeOfficeBuilding;
}

void CLargeOfficeBuilding::InitWindows() {

	m_zgDoor.InitRect(CFloatRect(0 * fResize, 0 * fResize, 1.25 * fResize, 1.75 * fResize), true);
	m_zgDoor.AddGeoWall(&m_zgFrame);

	m_zgWindow.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 1 * fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);
	m_zgWindowHigh.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 2 * fResize), true);
	m_zgWindowHigh.AddGeoWall(&m_zgFrame);
	m_zgWindowWide.InitRect(CFloatRect(1 * fResize, 1 * fResize, 2 * fResize, 0.75 * fResize), true);
	m_zgWindowWide.AddGeoWall(&m_zgFrame);

}

void CLargeOfficeBuilding::AddWindows() {

	m_zgWallSouth0.AddGeoWindows(&m_zgDoor, CFloatRect(1 * fResize, 0 * fResize, 1 * fResize, 1 * fResize), 1, 1);

	m_zgWallNorth0.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);
	m_zgWallNorth1.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 * fResize, 1 * fResize, 1 * fResize, 5 * fResize), 1, 2);
	m_zgWallNorth2.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 * fResize, 1 * fResize, 1 * fResize, 2.5F * fResize), 1, 1);

	m_zgWallSouth0.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);
	m_zgWallSouth1.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 * fResize, 1 * fResize, 1 * fResize, 5 * fResize), 1, 2);
	m_zgWallSouth2.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 * fResize, 1 * fResize, 1 * fResize, 2.5F * fResize), 1, 1);

	m_zgWallEast0.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 * fResize, 0 * fResize, 5 * fResize, 2 * fResize), 2, 2);
	m_zgWallEast1.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 * fResize, 0 * fResize, 5 * fResize, 2 * fResize), 2, 2);
	m_zgWallEast2.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 * fResize, 1 * fResize, 5 * fResize, 3 * fResize), 2, 3);

	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0, 2, 5, 6), 8, 5);

}

void CLargeOfficeBuilding::InitWalls() {
	
	m_zgFrame.Init(1.0F, 1.0F, .25F, &m_zm);

	m_zgWallNorth0.Init(3.1F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallNorth1.Init(1.1F * fResize, 6.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallNorth2.Init(1.1F * fResize, 4.0F * fResize, .1F * fResize, &m_zm);

	m_zgWallWest.Init(5.0F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);

	m_zgWallSouth0.Init(3.1F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallSouth1.Init(1.1F * fResize, 6.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallSouth2.Init(1.1F * fResize, 4.0F * fResize, .1F * fResize, &m_zm);

	m_zgWallEast0.Init(5.0F * fResize, 2.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallEast1.Init(5.0F * fResize, 2.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallEast2.Init(5.0F * fResize, 4.0F * fResize, .1F * fResize, &m_zm);

	m_zgRoof0.Init(3.0F * fResize, 0.1F * fResize, 5.0 * fResize, &m_zm);
	m_zgRoof1.Init(1.0F * fResize, 0.1F * fResize, 5.0 * fResize, &m_zm);
	m_zgRoof2.Init(1.0F * fResize, 0.1F * fResize, 5.0 * fResize, &m_zm);

	//m_zgGround.Init(40.0F, 0.1F, 40.0F, &m_zm);

}

void CLargeOfficeBuilding::AddPlacements() {

	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallNorth0);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallNorth1);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallNorth2);

	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallWest);

	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallEast0);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallEast1);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallEast2);

	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallSouth0);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallSouth1);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpWallSouth2);

	m_zpLargeOfficeBuilding.AddPlacement(&m_zpRoof0);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpRoof1);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpRoof2);

	//m_zpLargeOfficeBuilding.AddPlacement(&m_zpGround);
	m_zpLargeOfficeBuilding.AddPlacement(&m_zpDoor);

}

void CLargeOfficeBuilding::RotateAll() {

	m_zpWallEast0.Rotate(0, 1, 0, +1.570796326F);
	m_zpWallEast1.Rotate(0, 1, 0, +1.570796326F);
	m_zpWallEast2.Rotate(0, 1, 0, +1.570796326F);

	m_zpWallWest.Rotate(0, 1, 0, -1.570796326F);

	m_zpWallNorth0.Rotate(0, 1, 0, 3.141592652F);
	m_zpWallNorth1.Rotate(0, 1, 0, 3.141592652F);
	m_zpWallNorth2.Rotate(0, 1, 0, 3.141592652F);

}

void CLargeOfficeBuilding::TranslateAll() {

	m_zpWallNorth0.TranslateDelta(CHVector(3.0F * fResize, 0.0F * fResize, -4.9F * fResize));
	m_zpWallNorth0.AddGeo(&m_zgWallNorth0);
	m_zpWallNorth1.TranslateDelta(CHVector(4.0F * fResize, 0.0F * fResize, -4.9F * fResize));
	m_zpWallNorth1.AddGeo(&m_zgWallNorth1);
	m_zpWallNorth2.TranslateDelta(CHVector(5.0F * fResize, 0.0F * fResize, -4.9F * fResize));
	m_zpWallNorth2.AddGeo(&m_zgWallNorth2);

	m_zpWallSouth0.TranslateDelta(CHVector(0.0F * fResize, 0.0F * fResize, -0.1F * fResize));
	m_zpWallSouth0.AddGeo(&m_zgWallSouth0);
	m_zpWallSouth1.TranslateDelta(CHVector(3.0F * fResize, 0.0F * fResize, -0.1F * fResize));
	m_zpWallSouth1.AddGeo(&m_zgWallSouth1);
	m_zpWallSouth2.TranslateDelta(CHVector(4.0F * fResize, 0.0F * fResize, -0.1F * fResize));
	m_zpWallSouth2.AddGeo(&m_zgWallSouth2);

	m_zpWallWest.TranslateDelta(CHVector(0 * fResize, 0 * fResize, -5.0 * fResize));
	m_zpWallWest.AddGeo(&m_zgWallWest);

	m_zpWallEast0.TranslateDelta(CHVector(3.0 * fResize, 6.0F * fResize, 0.0F * fResize));
	m_zpWallEast0.AddGeo(&m_zgWallEast0);
	m_zpWallEast1.TranslateDelta(CHVector(4.0 * fResize, 4.0F * fResize, 0.0F * fResize));
	m_zpWallEast1.AddGeo(&m_zgWallEast1);
	m_zpWallEast2.TranslateDelta(CHVector(5.0 * fResize, 0.0F * fResize, 0.0F * fResize));
	m_zpWallEast2.AddGeo(&m_zgWallEast2);

	//m_zpGround.Translate(CHVector(-20.0F, 0, -20.0F));
	//m_zpGround.AddGeo(&m_zgGround);

	m_zpRoof0.Translate(CHVector(0 * fResize, 7.9F * fResize, -5.0F * fResize));
	m_zpRoof0.AddGeo(&m_zgRoof0);
	m_zpRoof1.Translate(CHVector(3 * fResize, 5.9F * fResize, -5.0F * fResize));
	m_zpRoof1.AddGeo(&m_zgRoof1);
	m_zpRoof2.Translate(CHVector(4 * fResize, 3.9F * fResize, -5.0F * fResize));
	m_zpRoof2.AddGeo(&m_zgRoof2);

}


NAMESPACE_VIEW_E
