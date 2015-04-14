#include "Gebauede01.h"

NAMESPACE_VIEW_B


Gebauede01::Gebauede01()
{
	
	m_zpGebauede01.AddPlacement(&m_zpWall);
	m_zpGebauede01.AddPlacement(&m_zpWallKuppel);
	
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



	//GeoK�rper
	m_zWall.InitTube(25, 80, 0.2, &m_zmWall);
	m_zWallKuppel.InitDome(25, 0.2, &m_zmWallKuppel);



	//Ops
	m_zpWall.Translate(0, 0, 0);
	m_zpWallKuppel.Translate(0, 80, 0);
	
	
	
}


Gebauede01::~Gebauede01()
{
}


CPlacement*Gebauede01::getPlacement(){
	
	return &m_zpGebauede01;
}


NAMESPACE_VIEW_E
