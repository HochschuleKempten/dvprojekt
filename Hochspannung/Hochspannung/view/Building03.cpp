#include "Building03.h"
NAMESPACE_VIEW_B

Building03::Building03()
{
	
	
	
	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	
}


Building03::~Building03()
{
}

void Building03::InitWindows(){

	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.1, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);

	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);
	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	


}

void Building03::AddWindows(){

	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 7, 3);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);
}

	void Building03::InitWalls(){

		m_zWallNorth.Init(5.1, 1, 1, &m_zmWallNorth);
		m_zgDach.Init(CHVector(3.5, 0.1, 2.55, 0), &m_zmDach);

	}
	void Building03::AddPlacements(){

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

	void Building03::TranslateAll(){

		m_zpWallNorth.Translate(1, 0, 8);


		m_zpWallWest.RotateY(PI / 2);
		m_zpWallWest.TranslateDelta(0, 0,9);

		m_zpWallEast.RotateY(PI / 2);
		m_zpWallEast.TranslateDelta(6, 0, 9);



		m_zpWallSouth.RotateY(PI);
		m_zpWallSouth.TranslateDelta(6, 0, 4.9);

		m_zpDach.Translate(3.5, 1, 6.45);
	}

NAMESPACE_VIEW_E