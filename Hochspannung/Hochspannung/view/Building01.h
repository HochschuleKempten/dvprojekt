#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class Building01 : public CPlacement
{

private:
	CGeoWindow m_zWindow;
	CGeoWindow m_zWindowInlay;


	CPlacement m_zpbuilding01;
	CGeoWall m_zWall;
	CPlacement m_zpWall;



	CGeoWall m_zWallKuppel;

	CPlacement m_zpWallKuppel;

	

	CGeoWall m_zWallFrame;
	CMaterial m_zmWallFrame;

	CGeoWall m_zWallGlass;
	CMaterial m_zmWallGlass;

	float fstandardradius=3.5F;
	float fstandardheight=10.F;
	float fstandardthickness = 0.2;

	float fresize;


	
	

public:

	Building01();
	explicit Building01(float fResize);
	virtual ~Building01();
	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void scaleforLoDs();

		
};


NAMESPACE_VIEW_E
