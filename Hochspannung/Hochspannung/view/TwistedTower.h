#pragma once


#include "VGeneral.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


class CTwistedTower : public CPlacement
{
public:
	CTwistedTower(void);
	~CTwistedTower(void);

	void InitWindows();
	void InitWalls();
	void AddWindows();
	void CreateMiters();
	void AddPlacements();
	void RotateAll();
	void TranslateAll();
	void ScaleForLod();

private:



	float fResize;



	CPlacement m_zpWindow;

	CPlacement m_zpRoof;

	CPlacement m_zpWallNorth;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallWest;

	
	CGeoWall m_zgRoof;

	CGeoWall m_zgWallNorth;
	CGeoWall m_zgWallEast;
	CGeoWall m_zgWallWest;

	//Windows
	CGeoWindow m_zgWindow;

	CMaterial m_zm;
	

};





NAMESPACE_VIEW_E