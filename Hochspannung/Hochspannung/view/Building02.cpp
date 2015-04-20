#include "Building02.h"

NAMESPACE_VIEW_B
Building02::Building02()
{
	
	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();


}


Building02::~Building02()
{
}

void Building02::InitWindows(){

	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.2, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	
	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);



}

void Building02::AddWindows(){

	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 4, 5);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);
}

void Building02::InitWalls(){

	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallNorth.Init(5, 5, 1, &m_zmWallNorth);
	m_zgDach.Init(CHVector(2.5, 1, 2.5, 0), &m_zmDach);


}
void Building02::AddPlacements(){


	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallWest);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallSouth);
	AddPlacement(&m_zpDach);



	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(&m_zWallNorth);
	m_zpWallEast.AddGeo(&m_zWallNorth);
	m_zpWallSouth.AddGeo(&m_zWallNorth);
	m_zpDach.AddGeo(&m_zgDach);

}

void Building02::TranslateAll(){

	m_zpWallNorth.Translate(0, 0, 60);

	m_zpWallWest.RotateY(PI / 2);
	m_zpWallWest.TranslateDelta(4.9, 0, 6);

	m_zpWallEast.RotateY(PI / 2);
	m_zpWallEast.TranslateDelta(0, 0, 6);


	m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(5, 0, 1.1);

	m_zpDach.Translate(2.5, 5, 3.5);
}

NAMESPACE_VIEW_E