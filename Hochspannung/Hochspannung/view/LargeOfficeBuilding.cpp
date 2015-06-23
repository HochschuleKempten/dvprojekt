#include "LargeOfficeBuilding.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


CLargeOfficeBuilding::CLargeOfficeBuilding(float fResize)
{
	this->fResize = fResize;
}

CLargeOfficeBuilding::~CLargeOfficeBuilding(void)
{}

void CLargeOfficeBuilding::init()
{
	if (fResize == 1)
	{
		InitWindows();
		AddWindows();
	}

	//Walls
	InitWalls();

	AddPlacements();

	//Rotations
	RotateAll();

	//Translations
	TranslateAll();

	//Resize for Lods
	scaleForLod();
}

void CLargeOfficeBuilding::InitWindows() {

	m_zgDoor.InitRect(CFloatRect(0.0F / fResize, 0.0F / fResize, 1.25F / fResize, 1.75F / fResize), true);
	m_zgDoor.AddGeoWall(&m_zgFrame);

	m_zgWindow.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 0.5F / fResize, 1.0F / fResize), true);
	m_zgWindow.AddGeoWall(&m_zgFrame);
	m_zgWindowHigh.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 0.5F / fResize, 2.0F / fResize), true);
	m_zgWindowHigh.AddGeoWall(&m_zgFrame);
	m_zgWindowWide.InitRect(CFloatRect(1.0F / fResize, 1.0F / fResize, 2.0F / fResize, 0.75F / fResize), true);
	m_zgWindowWide.AddGeoWall(&m_zgFrame);

}

void CLargeOfficeBuilding::AddWindows() {

	m_zgWallSouth0.AddGeoWindows(&m_zgDoor, CFloatRect(1 / fResize, 0 / fResize, 1 / fResize, 1 / fResize), 1, 1);

	m_zgWallNorth0.AddGeoWindows(&m_zgWindow, CFloatRect(0 / fResize, 2 / fResize, 3 / fResize, 6 / fResize), 4, 5);
	m_zgWallNorth1.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 / fResize, 1 / fResize, 1 / fResize, 5 / fResize), 1, 2);
	m_zgWallNorth2.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 / fResize, 1 / fResize, 1 / fResize, 2.5F / fResize), 1, 1);

	m_zgWallSouth0.AddGeoWindows(&m_zgWindow, CFloatRect(0 / fResize, 2 / fResize, 3 / fResize, 6 / fResize), 4, 5);
	m_zgWallSouth1.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 / fResize, 1 / fResize, 1 / fResize, 5 / fResize), 1, 2);
	m_zgWallSouth2.AddGeoWindows(&m_zgWindowHigh, CFloatRect(0 / fResize, 1 / fResize, 1 / fResize, 2.5F / fResize), 1, 1);

	m_zgWallEast0.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 / fResize, 0 / fResize, 5 / fResize, 2 / fResize), 2, 2);
	m_zgWallEast1.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 / fResize, 0 / fResize, 5 / fResize, 2 / fResize), 2, 2);
	m_zgWallEast2.AddGeoWindows(&m_zgWindowWide, CFloatRect(0 / fResize, 1 / fResize, 5 / fResize, 3 / fResize), 2, 3);

	m_zgWallWest.AddGeoWindows(&m_zgWindow, CFloatRect(0, 2, 5, 6), 8, 5);

}

