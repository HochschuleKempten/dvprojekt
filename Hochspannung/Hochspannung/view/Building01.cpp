#include "Building01.h"

NAMESPACE_VIEW_B
Building01::Building01()
{
	
	fresize = 1;
	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();
	
}

Building01::Building01(float fResize)
{
	fresize = fResize;

	InitWindows();
	AddWindows();
	InitWalls();
	AddPlacements();
	TranslateAll();
	scaleforLoDs();

}


Building01::~Building01()
{
}

void Building01::InitWindows(){

	//m_zWallGlass.Init(1.F, 1.F, 0.5F, &m_zmWallGlass);
	//m_zWindowInlay.InitRect(CFloatRect(0.1F, 0.1F, 0.8F, 0.8F), false);
	//m_zWindowInlay.AddGeoWall(&m_zWallGlass);
	
	m_zWallFrame.Init(1.F, 1.F, 0.5F, &VMaterialLoader::materialWindowsofBuilding);
	m_zWindow.InitRect(CFloatRect(0.2F, 0.9F, 0.1F, 0.4F), false);
	m_zWindow.AddGeoWall(&m_zWallFrame);
}

void Building01::AddWindows(){

	
	//m_zWallFrame.AddGeoWindow(&m_zWindowInlay);
	m_zWall.AddGeoWindows(&m_zWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 7, 7);
	
	
}

void Building01::InitWalls(){

	//StandardSizeofBuildingLod1
	m_zWall.InitTube(fstandardradius/fresize, fstandardheight/fresize, fstandardthickness/fresize, &VMaterialLoader::materialBuilding01,1.0);
	m_zWallKuppel.InitDome(fstandardradius / fresize, fstandardthickness / fresize, &VMaterialLoader::materialBuilding01, 1.0);

}
void Building01::AddPlacements(){


	m_zpWall.AddGeo(&m_zWall);
	m_zpWallKuppel.AddGeo(&m_zWallKuppel);
	m_zpbuilding01.AddPlacement(&m_zpWall);
	m_zpbuilding01.AddPlacement(&m_zpWallKuppel);
	AddPlacement(&m_zpbuilding01);

}

void Building01::TranslateAll(){

	m_zpWall.Translate(0.F, 0.F, 0.F);
	m_zpWallKuppel.Translate(0.F, fstandardheight / fresize, 0.F);
}

void Building01::scaleforLoDs(){

	m_zpbuilding01.Scale(fresize);

}

NAMESPACE_VIEW_E