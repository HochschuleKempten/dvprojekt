#pragma once


#include "VGeneral.h"
#include "VMaterialLoader.h"

NAMESPACE_VIEW_B

class Building01 : public CPlacement
{

private:
	CGeoWindow m_zWindow;
	CGeoWindow m_zWindowInlay;


	CGeoWall m_zWallLod1;
	CGeoWall m_zWallLod2;
	CGeoWall m_zWallLod3;

	CPlacement m_zpWall;
	CPlacement m_zpWallLod1;
	CPlacement m_zpWallLod2;
	CPlacement m_zpWallLod3;


	CGeoWall m_zWallKuppelLod1;
	CGeoWall m_zWallKuppelLod2;
	CGeoWall m_zWallKuppelLod3;

	CPlacement m_zpWallKuppel;
	CPlacement m_zpWallKuppelLod1;
	CPlacement m_zpWallKuppelLod2;
	CPlacement m_zpWallKuppelLod3;
	

	CGeoWall m_zWallFrame;
	CMaterial m_zmWallFrame;

	CGeoWall m_zWallGlass;
	CMaterial m_zmWallGlass;


	//for testing lods
	CMaterial test1;
	CMaterial test2;
	

public:

	Building01();
	~Building01();
	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void scaleforLoDs();

		
};




NAMESPACE_VIEW_E