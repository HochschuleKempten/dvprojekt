
#include "OfficeTowerViewingDeck.h"

NAMESPACE_VIEW_B
COfficeTowerViewingDeck::COfficeTowerViewingDeck()
{

	this->fResize = 1.0F;

	InitWindows();

	//Add Windows
	AddWindows();

	//Walls
	InitWalls();

	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	AddPlacements();

	TranslateAll();

	//Resize for Lods
	ScaleForLod();
}


COfficeTowerViewingDeck::COfficeTowerViewingDeck(float fResize)
{

	this->fResize = fResize;
	
	InitWindows();

	//Add Windows
	AddWindows();

	//Walls
	InitWalls();

	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	AddPlacements();

	TranslateAll();

	//Resize for Lods
	ScaleForLod();
}

COfficeTowerViewingDeck::~COfficeTowerViewingDeck(void)
{
	
}



void COfficeTowerViewingDeck::TranslateAll() {
	m_zpWall.TranslateDelta(0.0F / fResize, 0.0F / fResize, 0.F / fResize);
	m_zpWall.AddGeo(&m_zgWall);

	m_zpWallTop.TranslateDelta(0.0F / fResize, 30.0F / fResize, 0.0F / fResize);
	m_zpWallTop.AddGeo(&m_zgWallTop);

	m_zpRoof.Translate(0, 30 / fResize, 0);
	m_zpRoof.AddGeo(&m_zgRoof);
	m_zpRoofTop.Translate(0, 32 / fResize, 0);
	m_zpRoofTop.AddGeo(&m_zgRoofTop);
}

void COfficeTowerViewingDeck::AddPlacements() {

	AddPlacement(&m_zpWall);
	AddPlacement(&m_zpWallTop);
	AddPlacement(&m_zpRoof);
	AddPlacement(&m_zpRoofTop);

}

void COfficeTowerViewingDeck::InitWindows() {

	m_zgWindow.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 0.5F / fResize, 1.0F / fResize), true);
	m_zgRailing.InitRect(CFloatRect(0.0F / fResize, 0.0F / fResize, 0.95F / fResize, 0.7F / fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void COfficeTowerViewingDeck::AddWindows() {

	m_zgWall.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 1.0F / fResize, 20.0F / fResize, 28.0F / fResize), 25, 25);
	m_zgWall.AddGeoWindows(&m_zgRailing, CFloatRect(0.0F / fResize, 30.0F / fResize, 20.0F / fResize, 0.7F / fResize), 20, 1);
	m_zgWallTop.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 0.5F / fResize, 12.5F / fResize, 1.0F / fResize), 15, 1);

}

void COfficeTowerViewingDeck::InitWalls() {
	m_zgFrame.Init(1.0F, 1.0F, .25F, &VMaterialLoader::materialWindowsofBuilding);

	m_zgWall.InitTube(3.183F / fResize, 30.75F / fResize, .1F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);
	m_zgWallTop.InitTube(1.989F / fResize, 2.0F / fResize, .1F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);

	m_zgRoof.InitDomeCone(3.2F / fResize, 0.0F / fResize, 0.05F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);
	m_zgRoofTop.InitDomeCone(2.0F / fResize, 0.0F / fResize, 0.05F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);

}

void COfficeTowerViewingDeck::ScaleForLod(){

	this->Scale(fResize);

}

NAMESPACE_VIEW_E