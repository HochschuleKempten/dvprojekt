#include "Gebaeude03.h"
NAMESPACE_VIEW_B

Gebaeude03::Gebaeude03()
{
	
	
	

	//Geäubde scenePlacement
	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallWest);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallSouth);
	AddPlacement(&m_zpDach);

	

	//PlacementsGeo
	

	//Gebäude PlacementsGEo

	
	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(&m_zWallNorth);
	m_zpWallEast.AddGeo(&m_zWallNorth);
	m_zpWallSouth.AddGeo(&m_zWallNorth);
	m_zpDach.AddGeo(&m_zgDach);

	//Walls&Windows
	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.1, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 7, 3);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);

	//GeoKörper
	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallNorth.Init(5.1, 1, 1, &m_zmWallNorth);
	m_zgDach.Init(CHVector(5.1, 1, 5.1, 0), &m_zmDach);
	//Ops
	

	




	//GebäudeOps

	m_zpWallNorth.Translate(1, 0, 8);


	m_zpWallWest.RotateY(PI / 2);
	m_zpWallWest.TranslateDelta(10.9, 0, 8);

	m_zpWallEast.RotateY(PI / 2);
	m_zpWallEast.TranslateDelta(1, 0, 8);



	m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(10.9, 0, -1.9);

	m_zpDach.Translate(6, 5.1, 3.05);
}


Gebaeude03::~Gebaeude03()
{
}

NAMESPACE_VIEW_E