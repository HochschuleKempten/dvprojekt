#include "Appartments.h"

NAMESPACE_VIEW_B


CAppartments::CAppartments(float fResize)
{
	// Hier eventuelle Vorinitialisierungen Deiner Vektoria-Objekte einfügen:

	//m_hwnd = hwnd;
	//m_bReSized = false;
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	//m_zr.Init(psplash);
	//m_zc.Init();
	//	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput);
	//m_zf.AddDeviceKeyboard(&m_zdk);
	//m_zv.InitFull(&m_zc);
	//m_zl.Init(CHVector(1, 1, 1), CColor(1, 1, 1));
	this->fResize = fResize;


	//Initialize Windows
	InitWindows();


	//Add Windows
	AddWindows();


	//TODO (NM)
	//Das Dach Abrunden.

	//Init Walls
	InitWalls();



	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");
	//m_zr.AddFrameHere(&m_zf);
	//m_zf.AddViewport(&m_zv);
	//m_zr.AddScene(&m_zs);

	//Placements
	AddPlacements();
	//m_zpAppartments.AddParallelLight(&m_zl);

	//m_zpCamera.Translate(0, 0, 5);
	//m_zpCamera.AddCamera(&m_zc);

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CAppartments::~CAppartments(void)
{
	// Hier eventuelle Nachinitialisierungen Deiner Vektoria-Objekte einfügen:
}

/*
void CAppartments::Init(HWND hwnd, CSplash * psplash)
{
//m_hwnd = hwnd;
//m_bReSized = false;
// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
//m_zr.Init(psplash);
//m_zc.Init();
//	m_zf.Init(hwnd, eApiRender_DirectX11_Shadermodel50, eApiInput_DirectInput);
//m_zf.AddDeviceKeyboard(&m_zdk);
//m_zv.InitFull(&m_zc);
//m_zl.Init(CHVector(1, 1, 1), CColor(1, 1, 1));

//window
m_zgWindow.InitRect(CFloatRect(1, 1, 0.5, 1), true);
m_zgWindow.AddGeoWall(&m_zgFrame);
//Add Door to Wall


//Add Windows
m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5, 1, 17, 8), 12, 6);
m_zgWallSouth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5, 1, 17, 8), 12, 6);
m_zgWallEast.AddGeoWindows(&m_zgWindow, CFloatRect(0.1, 1, 2.9, 8), 3, 6);
m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0.1, 1, 2.9, 8), 3, 6);

//Rounding

//TODO (NM)
//Das Dach Abrunden.

//Walls
m_zgFrame.Init(1, 1, 0.1, &m_zm);

m_zgWallNorth.Init(17.5F, 9.0F, .1F, &m_zm);
m_zgWallWest.Init(3.0F, 9.0F, .1F, &m_zm);
m_zgWallSouth.Init(17.5F, 9.0F, .1F, &m_zm);
m_zgWallEast.Init(3.0F, 9.0F, .1F, &m_zm);

m_zgRoof.Init(17.5F, 0.1F, 3.0F, &m_zm);
m_zgGround.Init(17.5F, 0.1F, 3.0F, &m_zm);



m_zm.MakeTextureDiffuse("textures\\white_image.jpg");
m_zr.AddFrameHere(&m_zf);
m_zf.AddViewport(&m_zv);
m_zr.AddScene(&m_zs);

//Placements
m_zs.AddPlacement(&m_zpWallNorth);
m_zs.AddPlacement(&m_zpWallWest);
m_zs.AddPlacement(&m_zpWallEast);
m_zs.AddPlacement(&m_zpWallSouth);
m_zs.AddPlacement(&m_zpRoof);

m_zs.AddPlacement(&m_zpGround);
m_zs.AddPlacement(&m_zpCamera);
m_zs.AddParallelLight(&m_zl);

m_zpCamera.Translate(0, 0, 5);
m_zpCamera.AddCamera(&m_zc);

//Rotations
m_zpWallEast.Rotate(0, 1, 0, 1.570796326F);
m_zpWallWest.Rotate(0, 1, 0, -1.570796326F);
m_zpWallNorth.Rotate(0, 1, 0, 3.1415928F);


//Translations
m_zpWallNorth.TranslateDelta(CHVector(17.4, 0, 0));
m_zpWallNorth.AddGeo(&m_zgWallNorth);
m_zpWallSouth.TranslateDelta(CHVector(0, 0, 2.9F));
m_zpWallSouth.AddGeo(&m_zgWallSouth);
m_zpWallWest.TranslateDelta(CHVector(0, 0, 0));
m_zpWallWest.AddGeo(&m_zgWallWest);
m_zpWallEast.TranslateDelta(CHVector(+17.4F, 0, +2.9F));
m_zpWallEast.AddGeo(&m_zgWallEast);
m_zpGround.Translate(CHVector(0, 0, 0));
m_zpGround.AddGeo(&m_zgGround);
m_zpRoof.Translate(CHVector(0, 8.9, 0));
m_zpRoof.AddGeo(&m_zgRoof);


//Textures
m_zgWallNorth.SetTextureStart(0.0F, 0.0F);
m_zgWallNorth.SetTextureRepeat(3.0F, 4.0F);


//Miters
m_zgWallNorth.SetMiterLeft(1.570796326F);
m_zgWallNorth.SetMiterRight(1.570796326F);





}
*/
//void CAppartments::Tick(float fTime, float fTimeDelta)
//{	// Hier die Echtzeit-Veränderungen einfügen:

//	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
//	m_zdk.SetWASDRotationSensitivity(2);
//	m_zdk.SetWASDTranslationSensitivity(2.0F);
//	m_zr.Tick(fTimeDelta);
//}

/*
void CAppartments::Fini()
{
// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CAppartments::WindowReSize(int iNewWidth, int iNewHeight)
{
// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
// Hier kannst Du dann die Auflösung des Viewports neu einstellen:

}

*/

CPlacement*CAppartments::getPlacement(){
	return &m_zpAppartments;
}

void CAppartments::InitWindows() {
	m_zgWindow.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 1 * fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);
}

