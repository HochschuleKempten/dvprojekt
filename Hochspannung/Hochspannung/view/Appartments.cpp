
#include "Appartments.h"

NAMESPACE_VIEW_B
CAppartments::CAppartments(float fResize)
{
	
	this->fResize = fResize;


	//Initialize Windows
	InitWindows();


	//Add Windows
	AddWindows();



	//Init Walls
	InitWalls();



	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	//Placements
	AddPlacements();
	
	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

}

CAppartments::~CAppartments(void)
{
}

//todo Dach Round


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
	
}

void CAppartments::AddPlacements() {

	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallWest);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallSouth);
	AddPlacement(&m_zpRoof);



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
	m_zpRoof.Translate(CHVector(0 * fResize, 8.9F * fResize, 0 * fResize));
	m_zpRoof.AddGeo(&m_zgRoof);

}


NAMESPACE_VIEW_E