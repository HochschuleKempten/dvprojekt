
#include "TwistedTower.h"

NAMESPACE_VIEW_B

CTwistedTower::CTwistedTower(void)
{

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


	//Placements
	AddPlacements();

	
	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CTwistedTower::~CTwistedTower(void)
{

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

	
	m_zgRoof.Init(3.0F, 0.1F, 2.598F, &m_zm);

	m_zgWallNorth.Init(3.0F, 5.0F, 0.2F, &m_zm);
	m_zgWallEast.Init(3.0F, 5.0F, 0.2F, &m_zm);
	m_zgWallWest.Init(3.0F, 5.0F, 0.2F, &m_zm);

}

void CTwistedTower::AddPlacements() {


	AddPlacement(&m_zpRoof);

	

	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallWest);

}

void CTwistedTower::RotateAll(){

	m_zpWallNorth.Rotate(0, 1, 0, 0);
	m_zpWallEast.Rotate(0, 1, 0, -2.0943951F);
	m_zpWallWest.Rotate(0, 1, 0, +2.0943951F);

}

void CTwistedTower::TranslateAll() {


	m_zpRoof.Translate(0.0F, 0.0F, 0.0F);
	m_zpRoof.AddGeo(&m_zgRoof);

	m_zpWallNorth.TranslateDelta(0, 0, 0);
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallEast.TranslateDelta(1.6F, 0, -2.598F);
	m_zpWallEast.AddGeo(&m_zgWallEast);
	m_zpWallWest.TranslateDelta(2.8F, 0, 0.2F);
	m_zpWallWest.AddGeo(&m_zgWallWest);

}

NAMESPACE_VIEW_E