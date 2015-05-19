
#include "SmallOfficeBuilding.h"

NAMESPACE_VIEW_B
CSmallOfficeBuilding::CSmallOfficeBuilding()
{


	this->fResize = 1.0F;


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

	//Resize for Lods
	ScaleForLod();
}

CSmallOfficeBuilding::CSmallOfficeBuilding(float fResize)
{

	
	this->fResize = fResize;


	if (fResize == 1){
		void InitWindows();
		void AddWindows();
	}

	InitWalls();


	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	//Placements
	AddPlacements();
	

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

	//Resize for Lods
	ScaleForLod();

}

CSmallOfficeBuilding::~CSmallOfficeBuilding(void)
{
}



void CSmallOfficeBuilding::InitWindows() {

	m_zgDoor.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 1.0F / fResize, 1.0F / fResize), true);
	m_zgWindow.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 0.5F / fResize, 1.0F / fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void CSmallOfficeBuilding::AddWindows() {

	m_zgWallSouth.AddGeoWindows(&m_zgDoor, CFloatRect(1.0F / fResize, 0.5F / fResize, 1.0F / fResize, 1.0F / fResize), 1, 4);

	m_zgWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 2.0F / fResize, 3.0F / fResize, 6.0F / fResize), 4, 5);
	m_zgWallSouth.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 2.0F / fResize, 3.0F / fResize, 6.0F / fResize), 4, 5);
	m_zgWallEast.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 2.0F / fResize, 3.0F / fResize, 6.0F / fResize), 4, 5);
	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 2.0F / fResize, 3.0F / fResize, 6.0F / fResize), 4, 5);

}

void CSmallOfficeBuilding::InitWalls() {

	m_zgFrame.Init(1.0F, 1.0F, .25F, &VMaterialLoader::materialWindowsofBuilding);
	m_zgWallNorth.Init(3.0F / fResize, 8.0F / fResize, .1F / fResize, &VMaterialLoader::materialSmallOfficeBuilding);
	m_zgWallWest.Init(3.0F / fResize, 8.0F / fResize, .1F / fResize, &VMaterialLoader::materialSmallOfficeBuilding);
	m_zgWallSouth.Init(3.0F / fResize, 8.0F / fResize, .1F / fResize, &VMaterialLoader::materialSmallOfficeBuilding);
	m_zgWallEast.Init(3.0F / fResize, 8.0F / fResize, .1F / fResize, &VMaterialLoader::materialSmallOfficeBuilding);

	m_zgRoof.Init(3.0F / fResize, 0.1F / fResize, 3.0F / fResize, &VMaterialLoader::materialSmallOfficeBuilding);


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

	m_zpWallNorth.TranslateDelta(3.0F / fResize, 0.0F / fResize, 0.1F / fResize);
	m_zpWallNorth.AddGeo(&m_zgWallNorth);
	m_zpWallSouth.TranslateDelta(0.0F / fResize, 0.0F / fResize, 2.9F / fResize);
	m_zpWallSouth.AddGeo(&m_zgWallSouth);
	m_zpWallWest.TranslateDelta(0.0F / fResize, 0.0F / fResize, 0.0F / fResize);
	m_zpWallWest.AddGeo(&m_zgWallWest);
	m_zpWallEast.TranslateDelta(3.0F / fResize, 0.0F / fResize, 3.0F / fResize);
	m_zpWallEast.AddGeo(&m_zgWallEast);
	m_zpRoof.Translate(0.0F / fResize, 7.9F / fResize, 0.0F / fResize);
	m_zpRoof.AddGeo(&m_zgRoof);

}

void CSmallOfficeBuilding::ScaleForLod(){

	this->Scale(fResize);

}

NAMESPACE_VIEW_E