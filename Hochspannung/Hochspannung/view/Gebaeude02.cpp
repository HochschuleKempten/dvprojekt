#include "Gebaeude02.h"

NAMESPACE_VIEW_B


Gebaeude02::Gebaeude02()
{
	m_zpGebaeude02.AddPlacement(&m_zpWallNorth);
	m_zpGebaeude02.AddPlacement(&m_zpWallWest);
	m_zpGebaeude02.AddPlacement(&m_zpWallEast);
	m_zpGebaeude02.AddPlacement(&m_zpWallSouth);
	m_zpGebaeude02.AddPlacement(&m_zpDach);


	pm_zWallNSWE = &m_zWallNorth;
	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(pm_zWallNSWE);
	m_zpWallEast.AddGeo(pm_zWallNSWE);
	m_zpWallSouth.AddGeo(pm_zWallNSWE);
	m_zpDach.AddGeo(&m_zgDach);


	//Walls&Windows
	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.2, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 4, 5);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);



	//GeoKörper
	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallNorth.Init(50, 50, 1, &m_zmWallNorth);
	m_zgDach.Init(CHVector(25, 1, 25, 0), &m_zmDach);



	m_zpWallNorth.Translate(0, 0, 60);

	m_zpWallWest.RotateY(PI / 2);
	m_zpWallWest.TranslateDelta(49, 0, 60);

	m_zpWallEast.RotateY(PI / 2);
	m_zpWallEast.TranslateDelta(0, 0, 60);
	

	m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(50, 0, 11);

	m_zpDach.Translate(25, 50, 35);

}


Gebaeude02::~Gebaeude02()
{
}

CPlacement* Gebaeude02::getPlacement(){

	return &m_zpGebaeude02;
}


NAMESPACE_VIEW_E
