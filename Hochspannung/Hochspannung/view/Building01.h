#pragma once


#include "VGeneral.h"

NAMESPACE_VIEW_B

class Building01 : public CPlacement
{

private:
	CGeoWindow m_zWindow;
	CGeoWindow m_zWindowInlay;


	CGeoWall m_zWall;
	CPlacement m_zpWall;
	CMaterial m_zmWall;


	CGeoWall m_zWallKuppel;
	CPlacement m_zpWallKuppel;
	CMaterial m_zmWallKuppel;

	CGeoWall m_zWallFrame;
	CMaterial m_zmWallFrame;

	CGeoWall m_zWallGlass;
	CMaterial m_zmWallGlass;



public:

	Building01();
	~Building01();
	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();

		
};




NAMESPACE_VIEW_E