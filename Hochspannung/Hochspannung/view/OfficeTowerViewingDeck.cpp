#include "OfficeTowerViewingDeck.h"

NAMESPACE_VIEW_B


COfficeTowerViewingDeck::COfficeTowerViewingDeck(float fResize)
{

	this->fResize = fResize;
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


	//window 
	InitWindows();

	//Add Door to Wall


	//Add Windows
	AddWindows();


	//Roundings
	Round();


	//Miters

	//Walls
	InitWalls();
	//m_zgGround.Init(40.0F, 0.1F, 40.0F, &m_zm);


	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");
	//m_zr.AddFrameHere(&m_zf);
	//m_zf.AddViewport(&m_zv);
	//m_zr.AddScene(&m_zs);

	//Placements
	AddPlacements();
	//m_zpOfficeTower.AddPlacement(&m_zpCamera);

	//m_zs.AddParallelLight(&m_zl);

	//m_zpCamera.Translate(0, 0, 5);
	//m_zpCamera.AddCamera(&m_zc);


	TranslateAll();



}

COfficeTowerViewingDeck::~COfficeTowerViewingDeck(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

/*
void COfficeTowerViewingDeck::Init(HWND hwnd, CSplash * psplash)
{}

void COfficeTowerViewingDeck::Tick(float fTime, float fTimeDelta)
{
// Hier die Echtzeit-Veränderungen einfügen:

m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
m_zdk.SetWASDRotationSensitivity(4);
m_zdk.SetWASDTranslationSensitivity(4.0F);
m_zr.Tick(fTimeDelta);



}


void COfficeTowerViewingDeck::Fini()
{
// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void COfficeTowerViewingDeck::WindowReSize(int iNewWidth, int iNewHeight)
{
// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}

*/

CPlacement*COfficeTowerViewingDeck::getPlacement(){
	return &m_zpOfficeTower;
}

void COfficeTowerViewingDeck::TranslateAll() {
	m_zpWall.TranslateDelta(CHVector(0.0F * fResize, 0.0F * fResize, 0.F * fResize));
	m_zpWall.AddGeo(&m_zgWall);

	m_zpWallTop.TranslateDelta(CHVector(0.0F * fResize, 30.0F * fResize, 0.0F * fResize));
	m_zpWallTop.AddGeo(&m_zgWallTop);

	//m_zpGround.Translate(CHVector(-20, 0, -20));
	//m_zpGround.AddGeo(&m_zgGround);
	m_zpRoof.Translate(CHVector(0, 30 * fResize, 0));
	m_zpRoof.AddGeo(&m_zgRoof);
	m_zpRoofTop.Translate(CHVector(0, 32 * fResize, 0));
	m_zpRoofTop.AddGeo(&m_zgRoofTop);
}

void COfficeTowerViewingDeck::AddPlacements() {

	m_zpOfficeTower.AddPlacement(&m_zpWall);
	m_zpOfficeTower.AddPlacement(&m_zpWallTop);
	m_zpOfficeTower.AddPlacement(&m_zpRoof);
	m_zpOfficeTower.AddPlacement(&m_zpRoofTop);

}

void COfficeTowerViewingDeck::InitWindows() {

	m_zgWindow.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 1 * fResize), true);
	m_zgRailing.InitRect(CFloatRect(0 * fResize, 0 * fResize, 0.95 * fResize, 0.7 * fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void COfficeTowerViewingDeck::AddWindows() {

	m_zgWall.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 1 * fResize, 20 * fResize, 28 * fResize), 25, 25);
	m_zgWall.AddGeoWindows(&m_zgRailing, CFloatRect(0 * fResize, 30 * fResize, 20 * fResize, 0.7 * fResize), 20, 1);
	m_zgWallTop.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 0.5F * fResize, 12.5 * fResize, 1 * fResize), 15, 1);

}

void COfficeTowerViewingDeck::InitWalls() {
	m_zgFrame.Init(1.0F, 1.0F, .25F, &m_zm);

	m_zgWall.Init(20.0F * fResize, 30.75F * fResize, .1F * fResize, &m_zm);
	m_zgWallTop.Init(12.50F * fResize, 2.0F * fResize, .1F * fResize, &m_zm);

	m_zgRoof.InitDomeCone(3.2F * fResize, 0.0F * fResize, 0.05 * fResize, &m_zm);
	m_zgRoofTop.InitDomeCone(2.0F * fResize, 0.0F * fResize, 0.05 * fResize, &m_zm);

}

void COfficeTowerViewingDeck::Round() {

	m_zgWall.SetRoundingX(-2 * PI, 0.05F * fResize);
	m_zgWallTop.SetRoundingX(-2 * PI, 0.05F * fResize);

}


NAMESPACE_VIEW_E
