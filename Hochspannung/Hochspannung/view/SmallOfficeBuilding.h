#pragma once





#include "VGeneral.h"

NAMESPACE_VIEW_B


class CSmallOfficeBuilding : public CPlacement
{
public:
	CSmallOfficeBuilding();
	CSmallOfficeBuilding(float fResize);
	~CSmallOfficeBuilding(void);

	void InitWindows();
	void InitWalls();
	void AddWindows();
	void AddPlacements();
	void RotateAll();
	void TranslateAll();
	

private:



	float fResize;


	

	CPlacement m_zpWallNorth;
	CPlacement m_zpWallSouth;
	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpRoof;
	CPlacement m_zpDoor;
	CPlacement m_zpWindow;


	//Walls
	CGeoWall m_zgWallNorth;
	CGeoWall m_zgWallSouth;
	CGeoWall m_zgWallEast;
	CGeoWall m_zgWallWest;
	CGeoWall m_zgRoof;
	//CGeoWall m_zgGround;

	//Windows
	CGeoWindow m_zgDoor;
	CGeoWindow m_zgWindow;
	//Frame
	CGeoWall m_zgFrame;

	//Combinations

	CMaterial m_zm;


};





NAMESPACE_VIEW_E