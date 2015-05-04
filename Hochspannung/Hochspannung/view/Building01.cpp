#include "Building01.h"

NAMESPACE_VIEW_B
Building01::Building01()
{
	
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
	m_zWallLod1.AddGeoWindows(&m_zWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 7, 7);
	m_zWallLod2.AddGeoWindows(&m_zWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 7, 7);
	m_zWallLod3.AddGeoWindows(&m_zWindow, CFloatRect(0.F, 0.1F, 1.F, 0.8F), 7, 7);
	
}

void Building01::InitWalls(){

	//StandardSizeofBuildingLod1
	m_zWallLod1.InitTube(3.5F, 10.F, 0.2F, &VMaterialLoader::materialBuilding01,1.0);
	m_zWallKuppelLod1.InitDome(3.5F,0.2F, &VMaterialLoader::materialBuilding01,1.0);

	/*//InitLod2
	m_zWallLod2.InitTube(1.75F, 5.F, 0.1F, &VMaterialLoader::materialBuilding01, 1.0);
	m_zWallKuppelLod2.InitDome(1.75F, 0.1F, &VMaterialLoader::materialBuilding01, 1.0);



	//InitLod3
	m_zWallLod3.InitTube(0.875F, 2.5F, 0.05F, &VMaterialLoader::materialBuilding01, 1.0);
	m_zWallKuppelLod3.InitDome(0.875F, 0.05F, &VMaterialLoader::materialBuilding01, 1.0);
	*/

	//for testing lods
	m_zWallLod2.InitTube(1.75F, 5.F, 0.1F,&test1, 1.0);
	m_zWallKuppelLod2.InitDome(1.75F, 0.1F, &test1 , 1.0);

	m_zWallLod3.InitTube(0.875F, 2.5F, 0.05F, &test2, 1.0);
	m_zWallKuppelLod3.InitDome(0.875F, 0.05F, &test2, 1.0);

	test1.MakeTextureDiffuse("textures\\red_image.jpg");
	test2.MakeTextureDiffuse("textures\\green_image.jpg");
}
void Building01::AddPlacements(){

	
	//WalladdplacWalllods
	m_zpWall.AddPlacement(&m_zpWallLod1);
	m_zpWall.AddPlacement(&m_zpWallLod2);
	m_zpWall.AddPlacement(&m_zpWallLod3);

	//WallKuppeladdplacWallKuppellods
	m_zpWallKuppel.AddPlacement(&m_zpWallKuppelLod1);
	m_zpWallKuppel.AddPlacement(&m_zpWallKuppelLod2);
	m_zpWallKuppel.AddPlacement(&m_zpWallKuppelLod3);

	//WallLodaddgeo
	m_zpWallLod1.AddGeo(&m_zWallLod1);
	m_zpWallLod2.AddGeo(&m_zWallLod2);
	m_zpWallLod3.AddGeo(&m_zWallLod3);
	
	//WallKuppelLodaddgeo
	m_zpWallKuppelLod1.AddGeo(&m_zWallKuppelLod1);
	m_zpWallKuppelLod2.AddGeo(&m_zWallKuppelLod2);
	m_zpWallKuppelLod3.AddGeo(&m_zWallKuppelLod3);

	//

	m_zpWall.AddPlacement(&m_zpWallKuppel);


	AddPlacement(&m_zpWall);
	AddPlacement(&m_zpWallKuppel);
	


}

void Building01::TranslateAll(){

	m_zpWall.Translate(0.F, 0.F, 0.F);
	m_zpWallKuppel.Translate(0.F, 10.F, 0.F);
}

void Building01::scaleforLoDs(){

	m_zpWallLod1.SetLoD(0, 10);
	m_zpWallLod2.SetLoD(10, 30);
	m_zpWallLod3.SetLoD(30, 100);

	m_zpWallLod1.Scale(1);
	m_zpWallLod2.Scale(2);
	m_zpWallLod3.Scale(4);

	m_zpWallLod1.TranslateXDelta(0);
	m_zpWallLod2.TranslateXDelta(5);
	m_zpWallLod3.TranslateXDelta(10);
	


}

NAMESPACE_VIEW_E