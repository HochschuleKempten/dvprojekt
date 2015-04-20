#include "Gebaeude02.h"

NAMESPACE_VIEW_B
Gebaeude02::Gebaeude02()
{
	AddPlacement(&m_zpWallNorth);
	AddPlacement(&m_zpWallWest);
	AddPlacement(&m_zpWallEast);
	AddPlacement(&m_zpWallSouth);
	AddPlacement(&m_zpDach);


	
	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(&m_zWallNorth);
	m_zpWallEast.AddGeo(&m_zWallNorth);
	m_zpWallSouth.AddGeo(&m_zWallNorth);
	m_zpDach.AddGeo(&m_zgDach);


	//Walls&Windows
	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.2, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 4, 5);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);



	//GeoK�rper
	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallNorth.Init(5, 5, 1, &m_zmWallNorth);
	m_zgDach.Init(CHVector(2.5, 1, 2.5, 0), &m_zmDach);



	m_zpWallNorth.Translate(0, 0, 60);

	m_zpWallWest.RotateY(PI / 2);
	m_zpWallWest.TranslateDelta(4.9, 0, 6);

	m_zpWallEast.RotateY(PI / 2);
	m_zpWallEast.TranslateDelta(0, 0, 6);
	

	m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(5, 0, 1.1);

	m_zpDach.Translate(2.5, 5, 3.5);

}


Gebaeude02::~Gebaeude02()
{
}

NAMESPACE_VIEW_E