#include "Building01.h"

NAMESPACE_VIEW_B
Building01::Building01()
{
	
	AddPlacement(&m_zpWall);
	AddPlacement(&m_zpWallKuppel);
	
	m_zpWall.AddPlacement(&m_zpWallKuppel);


	//PlacementsGeo
	m_zpWall.AddGeo(&m_zWall);
	m_zpWallKuppel.AddGeo(&m_zWallKuppel);
	
	



	//Walls&Windows
	m_zWindow.InitRect(CFloatRect(0.2, 0.9, 0.1, 0.4), false);
	m_zWindow.AddGeoWall(&m_zWallFrame);

	m_zWindowInlay.AddGeoWall(&m_zWallGlass);
	m_zWall.AddGeoWindows(&m_zWindow, CFloatRect(0, 0.1, 1, 0.8), 7, 7);

	m_zWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zWallFrame.AddGeoWindow(&m_zWindowInlay);

	m_zWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);



	//GeoKörper
	m_zWall.InitTube(2.5, 8, 0.2, &m_zmWall);
	m_zWallKuppel.InitDome(2.5, 0.2, &m_zmWallKuppel);



	//Ops
	m_zpWall.Translate(0, 0, 0);
	m_zpWallKuppel.Translate(0, 8, 0);
	
	
	
}


Building01::~Building01()
{
}


NAMESPACE_VIEW_E