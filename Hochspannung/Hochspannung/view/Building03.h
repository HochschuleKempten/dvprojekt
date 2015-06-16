#pragma once


#include "VGeneral.h"

NAMESPACE_VIEW_B
class Building03 : public CPlacement
{
private:

	//Gebäude03
	CPlacement m_zpbuilding03;

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

	CMaterial m_zmstand;

	//Boden
	float fstandardwidthwall = 5.F;
	float fstandardheightwall = 10.F;
	float fstandarddepthwall = 0.1F;

	float fstandardwidthroof = 2.6F;
	float fstandardheightroof = 0.1F;
	float fstandarddepthroof = 2.6F;

	float fresize ;
	

public:

	Building03();
	Building03(float fResize);
	~Building03();

	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void scaleforLoDs();

};


NAMESPACE_VIEW_E