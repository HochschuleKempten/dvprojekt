#include "Building03.h"
#include "VMaterialLoader.h"
NAMESPACE_VIEW_B

Building03::Building03()
{
	
	fresize = 1;
	
	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();
}
Building03::Building03(float fResize)
{

	fresize = fResize;

	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();
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

	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 14, 3);
	//m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);
}

	void Building03::InitWalls(){

		m_zWallNorth.Init(fstandardwidthwall / fresize, fstandardheightwall / fresize, fstandarddepthwall / fresize, &VMaterialLoader::materialBuilding03);
		m_zgDach.Init(CHVector(fstandardwidthroof / fresize, fstandardheightroof / fresize, fstandarddepthroof / fresize, 0.F), &VMaterialLoader::materialBuilding03);

	}
	void Building03::AddPlacements(){

		m_zpbuilding03.AddPlacement(&m_zpWallNorth);
		m_zpbuilding03.AddPlacement(&m_zpWallWest);
		m_zpbuilding03.AddPlacement(&m_zpWallEast);
		m_zpbuilding03.AddPlacement(&m_zpWallSouth);
		m_zpbuilding03.AddPlacement(&m_zpDach);

		AddPlacement(&m_zpbuilding03);

		m_zpWallNorth.AddGeo(&m_zWallNorth);
		m_zpWallWest.AddGeo(&m_zWallNorth);
		m_zpWallEast.AddGeo(&m_zWallNorth);
		m_zpWallSouth.AddGeo(&m_zWallNorth);
		m_zpDach.AddGeo(&m_zgDach);

	}

	void Building03::TranslateAll(){

		m_zpWallNorth.Translate(0.F, 0.F, 0.F);

		m_zpWallWest.RotateY(PI / 2.F);
		m_zpWallWest.TranslateDelta((fstandardwidthwall / fresize), 0.F, 0.F);

		m_zpWallEast.RotateY(PI / 2.F);
		//m_zpWallEast.Translate((fstandardwidthwall / fresize) / -2, (fstandardwidthwall / fresize) / -2, 0.F);
		//m_zpWallSouth.RotateY(PI);
		m_zpWallSouth.TranslateDelta(0.F, 0.F, fstandardwidthwall / -fresize);

		m_zpDach.Translate((fstandardwidthwall / fresize) / 2, fstandardheightwall / fresize, (fstandardwidthwall / -fresize) / 2);
	}


	void Building03::scaleforLoDs(){

		m_zpbuilding03.Scale(fresize);

	}

NAMESPACE_VIEW_E