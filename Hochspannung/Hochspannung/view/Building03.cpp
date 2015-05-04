#include "Building03.h"
#include "VMaterialLoader.h"
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

	m_zgWindow.InitRect(CFloatRect(0.2F, 0.9F, 0.1F, 0.1F), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	//m_zgWindowInlay.InitRect(CFloatRect(0.1F, 0.1F, 0.8F, 0.8F), false);
	//m_zgWindowInlay.InitRect(CFloatRect(0.1F, 0.1F, 0.8F, 0.8F), false);

	//m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);
	m_zgWallFrame.Init(1.F, 1.F, 0.5F, &VMaterialLoader::materialWindowsofBuilding);
	//m_zgWallGlass.Init(1.F, 1.F, 0.5F, &m_zmWallGlass);
	


}

void Building03::AddWindows(){

	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 7, 3);
	//m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);
}

	void Building03::InitWalls(){

		m_zWallNorth.Init(5.1F, 1.F, 1.F, &VMaterialLoader::materialBuilding03);
		m_zgDach.Init(CHVector(3.5F, 0.1F, 2.55F, 0.F), &VMaterialLoader::materialBuilding03);

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

		m_zpWallNorth.Translate(1.F, 0.F, 8.F);


		m_zpWallWest.RotateY(PI / 2.F);
		m_zpWallWest.TranslateDelta(0.F, 0.F,9.F);

		m_zpWallEast.RotateY(PI / 2.F);
		m_zpWallEast.TranslateDelta(6.F, 0.F, 9.F);



		m_zpWallSouth.RotateY(PI);
		m_zpWallSouth.TranslateDelta(6.F, 0.F, 4.9F);

		m_zpDach.Translate(3.5F, 1.F, 6.45F);
	}

NAMESPACE_VIEW_E