void CAppartments::AddWindows() {

	m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5 * fResize, 1 * fResize, 17 * fResize, 8 * fResize), 12, 6);
	m_zgWallSouth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5 * fResize, 1 * fResize, 17 * fResize, 8 * fResize), 12, 6);
	m_zgWallEast.AddGeoWindows(&m_zgWindow, CFloatRect(0.1 * fResize, 1 * fResize, 2.9 * fResize, 8 * fResize), 3, 6);
	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0.1 * fResize, 1 * fResize, 2.9 * fResize, 8 * fResize), 3, 6);

}

void CAppartments::InitWalls(){

	m_zgFrame.Init(1, 1, 0.1, &m_zm);

	m_zgWallNorth.Init(17.5F * fResize, 9.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallWest.Init(3.0F * fResize, 9.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallSouth.Init(17.5F * fResize, 9.0F * fResize, .1F * fResize, &m_zm);
	m_zgWallEast.Init(3.0F * fResize, 9.0F * fResize, .1F * fResize, &m_zm);

	m_zgRoof.Init(17.5F * fResize, 0.1F * fResize, 3.0F * fResize, &m_zm);
	//m_zgGround.Init(17.5F, 0.1F, 3.0F, &m_zm);
}

void CAppartments::AddPlacements() {

	m_zpAppartments.AddPlacement(&m_zpWallNorth);
	m_zpAppartments.AddPlacement(&m_zpWallWest);
	m_zpAppartments.AddPlacement(&m_zpWallEast);
	m_zpAppartments.AddPlacement(&m_zpWallSouth);
	m_zpAppartments.AddPlacement(&m_zpRoof);

	//m_zpAppartments.AddPlacement(&m_zpGround);
	//m_zpAppartments.AddPlacement(&m_zpCamera);

}

void CAppartments::RotateAll() {

	m_zpWallEast.Rotate(0, 1, 0, 1.570796326F);
	m_zpWallWest.Rotate(0, 1, 0, -1.570796326F);
	m_zpWallNorth.Rotate(0, 1, 0, 3.1415928F);

}

void CAppartments::TranslateAll() {

	m_zpWallNorth.TranslateDelta(CHVector(17.4 * fResize, 0 * fResize, 0 * fResize));
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallSouth.TranslateDelta(CHVector(0 * fResize, 0 * fResize, 2.9F * fResize));
	m_zpWallSouth.AddGeo(&m_zgWallSouth);
	m_zpWallWest.TranslateDelta(CHVector(0 * fResize, 0 * fResize, 0 * fResize));
	m_zpWallWest.AddGeo(&m_zgWallWest);
	m_zpWallEast.TranslateDelta(CHVector(+17.4F * fResize, 0 * fResize, +2.9F * fResize));
	m_zpWallEast.AddGeo(&m_zgWallEast);
	//m_zpGround.Translate(CHVector(0, 0, 0));
	//m_zpGround.AddGeo(&m_zgGround);
	m_zpRoof.Translate(CHVector(0 * fResize, 8.9F * fResize, 0 * fResize));
	m_zpRoof.AddGeo(&m_zgRoof);

}


NAMESPACE_VIEW_E
