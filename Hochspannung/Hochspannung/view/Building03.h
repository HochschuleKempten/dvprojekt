#pragma once


#include "VGeneral.h"

NAMESPACE_VIEW_B
class Building03 : public CPlacement
{
private:

	//Gebäude03
	CGeoWall m_zWallNorth;
	CPlacement m_zpWallNorth;
	CMaterial m_zmWallNorth;

	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallSouth;

	

	CGeoCube m_zgDach;
	CPlacement m_zpDach;
	CMaterial m_zmDach;

	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowInlay;

	CGeoWall m_zgWallFrame;
	CMaterial m_zmWallFrame;

	CGeoWall m_zgWallGlass;
	CMaterial m_zmWallGlass;


	//Boden

	

public:

	Building03();
	~Building03();

	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();

};


NAMESPACE_VIEW_E