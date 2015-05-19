
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
	
	if (fResize == 1){
		void InitWindows();
		void AddWindows();
	}

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

	m_zpWallTop.TranslateDelta(0.0F / fResize, 24.0F / fResize, 0.0F / fResize);
	m_zpWallTop.AddGeo(&m_zgWallTop);

	m_zpRoof.Translate(0, 24.0F / fResize, 0);
	m_zpRoof.AddGeo(&m_zgRoof);
	m_zpRoofTop.Translate(0, 25.6F / fResize, 0);
	m_zpRoofTop.AddGeo(&m_zgRoofTop);
}

void COfficeTowerViewingDeck::AddPlacements() {

	AddPlacement(&m_zpWall);
	AddPlacement(&m_zpWallTop);
	AddPlacement(&m_zpRoof);
	AddPlacement(&m_zpRoofTop);

}

void COfficeTowerViewingDeck::InitWindows() {

	m_zgWindow.InitRect(CFloatRect(0.8F / fResize, 0.8F / fResize, 0.4F / fResize, 0.8F / fResize), true);
	m_zgRailing.InitRect(CFloatRect(0.0F / fResize, 0.0F / fResize, 0.76F / fResize, 0.56 / fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void COfficeTowerViewingDeck::AddWindows() {

	m_zgWall.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 0.8F / fResize, 16.0F / fResize, 22.4F / fResize), 25, 25);
	m_zgWall.AddGeoWindows(&m_zgRailing, CFloatRect(0.0F / fResize, 24.0F / fResize, 16.0F / fResize, 0.56F / fResize), 20, 1);
	m_zgWallTop.AddGeoWindows(&m_zgWindow, CFloatRect(0.0F / fResize, 0.4F / fResize, 10.0F / fResize, 0.8F / fResize), 15, 1);

}

void COfficeTowerViewingDeck::InitWalls() {
	m_zgFrame.Init(1.0F, 1.0F, .25F, &VMaterialLoader::materialWindowsofBuilding);

	m_zgWall.InitTube(2.5654 / fResize, 24.6F / fResize, 0.08F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);
	m_zgWallTop.InitTube(1.5912F / fResize, 1.6F / fResize, 0.08F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);

	m_zgRoof.InitDomeCone(2.56F / fResize, 0.0F / fResize, 0.04F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);
	m_zgRoofTop.InitDomeCone(1.6F / fResize, 0.0F / fResize, 0.04F / fResize, &VMaterialLoader::materialOfficTowerViewingDeck);

}

void COfficeTowerViewingDeck::ScaleForLod(){

	this->Scale(fResize);

}

NAMESPACE_VIEW_E