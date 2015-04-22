
#include "OfficeTowerViewingDeck.h"

NAMESPACE_VIEW_B

COfficeTowerViewingDeck::COfficeTowerViewingDeck(float fResize)
{

	this->fResize = fResize;
	
	InitWindows();

	//Add Windows
	AddWindows();

	//Roundings
//	Round();

	//Walls
	InitWalls();

	m_zm.MakeTextureDiffuse("textures\\white_image.jpg");


	AddPlacements();

	TranslateAll();

}

COfficeTowerViewingDeck::~COfficeTowerViewingDeck(void)
{
	
}



void COfficeTowerViewingDeck::TranslateAll() {
	m_zpWall.TranslateDelta(CHVector(0.0F * fResize, 0.0F * fResize, 0.F * fResize));
	m_zpWall.AddGeo(&m_zgWall);

	m_zpWallTop.TranslateDelta(CHVector(0.0F * fResize, 30.0F * fResize, 0.0F * fResize));
	m_zpWallTop.AddGeo(&m_zgWallTop);

	//m_zpGround.Translate(CHVector(-20, 0, -20));
	//m_zpGround.AddGeo(&m_zgGround);
	m_zpRoof.Translate(CHVector(0, 30 * fResize, 0));
	m_zpRoof.AddGeo(&m_zgRoof);
	m_zpRoofTop.Translate(CHVector(0, 32 * fResize, 0));
	m_zpRoofTop.AddGeo(&m_zgRoofTop);
}

void COfficeTowerViewingDeck::AddPlacements() {

	AddPlacement(&m_zpWall);
	AddPlacement(&m_zpWallTop);
	AddPlacement(&m_zpRoof);
	AddPlacement(&m_zpRoofTop);

}

void COfficeTowerViewingDeck::InitWindows() {

	m_zgWindow.InitRect(CFloatRect(1 * fResize, 1 * fResize, 0.5 * fResize, 1 * fResize), true);
	m_zgRailing.InitRect(CFloatRect(0 * fResize, 0 * fResize, 0.95 * fResize, 0.7 * fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);

}

void COfficeTowerViewingDeck::AddWindows() {

	m_zgWall.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 1 * fResize, 20 * fResize, 28 * fResize), 25, 25);
	m_zgWall.AddGeoWindows(&m_zgRailing, CFloatRect(0 * fResize, 30 * fResize, 20 * fResize, 0.7 * fResize), 20, 1);
	m_zgWallTop.AddGeoWindows(&m_zgWindow, CFloatRect(0 * fResize, 0.5F * fResize, 12.5 * fResize, 1 * fResize), 15, 1);

}

void COfficeTowerViewingDeck::InitWalls() {
	m_zgFrame.Init(1.0F, 1.0F, .25F, &m_zm);

	m_zgWall.InitTube(3.183F * fResize, 30.75F * fResize, .1F * fResize, &m_zm);
	m_zgWallTop.InitTube(1.989F * fResize, 2.0F * fResize, .1F * fResize, &m_zm);

	m_zgRoof.InitDomeCone(3.2F * fResize, 0.0F * fResize, 0.05 * fResize, &m_zm);
	m_zgRoofTop.InitDomeCone(2.0F * fResize, 0.0F * fResize, 0.05 * fResize, &m_zm);

}

//void COfficeTowerViewingDeck::Round() {
//
//	m_zgWall.SetRoundingX(-2 * PI, 0.05F * fResize);
//	m_zgWallTop.SetRoundingX(-2 * PI, 0.05F * fResize);
//
//}

NAMESPACE_VIEW_E