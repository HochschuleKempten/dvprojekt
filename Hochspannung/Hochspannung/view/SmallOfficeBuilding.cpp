
#include "SmallOfficeBuilding.h"

NAMESPACE_VIEW_B


CSmallOfficeBuilding::CSmallOfficeBuilding(float fResize)
{

	
	this->fResize = fResize;


	InitWindows();

	AddWindows();

	InitWalls();


	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	//Placements
	AddPlacements();
	

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CSmallOfficeBuilding::~CSmallOfficeBuilding(void)
{
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


}

void CSmallOfficeBuilding::AddPlacements() {
	
	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallWest);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallSouth);
	AddPlacement(&m_zpRoof);
	AddPlacement(&m_zpDoor);

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
	m_zpRoof.Translate(CHVector(0 * fResize, 7.9 * fResize, 0 * fResize));
	m_zpRoof.AddGeo(&m_zgRoof);

}

NAMESPACE_VIEW_E