#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class Gebaeude02
{
private:

	CGeoWall m_zWallNorth;
	CPlacement m_zpWallNorth;
	CMaterial m_zmWallNorth;

	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallSouth;

	CGeoWall *pm_zWallNSWE;

	CGeoCube m_zgDach;
	CPlacement m_zpDach;
	CMaterial m_zmDach;

	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowInlay;

	CGeoWall m_zgWallFrame;
	CMaterial m_zmWallFrame;
	CGeoWall m_zgWallGlass;
	CMaterial m_zmWallGlass;

	CPlacement m_zpGebaeude02;
public:
	Gebaeude02();
	~Gebaeude02();

	CPlacement *getPlacement();
};


NAMESPACE_VIEW_E
