#include "Appartments.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


CAppartments::CAppartments()
{
	this->fResize = 1.0F;
}


CAppartments::CAppartments(float fResize)
{
	this->fResize = fResize;
}

CAppartments::~CAppartments(void)
{
}

void CAppartments::init()
{
	if (fResize == 1)
	{
		InitWindows();
		AddWindows();
	}

	//Init Walls
	InitWalls();

	//Placements
	AddPlacements();

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

	//Resize for Lods
	ScaleForLod();
}

void CAppartments::InitWindows() {
	m_zgWindow.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 0.5F / fResize, 1.0F / fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);
}

void CAppartments::AddWindows() {

	m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5F / fResize, 1.0F / fResize, 17.0F / fResize, 8.0F / fResize), 12, 6);
	m_zgWallSouth.AddGeoWindows(&m_zgWindow, CFloatRect(0.5F / fResize, 1.0F / fResize, 17.0F / fResize, 8.0F / fResize), 12, 6);
	m_zgWallEast.AddGeoWindows(&m_zgWindow, CFloatRect(0.1F / fResize, 1.0F / fResize, 2.9F / fResize, 8.0F / fResize), 3, 6);
	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0.1F / fResize, 1.0F / fResize, 2.9F / fResize, 8.0F / fResize), 3, 6);
}

void CAppartments::InitWalls(){

	m_zgFrame.Init(1.0F, 1.0F, 0.1F, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_WINDOW, switchedState));

	m_zgWallNorth.Init(17.5F / fResize, 9.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallWest.Init(3.0F / fResize, 9.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallSouth.Init(17.5F / fResize, 9.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallEast.Init(3.0F / fResize, 9.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));

	m_zgRoof.Init(17.5F / fResize, 0.1F / fResize, 3.0F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	
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

	m_zpWallNorth.TranslateDelta(17.4F / fResize, 0.0F / fResize, 0.0F / fResize);
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallSouth.TranslateDelta(0.0F / fResize, 0.0F / fResize, 2.9F / fResize);
	m_zpWallSouth.AddGeo(&m_zgWallSouth);
	m_zpWallWest.TranslateDelta(0.0F / fResize, 0.0F / fResize, 0.0F / fResize);
	m_zpWallWest.AddGeo(&m_zgWallWest);
	m_zpWallEast.TranslateDelta(17.4F / fResize, 0.0F / fResize, 2.9F / fResize);
	m_zpWallEast.AddGeo(&m_zgWallEast);
	m_zpRoof.Translate(0.0F / fResize, 8.9F / fResize, 0.0F / fResize);
	m_zpRoof.AddGeo(&m_zgRoof);

}

void CAppartments::ScaleForLod(){

	Scale(fResize);
}


NAMESPACE_VIEW_E
