#pragma once


#include "VGeneral.h"
#include "IViewModel.h"

NAMESPACE_VIEW_B



class Building02: public CPlacement,public IViewModel
{
private:

	CGeoWall m_zWallNorth;
	CPlacement m_zpWallNorth;

	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallSouth;
	CPlacement m_zpbuilding02;
	

	CGeoCube m_zgDach;
	CPlacement m_zpDach;
		
	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowInlay;

	CGeoWall m_zgWallFrame;
	CGeoWall m_zgWallGlass;

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
	virtual void init() override;

	void InitWindows();
	void AddWindows();
	void InitWalls();
	void AddPlacements();
	void TranslateAll();
	void scaleforLoDs();


	virtual void switchOn() override;

	virtual void switchOff() override;

	virtual float getWidth() override
	{
		return 0.0f;
	}

	virtual float getHeight() override
	{
		return 0.0f;
	}

};



NAMESPACE_VIEW_E