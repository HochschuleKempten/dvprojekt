#pragma once


#include "VGeneral.h"

NAMESPACE_VIEW_B



class Building02: public CPlacement
{
private:

	CGeoWall m_zWallNorth;
	CPlacement m_zpWallNorth;
	CMaterial m_zmWallNorth;

	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallSouth;
	CPlacement m_zpbuilding02;
	

	CGeoCube m_zgDach;
	CPlacement m_zpDach;
	CMaterial m_zmDach;

	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowInlay;

	CGeoWall m_zgWallFrame;
	CMaterial m_zmWallFrame;
	CGeoWall m_zgWallGlass;
	CMaterial m_zmWallGlass;

	CMaterial m_zm;

	float fstandardwidthwall = 5.F;
	float fstandardheightwall = 5.F;
	float fstandarddepthwall = 0.1F;

	float fstandardwidthroof = 2.6F;
	float fstandardheightroof = 0.1F;
	float fstandarddepthroof = 2.6F;
	
	float fresize;

public:
	Building02();
	Building02(float fResize);
	~Building02();

	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void scaleforLoDs();
};



NAMESPACE_VIEW_E