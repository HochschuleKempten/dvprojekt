#include "SmallOfficeBuilding.h"

NAMESPACE_VIEW_B


CSmallOfficeBuilding::CSmallOfficeBuilding(float fResize)
{

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
	//m_zr.AddFrameHere(&m_zf);
	//m_zf.AddViewport(&m_zv);
	//m_zr.AddScene(&m_zs);

	//Placements
	AddPlacements();
	//	m_zpOfficeBuilding.AddParallelLight(&m_zl);

	//m_zpCamera.Translate(0, 0, 5);
	//m_zpCamera.AddCamera(&m_zc);

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CSmallOfficeBuilding::~CSmallOfficeBuilding(void)
{
}

/*
void CSmallOfficeBuilding::Init(HWND hwnd, CSplash * psplash)
{

}

void CSmallOfficeBuilding::Tick(float fTime, float fTimeDelta)
{
// Hier die Echtzeit-Veränderungen einfügen:

m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
m_zdk.SetWASDRotationSensitivity(2);
m_zdk.SetWASDTranslationSensitivity(2.0F);
m_zr.Tick(fTimeDelta);




}

void CSmallOfficeBuilding::Fini()
{
// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CSmallOfficeBuilding::WindowReSize(int iNewWidth, int iNewHeight)
{
// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}

*/

CPlacement*CSmallOfficeBuilding::getPlacement(){
	return &m_zpOfficeBuilding;
}

void CSmallOfficeBuilding::InitWindows() {

	m_zgDoor.InitRect(CFloatRect(1 * fResize, 1 * fResize, 1 * fResize, 1 * fResize), true);
	m_zgWindow.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 1 * fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void CSmallOfficeBuilding::AddWindows() {

	m_zgWallSouth.AddGeoWindows(&m_zgDoor, CFloatRect(1 * fResize, 0.5 * fResize, 1 * fResize, 1 * fResize), 1, 4);

	m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);
	m_zgWallSouth.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);
	m_zgWallEast.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);
	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 2 * fResize, 3 * fResize, 6 * fResize), 4, 5);

}

void CSmallOfficeBuilding::InitWalls() {

	m_zgFrame.Init(1.0F, 1.0F, .25F, &m_zm);
	m_zgWallNorth.Init(3.0F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallWest.Init(3.0F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallSouth.Init(3.0F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallEast.Init(3.0F * fResize, 8.0F * fResize, .1F * fResize, &m_zm);

	m_zgRoof.Init(3.0F * fResize, 0.1F * fResize, 3.0 * fResize, &m_zm);
	//m_zgGround.Init(3.0F, 0.1F, 3.0F, &m_zm);

}

void CSmallOfficeBuilding::AddPlacements() {
	
	m_zpOfficeBuilding.AddPlacement(&m_zpWallNorth);
	m_zpOfficeBuilding.AddPlacement(&m_zpWallWest);
	m_zpOfficeBuilding.AddPlacement(&m_zpWallEast);
	m_zpOfficeBuilding.AddPlacement(&m_zpWallSouth);
	m_zpOfficeBuilding.AddPlacement(&m_zpRoof);
	//m_zpOfficeBuilding.AddPlacement(&m_zpGround);
	//m_zpOfficeBuilding.AddPlacement(&m_zpCamera);
	m_zpOfficeBuilding.AddPlacement(&m_zpDoor);

}

void CSmallOfficeBuilding::RotateAll() {

	m_zpWallEast.Rotate(0, 1, 0, +1.570796326F);
	m_zpWallWest.Rotate(0, 1, 0, -1.570796326F);
	m_zpWallNorth.Rotate(0, 1, 0, 3.141592652F);

}

void CSmallOfficeBuilding::TranslateAll() {

	m_zpWallNorth.TranslateDelta(CHVector(3.0F * fResize, 0 * fResize, 0.1F * fResize));
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallSouth.TranslateDelta(CHVector(0 * fResize, 0 * fResize, 2.9F * fResize));
	m_zpWallSouth.AddGeo(&m_zgWallSouth);
	m_zpWallWest.TranslateDelta(CHVector(0 * fResize, 0 * fResize, 0 * fResize));
	m_zpWallWest.AddGeo(&m_zgWallWest);
	m_zpWallEast.TranslateDelta(CHVector(3.0 * fResize, 0.0F * fResize, 3.0F * fResize));
	m_zpWallEast.AddGeo(&m_zgWallEast);
	//m_zpGround.Translate(CHVector(0, 0, 0));
	//m_zpGround.AddGeo(&m_zgGround);
	m_zpRoof.Translate(CHVector(0 * fResize, 7.9 * fResize, 0 * fResize));
	m_zpRoof.AddGeo(&m_zgRoof);

}


NAMESPACE_VIEW_E
