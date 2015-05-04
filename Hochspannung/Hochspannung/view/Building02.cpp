#include "Building02.h"
#include "VMaterialLoader.h"
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

	m_zgWindow.InitRect(CFloatRect(0.2F, 0.9F, 0.2F, 0.1F), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	
	//m_zgWindowInlay.InitRect(CFloatRect(0.1F, 0.1F, 0.8F, 0.8F), false);
	//m_zgWindowInlay.InitRect(CFloatRect(0.1F, 0.1F, 0.8F, 0.8F), false);
	//m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);



}

void Building02::AddWindows(){

		m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 4, 5);
		//m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);
	}

	void Building02::InitWalls(){

		m_zgWallFrame.Init(1.F, 1.F, 0.5F, &VMaterialLoader::materialWindowsofBuilding);
		//m_zgWallGlass.Init(1.F, 1.F, 0.5F, &VMaterialLoader::materialWindowsofBuilding);
		m_zWallNorth.Init(5.F, 5.F, 0.1F, &VMaterialLoader::materialBuilding02);
		m_zgDach.Init(CHVector(2.6F, 0.1F, 2.6F, 0.F), &VMaterialLoader::materialBuilding02);
		

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

		m_zpWallNorth.Translate(0.F, 0.F, 5.9F);

		m_zpWallWest.RotateY(PI / 2.F);
		m_zpWallWest.TranslateDelta(4.9F, 0.F, 6.F);

		m_zpWallEast.RotateY(PI / 2.F);
		m_zpWallEast.TranslateDelta(0.F, 0.F, 6.F);


		m_zpWallSouth.RotateY(PI);
		m_zpWallSouth.TranslateDelta(5.F, 0.F, 1.1F);

		m_zpDach.Translate(2.5F, 5.F, 3.5F);
	}

NAMESPACE_VIEW_E