void CLargeOfficeBuilding::InitWalls() {
	
	m_zgFrame.Init(1.0F, 1.0F, .25F, &VMaterialLoader::materialWindowsofBuilding);

	m_zgWallNorth0.Init(3.1F / fResize, 8.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallNorth1.Init(1.1F / fResize, 6.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallNorth2.Init(1.1F / fResize, 4.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));

	m_zgWallWest.Init(5.0F / fResize, 8.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));

	m_zgWallSouth0.Init(3.1F / fResize, 8.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallSouth1.Init(1.1F / fResize, 6.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallSouth2.Init(1.1F / fResize, 4.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));

	m_zgWallEast0.Init(5.0F / fResize, 2.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallEast1.Init(5.0F / fResize, 2.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgWallEast2.Init(5.0F / fResize, 4.0F / fResize, .1F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));

	m_zgRoof0.Init(3.0F / fResize, 0.1F / fResize, 5.0F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgRoof1.Init(1.0F / fResize, 0.1F / fResize, 5.0F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
	m_zgRoof2.Init(1.0F / fResize, 0.1F / fResize, 5.0F / fResize, VMaterialLoader::getMaterialModel(VMaterialLoader::BUILDING_BROWN_WALL, switchedState));
}

void CLargeOfficeBuilding::AddPlacements() {

	AddPlacement(&m_zpWallNorth0);
	AddPlacement(&m_zpWallNorth1);
	AddPlacement(&m_zpWallNorth2);

	AddPlacement(&m_zpWallWest);

	AddPlacement(&m_zpWallEast0);
	AddPlacement(&m_zpWallEast1);
	AddPlacement(&m_zpWallEast2);

	AddPlacement(&m_zpWallSouth0);
	AddPlacement(&m_zpWallSouth1);
	AddPlacement(&m_zpWallSouth2);

	AddPlacement(&m_zpRoof0);
	AddPlacement(&m_zpRoof1);
	AddPlacement(&m_zpRoof2);

	AddPlacement(&m_zpDoor);

}

void CLargeOfficeBuilding::RotateAll() {

	m_zpWallEast0.Rotate(0, 1, 0, +1.570796326F);
	m_zpWallEast1.Rotate(0, 1, 0, +1.570796326F);
	m_zpWallEast2.Rotate(0, 1, 0, +1.570796326F);

	m_zpWallWest.Rotate(0, 1, 0, -1.570796326F);

	m_zpWallNorth0.Rotate(0, 1, 0, 3.141592652F);
	m_zpWallNorth1.Rotate(0, 1, 0, 3.141592652F);
	m_zpWallNorth2.Rotate(0, 1, 0, 3.141592652F);

}

void CLargeOfficeBuilding::TranslateAll() {

	m_zpWallNorth0.TranslateDelta(3.0F / fResize, 0.0F / fResize, -4.9F / fResize);
	m_zpWallNorth0.AddGeo(&m_zgWallNorth0);
	m_zpWallNorth1.TranslateDelta(4.0F / fResize, 0.0F / fResize, -4.9F / fResize);
	m_zpWallNorth1.AddGeo(&m_zgWallNorth1);
	m_zpWallNorth2.TranslateDelta(5.0F / fResize, 0.0F / fResize, -4.9F / fResize);
	m_zpWallNorth2.AddGeo(&m_zgWallNorth2);

	m_zpWallSouth0.TranslateDelta(0.0F / fResize, 0.0F / fResize, -0.1F / fResize);
	m_zpWallSouth0.AddGeo(&m_zgWallSouth0);
	m_zpWallSouth1.TranslateDelta(3.0F / fResize, 0.0F / fResize, -0.1F / fResize);
	m_zpWallSouth1.AddGeo(&m_zgWallSouth1);
	m_zpWallSouth2.TranslateDelta(4.0F / fResize, 0.0F / fResize, -0.1F / fResize);
	m_zpWallSouth2.AddGeo(&m_zgWallSouth2);

	m_zpWallWest.TranslateDelta(0.0F / fResize, 0.0F / fResize, -5.0F / fResize);
	m_zpWallWest.AddGeo(&m_zgWallWest);

	m_zpWallEast0.TranslateDelta(3.0F / fResize, 6.0F / fResize, 0.0F / fResize);
	m_zpWallEast0.AddGeo(&m_zgWallEast0);
	m_zpWallEast1.TranslateDelta(4.0F / fResize, 4.0F / fResize, 0.0F / fResize);
	m_zpWallEast1.AddGeo(&m_zgWallEast1);
	m_zpWallEast2.TranslateDelta(5.0F / fResize, 0.0F / fResize, 0.0F / fResize);
	m_zpWallEast2.AddGeo(&m_zgWallEast2);



	m_zpRoof0.Translate(0.0F / fResize, 7.9F / fResize, -5.0F / fResize);
	m_zpRoof0.AddGeo(&m_zgRoof0);
	m_zpRoof1.Translate(3.0F / fResize, 5.9F / fResize, -5.0F / fResize);
	m_zpRoof1.AddGeo(&m_zgRoof1);
	m_zpRoof2.Translate(4.0F / fResize, 3.9F / fResize, -5.0F / fResize);
	m_zpRoof2.AddGeo(&m_zgRoof2);

}


void CLargeOfficeBuilding::scaleForLod(){

	this->Scale(fResize);

}


NAMESPACE_VIEW_E