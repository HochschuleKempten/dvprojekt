#pragma once

#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B


class CLargeOfficeBuilding : public CPlacement, public IViewModel
{
public:
	CLargeOfficeBuilding(float fResize);
	~CLargeOfficeBuilding(void);
	virtual void init() override;


	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void RotateAll();
	void TranslateAll();
	void scaleForLod();
private:
	

	float fResize;
	
	

	CPlacement m_zpWallNorth0;
	CPlacement m_zpWallNorth1;
	CPlacement m_zpWallNorth2;

	CPlacement m_zpWallSouth0;
	CPlacement m_zpWallSouth1;
	CPlacement m_zpWallSouth2;

	CPlacement m_zpWallWest;

	CPlacement m_zpWallEast0;
	CPlacement m_zpWallEast1;
	CPlacement m_zpWallEast2;

	CPlacement m_zpRoof0;
	CPlacement m_zpRoof1;
	CPlacement m_zpRoof2;


	CPlacement m_zpDoor;
	CPlacement m_zpWindow;
	CPlacement m_zpWindowHigh;
	CPlacement m_zpWindowWide;


	//Walls
	CGeoWall m_zgWallNorth0;
	CGeoWall m_zgWallNorth1;
	CGeoWall m_zgWallNorth2;

	CGeoWall m_zgWallSouth0;
	CGeoWall m_zgWallSouth1;
	CGeoWall m_zgWallSouth2;

	CGeoWall m_zgWallEast0;
	CGeoWall m_zgWallEast1;
	CGeoWall m_zgWallEast2;
	CGeoWall m_zgWallWest;

	CGeoWall m_zgRoof0;
	CGeoWall m_zgRoof1;
	CGeoWall m_zgRoof2;


	//Windows
	CGeoWindow m_zgDoor;
	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowHigh;
	CGeoWindow m_zgWindowWide;

	//Frame
	CGeoWall m_zgFrame;
	CGeoWall m_zgFrameHigh;

};


NAMESPACE_VIEW_E
